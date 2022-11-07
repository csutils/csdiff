/*
 * Copyright (C) 2011-2022 Red Hat, Inc.
 *
 * This file is part of csdiff.
 *
 * csdiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * csdiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with csdiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "parser-json.hh"

#include "abstract-tree.hh"
#include "parser-common.hh"
#include "parser-gcc.hh"            // for GccPostProcessor
#include "parser-json-cov.hh"
#include "parser-json-simple.hh"
#include "regex.hh"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/property_tree/json_parser.hpp>

/// tree decoder of the SARIF format
class SarifTreeDecoder: public AbstractTreeDecoder {
    public:
        void readScanProps(
                TScanProps             *pDst,
                const pt::ptree        *root)
            override;

        void readRoot(const pt::ptree *root) override;

        bool readNode(Defect *def) override;

    private:
        void updateCweMap(const pt::ptree *driverNode);

        std::string                 singleChecker = "UNKNOWN_SARIF_WARNING";
        const RE                    reCwe = RE("^CWE-([0-9]+)$");
        const RE                    reVersion = RE("^([0-9][0-9.]+).*$");
        const RE                    reRuleId =
            RE("(" RE_CHECKER_NAME "): (" RE_EVENT ")");

        typedef std::map<std::string, int>  TCweMap;
        TCweMap                     cweMap;

        ImpliedAttrDigger           digger;
};

/// tree decoder of the JSON format produced by GCC
class GccTreeDecoder: public AbstractTreeDecoder {
    public:
        bool readNode(Defect *def) override;

    private:
        const GccPostProcessor postProc;
};

/// tree decoder of the JSON format produced by ShellCheck
class ShellCheckTreeDecoder: public AbstractTreeDecoder {
    public:
        bool readNode(Defect *def) override;

    private:
        const GccPostProcessor postProc;
};

struct JsonParser::Private {
    using TDecoderPtr = std::unique_ptr<AbstractTreeDecoder>;

    InStream                       &input;
    TDecoderPtr                     decoder;
    pt::ptree                       root;
    int                             defNumber = 0;
    TScanProps                      scanProps;

    Private(InStream &input):
        input(input)
    {
    }

    void dataError(const std::string &msg);
};

void JsonParser::Private::dataError(const std::string &msg)
{
    this->input.handleError();
    if (this->input.silent())
        return;

    std::cerr
        << this->input.fileName() << ": error: failed to read defect #"
        << this->defNumber << ": " << msg << "\n";
}

JsonParser::JsonParser(InStream &input):
    d(new Private(input))
{
    try {
        // parse JSON
        read_json(input.str(), d->root);

        pt::ptree::const_iterator itFirst = d->root.begin();
        if (itFirst == d->root.end())
            // empty JSON, such as []
            return;

        const pt::ptree &first = itFirst->second;

        // recognize inner format of the JSON document
        pt::ptree *node = &d->root;
        if (findChildOf(&node, d->root, "defects"))
            // csdiff-native JSON format
            d->decoder.reset(new SimpleTreeDecoder(d->input));
        else if (findChildOf(&node, d->root, "issues"))
            // Coverity JSON format
            d->decoder.reset(new CovTreeDecoder);
        else if (findChildOf(&node, d->root, "runs"))
            // SARIF format
            d->decoder.reset(new SarifTreeDecoder);
        else if (findChildOf(&node, d->root, "comments"))
            // ShellCheck JSON format
            d->decoder.reset(new ShellCheckTreeDecoder);
        else if (first.not_found() != first.find("kind"))
            // GCC JSON format
            d->decoder.reset(new GccTreeDecoder);
        else
            throw pt::ptree_error("unknown JSON format");

        // read scan properties if available
        d->decoder->readScanProps(&d->scanProps, &d->root);

        // process the root node
        d->decoder->readRoot(node);
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

JsonParser::~JsonParser() = default;

bool JsonParser::hasError() const
{
    return d->input.anyError();
}

const TScanProps& JsonParser::getScanProps() const
{
    return d->scanProps;
}

bool JsonParser::getNext(Defect *def)
{
    // error recovery loop
    for (;;) {
        try {
            // make sure the Defect structure is properly initialized
            (*def) = Defect();

            // read the current node and move to the next one
            const bool ok = d->decoder->readNode(def);
            if (ok)
                d->defNumber++;

            return ok;
        }
        catch (pt::ptree_error &e) {
            d->dataError(e.what());
        }
    }
}

void SarifTreeDecoder::updateCweMap(const pt::ptree *driverNode)
{
    const pt::ptree *rules;
    if (!findChildOf(&rules, *driverNode, "rules"))
        return;

    for (const auto &item : *rules) {
        const pt::ptree &rule = item.second;
        const auto id = valueOf<std::string>(rule, "id", "");
        if (id.empty())
            // rule ID missing
            continue;

        const pt::ptree *props;
        if (!findChildOf(&props, rule, "properties"))
            // properties missing
            continue;

        const pt::ptree *cweList;
        if (!findChildOf(&cweList, *props, "cwe") || cweList->empty())
            // cwe list missing
            continue;

        const std::string cweStr = cweList->begin()->second.data();
        boost::smatch sm;
        if (!boost::regex_match(cweStr, sm, this->reCwe))
            // unable to parse cwe
            continue;

        const int cwe = std::stoi(sm[/* cwe */ 1]);
        this->cweMap[id] = cwe;
    }
}

void SarifTreeDecoder::readScanProps(
        TScanProps                 *pDst,
        const pt::ptree            *root)
{
    // read external properties if available
    const pt::ptree *iep;
    if (findChildOf(&iep, *root, "inlineExternalProperties")
            && (1U == iep->size()))
    {
        const pt::ptree *props;
        if (findChildOf(&props, iep->begin()->second, "externalizedProperties"))
            for (const pt::ptree::value_type &item : *props)
                (*pDst)[item.first] = item.second.data();
    }

    // check that we have exactly one run
    const pt::ptree *runs;
    if (!findChildOf(&runs, *root, "runs") || (1U != runs->size()))
        return;

    // check which tool was used for the run
    const pt::ptree *toolNode;
    if (!findChildOf(&toolNode, runs->begin()->second, "tool"))
        return;
    const pt::ptree *driverNode;
    if (!findChildOf(&driverNode, *toolNode, "driver"))
        return;

    this->updateCweMap(driverNode);

    const auto name = valueOf<std::string>(*driverNode, "name", "");
    auto version = valueOf<std::string>(*driverNode, "version", "");
    if (version.empty())
        version = valueOf<std::string>(*driverNode, "semanticVersion", "");

    if (name == "SnykCode") {
        // Snyk Code detected!
        this->singleChecker = "SNYK_CODE_WARNING";

        if (!version.empty())
            // record tool version of Snyk Code
            (*pDst)["analyzer-version-snyk-code"] = version;
    }
    else if (name == "gitleaks") {
        // gitleaks
        this->singleChecker = "GITLEAKS_WARNING";

        if (!version.empty())
            (*pDst)["analyzer-version-gitleaks"] = version;
    }
    else if (boost::starts_with(name, "GNU C")) {
        // GCC
        this->singleChecker = "COMPILER_WARNING";

        boost::smatch sm;
        if (boost::regex_match(version, sm, this->reVersion))
            (*pDst)["analyzer-version-gcc"] = sm[/* version */ 1];
    }
}

void SarifTreeDecoder::readRoot(const pt::ptree *runs)
{
    if (1U != runs->size())
        // exactly one run expected
        return;

    if (!findChildOf(&defList_, runs->begin()->second, "results"))
        // no results found
        return;

    // initialize the iteration over "results"
    defIter_ = defList_->begin();
}

static void sarifReadLocation(DefEvent *pEvt, const pt::ptree &loc)
{
    const pt::ptree *pl;
    if (!findChildOf(&pl, loc, "physicalLocation"))
        // unknown location info format
        return;

    const pt::ptree *al;
    if (findChildOf(&al, *pl, "artifactLocation")) {
        const auto uri = valueOf<std::string>(*al, "uri", "");
        if (!uri.empty())
            // read file name
            pEvt->fileName = uri;
    }

    const pt::ptree *reg;
    if (findChildOf(&reg, *pl, "region")) {
        // read line/col if available
        pEvt->line = valueOf<int>(*reg, "startLine", 0);
        pEvt->column = valueOf<int>(*reg, "startColumn", 0);
    }
}

static bool sarifReadMsg(std::string *pDst, const pt::ptree &node)
{
    const pt::ptree *msgNode;
    if (!findChildOf(&msgNode, node, "message"))
        return false;

    *pDst = valueOf<std::string>(*msgNode, "text", "<unknown>");
    return true;
}

static void sarifReadComments(Defect *pDef, const pt::ptree &relatedLocs)
{
    for (const auto &item : relatedLocs) {
        const pt::ptree &loc = item.second;

        DefEvent tmp;
        sarifReadLocation(&tmp, loc);
        if (!tmp.fileName.empty())
            // location info available --> not a csdiff-encoded comment
            continue;

        DefEvent evt("#");
        if (!sarifReadMsg(&evt.msg, loc))
            continue;

        evt.verbosityLevel = 1;
        pDef->events.push_back(evt);
    }
}

static void sarifReadCodeFlow(Defect *pDef, const pt::ptree &cf)
{
    const pt::ptree *tf;
    if ((1U != cf.size())
            || !findChildOf(&tf, cf.begin()->second, "threadFlows"))
        return;

    const pt::ptree *locs;
    if (1U != tf->size()
            || !findChildOf(&locs, tf->begin()->second, "locations"))
        return;

    TEvtList events;
    int keyEventIdx = -1;

    // read the full list of events
    for (const auto &item : *locs) {
        const pt::ptree &tfLoc = item.second;

        const pt::ptree *kindList;
        if (!findChildOf(&kindList, tfLoc, "kinds") || kindList->empty())
            // kind of the event not specified
            continue;

        // concatenate event name
        std::string evtName;
        for (const auto &kindItem : *kindList) {
            const pt::ptree &kind = kindItem.second;
            if (!evtName.empty())
                evtName += "_";
            evtName += kind.data();
        }

        // append a new event of the specified kind
        events.push_back(DefEvent(evtName));
        DefEvent &evt = events.back();

        evt.verbosityLevel = valueOf<int>(tfLoc, "nestingLevel", 1);
        if (!evt.verbosityLevel)
            // update key event
            keyEventIdx = events.size() - 1U;

        const pt::ptree *loc;
        if (!findChildOf(&loc, tfLoc, "location"))
            // location info missing
            return;

        sarifReadLocation(&evt, *loc);
        sarifReadMsg(&evt.msg, *loc);
    }

    if (events.size() <= 1U)
        // we failed to read more than one event
        return;

    if (-1 == keyEventIdx) {
        // no key event in threadFlows
        std::copy(events.begin(), events.end(),
                std::back_inserter(pDef->events));
    }
    else {
        // use only the events from threadFlows
        events.swap(pDef->events);
        pDef->keyEventIdx = keyEventIdx;
    }
}

static int sarifCweFromDefNode(const pt::ptree &defNode)
{
    const pt::ptree *taxa;
    if (!findChildOf(&taxa, defNode, "taxa"))
        return 0;

    for (const auto &item : *taxa) {
        const pt::ptree &t = item.second;

        const pt::ptree *tc;
        if (!findChildOf(&tc, t, "toolComponent"))
            continue;

        if (valueOf<std::string>(*tc, "name", "") == "cwe")
            return valueOf<int>(t, "id", 0);
    }

    // not found
    return 0;
}

bool SarifTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    const pt::ptree *pNode = this->nextNode();
    if (!pNode)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *pNode;

    // initialize the defect structure
    *def = Defect(this->singleChecker);

    // initialize the key event
    const auto level = valueOf<std::string>(defNode, "level", "warning");
    def->events.push_back(DefEvent(level));
    DefEvent &keyEvent = def->events.back();

    // read "rule" that triggered the report
    const auto rule = valueOf<std::string>(defNode, "ruleId", "");
    if (!rule.empty()) {
        boost::smatch sm;
        if (boost::regex_match(rule, sm, reRuleId)) {
            // csdiff format
            def->checker    = sm[/* checker  */ 1];
            keyEvent.event  = sm[/* keyEvent */ 2];
        }
        else {
            // output of a single tool
            keyEvent.event += "[" + rule + "]";

            // distinguish GCC compiler/analyzer
            if (def->checker == "COMPILER_WARNING"
                    && boost::starts_with(rule, "-Wanalyzer-"))
                def->checker = "GCC_ANALYZER_WARNING";
        }
    }

    def->cwe = sarifCweFromDefNode(defNode);
    if (!def->cwe) {
        // lookup cwe
        const TCweMap::const_iterator it = this->cweMap.find(rule);
        if (this->cweMap.end() != it)
            def->cwe = it->second;
    }

    // read location and diagnostic message
    keyEvent.fileName = "<unknown>";
    const pt::ptree *locs;
    if (findChildOf(&locs, defNode, "locations") && !locs->empty())
        sarifReadLocation(&keyEvent, locs->begin()->second);
    sarifReadMsg(&keyEvent.msg, defNode);

    // read code flow if available
    const pt::ptree *cf;
    if (findChildOf(&cf, defNode, "codeFlows"))
        sarifReadCodeFlow(def, *cf);

    // read comments if available
    const pt::ptree *relatedLocs;
    if (findChildOf(&relatedLocs, defNode, "relatedLocations"))
        sarifReadComments(def, *relatedLocs);

    this->digger.inferLangFromChecker(def);
    this->digger.inferToolFromChecker(def);

    return true;
}

static bool gccReadEvent(DefEvent *pEvt, const pt::ptree &evtNode)
{
    using std::string;

    // read kind (error, warning, note)
    string &evtName = pEvt->event;
    evtName = valueOf<string>(evtNode, "kind", "");
    if (evtName.empty())
        return false;

    // read location
    pEvt->fileName = "<unknown>";
    const pt::ptree *locs;
    if (findChildOf(&locs, evtNode, "locations") && !locs->empty()) {
        const pt::ptree *caret;
        if (findChildOf(&caret, locs->begin()->second, "caret")) {
            pEvt->fileName  = valueOf<string>(*caret, "file", "<unknown>");
            pEvt->line      = valueOf<int>   (*caret, "line", 0);
            pEvt->column    = valueOf<int>   (*caret, "byte-column", 0);
        }
    }

    // read message
    pEvt->msg = valueOf<string>(evtNode, "message", "<unknown>");

    // read -W... if available
    const string option = valueOf<string>(evtNode, "option", "");
    if (!option.empty())
        pEvt->msg += " [" + option + "]";

    return true;
}

bool GccTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    const pt::ptree *pNode = this->nextNode();
    if (!pNode)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *pNode;

    *def = Defect("COMPILER_WARNING");

    // read key event
    def->events.push_back(DefEvent());
    if (!gccReadEvent(&def->events.back(), defNode))
        return false;

    // read other events if available
    const pt::ptree *children;
    if (findChildOf(&children, defNode, "children")) {
        for (const auto &item : *children) {
            const pt::ptree &evtNode = item.second;

            DefEvent evt;
            if (gccReadEvent(&evt, evtNode))
                def->events.emplace_back(evt);
        }
    }

    // read CWE ID if available
    const pt::ptree *meta;
    if (findChildOf(&meta, defNode, "metadata"))
        def->cwe = valueOf<int>(*meta, "cwe", 0);

    // apply post-processing rules
    this->postProc.apply(def);

    return true;
}

static bool scReadEvent(DefEvent *pEvt, const pt::ptree &evtNode)
{
    using std::string;

    // read level (error, warning, note)
    string &evtName = pEvt->event;
    evtName = valueOf<string>(evtNode, "level", "");
    if (evtName.empty())
        return false;

    // read location
    pEvt->fileName = valueOf<string>(evtNode, "file", "<unknown>");
    pEvt->line     = valueOf<int>   (evtNode, "line", 0);
    pEvt->column   = valueOf<int>   (evtNode, "byte-column", 0);

    // read message
    pEvt->msg = valueOf<string>(evtNode, "message", "<unknown>");

    // append [SC...] if available
    const string code = valueOf<string>(evtNode, "code", "");
    if (!code.empty())
        pEvt->msg += " [SC" + code + "]";

    return true;
}

bool ShellCheckTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    const pt::ptree *pNode = this->nextNode();
    if (!pNode)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *pNode;

    *def = Defect("SHELLCHECK_WARNING");

    // read key event
    def->events.push_back(DefEvent());
    if (!scReadEvent(&def->events.back(), defNode))
        return false;

    // TODO: go through fix/replacements nodes

    // apply post-processing rules
    this->postProc.apply(def);

    return true;
}
