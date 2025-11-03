/*
 * Copyright (C) 2012-2022 Red Hat, Inc.
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

#include "parser-json-sarif.hh"

#include "parser-common.hh"         // for ImpliedAttrDigger
#include "regex.hh"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

struct SarifTreeDecoder::Private {
    void updateCweMap(const pt::ptree *driverNode);
    void readToolInfo(TScanProps *pScanProps, const pt::ptree *toolNode);

    std::string                 singleChecker = "UNKNOWN_SARIF_WARNING";
    std::string                 pwd;
    const RE                    reFileUrl = RE("^file://");
    const RE                    reCwe = RE("^CWE-([0-9]+)$");
    const RE                    reVersion = RE("^([0-9][0-9.]+).*$");
    const RE                    reRuleId =
        RE("(" RE_CHECKER_NAME "): (" RE_EVENT ")");

    typedef std::map<std::string, int>  TCweMap;
    TCweMap                     cweMap;

    ImpliedAttrDigger           digger;
};

SarifTreeDecoder::SarifTreeDecoder():
    d(new Private)
{
}

SarifTreeDecoder::~SarifTreeDecoder() = default;

void SarifTreeDecoder::Private::updateCweMap(const pt::ptree *driverNode)
{
    const pt::ptree *rules;
    if (!findChildOf(&rules, *driverNode, "rules"))
        return;

    for (const auto &item : *rules) {
        const pt::ptree &rule = item.second;
        const auto id = valueOf<std::string>(rule, "id");
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

void SarifTreeDecoder::Private::readToolInfo(
        TScanProps                 *pScanProps,
        const pt::ptree            *toolNode)
{
    const pt::ptree *driverNode;
    if (!findChildOf(&driverNode, *toolNode, "driver"))
        return;

    this->updateCweMap(driverNode);

    const auto name = valueOf<std::string>(*driverNode, "name");
    auto version = valueOf<std::string>(*driverNode, "version");
    if (version.empty())
        version = valueOf<std::string>(*driverNode, "semanticVersion");

    if (name == "SnykCode") {
        // Snyk Code detected!
        this->singleChecker = "SNYK_CODE_WARNING";

        if (!version.empty())
            // record tool version of Snyk Code
            (*pScanProps)["analyzer-version-snyk-code"] = std::move(version);
    }
    else if (name == "gitleaks") {
        // gitleaks
        this->singleChecker = "GITLEAKS_WARNING";

        if (!version.empty())
            (*pScanProps)["analyzer-version-gitleaks"] = std::move(version);
    }
    else if (name == "Semgrep OSS") {
        // semgrep
        this->singleChecker = "SEMGREP_WARNING";

        if (!version.empty())
            (*pScanProps)["analyzer-version-semgrep"] = std::move(version);
    }
    else if (boost::starts_with(name, "GNU C")) {
        // GCC
        this->singleChecker = "COMPILER_WARNING";

        boost::smatch sm;
        if (boost::regex_match(version, sm, this->reVersion))
            (*pScanProps)["analyzer-version-gcc"] = sm[/* version */ 1];
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
    if (!findChildOf(&runs, *root, "runs")
            || /* TODO: warn bout unsupported format */ (1U != runs->size()))
        return;

    // jump to the only run
    const pt::ptree &run0 = runs->begin()->second;

    // check which tool was used for the run
    const pt::ptree *toolNode;
    if (findChildOf(&toolNode, run0, "tool"))
        d->readToolInfo(pDst, toolNode);

    // read PWD so that we can reconstruct absolute paths later on
    const pt::ptree *uriBase, *pwdNode, *uriNode;
    if (findChildOf(&uriBase, run0, "originalUriBaseIds")
            && findChildOf(&pwdNode, *uriBase, "PWD")
            && findChildOf(&uriNode, *pwdNode, "uri"))
    {
        // remove the "file://" prefix
        const auto &pwd = uriNode->data();
        d->pwd = boost::regex_replace(pwd, d->reFileUrl, "");
        // FIXME: Should we check whether d->pwd begins with '/'?

        // make sure that d->pwd ends with '/'
        if (!d->pwd.empty() && *d->pwd.rbegin() != '/')
            d->pwd += '/';
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
        const auto uri = valueOf<std::string>(*al, "uri");
        if (!uri.empty())
            // read file name
            pEvt->fileName = std::move(uri);
    }

    const pt::ptree *reg;
    if (findChildOf(&reg, *pl, "region")) {
        // read line
        if ((pEvt->line = valueOf<int>(*reg, "startLine"))) {
            const int endLine = valueOf<int>(*reg, "endLine");
            pEvt->vSize = diffNums(pEvt->line, endLine);
        }

        // read column
        if ((pEvt->column = valueOf<int>(*reg, "startColumn"))) {
            const int endColumn = valueOf<int>(*reg, "endColumn");
            pEvt->hSize = diffNums(pEvt->column, endColumn);
        }
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
        pDef->events.push_back(std::move(evt));
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

        std::string evtName;
        const pt::ptree *kindList;
        if (findChildOf(&kindList, tfLoc, "kinds")) {
            // calculate event name from the `kinds` list
            for (const auto &kindItem : *kindList) {
                const pt::ptree &kind = kindItem.second;
                if (!evtName.empty())
                    evtName += "_";
                evtName += kind.data();
            }
        }

        // append a new event of the specified kind
        events.push_back(DefEvent(evtName));
        DefEvent &evt = events.back();

        // read/infer verbosity level
        evt.verbosityLevel = valueOf<int>(tfLoc, "nestingLevel",
                (evt.event.empty())
                ? /* trace */ 2
                : /* info  */ 1);

        if (!evt.verbosityLevel)
            // update key event
            keyEventIdx = events.size() - 1U;

        const pt::ptree *loc;
        if (!findChildOf(&loc, tfLoc, "location"))
            // location info missing
            return;

        sarifReadLocation(&evt, *loc);
        sarifReadMsg(&evt.msg, *loc);

        if (evt.event.empty()) {
            // if no `kind` is given, assume a generic trace event
            evt.event = "path";
            if (evt.msg.empty())
                evt.msg = "generic trace event";
        }
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

        if (valueOf<std::string>(*tc, "name") == "cwe")
            return valueOf<int>(t, "id");
    }

    // not found
    return 0;
}

static void expandRelativePaths(Defect *pDef, const std::string &pwd)
{
    if (pwd.empty())
        // no PWD info provided
        return;

    // go through all events
    for (DefEvent &evt : pDef->events) {
        std::string &fileName = evt.fileName;
        if (fileName.empty())
            // no file path to expand
            continue;

        const unsigned char beginsWith = *fileName.begin();
        switch (beginsWith) {
            case '/':   // absolute path
            case '<':   // <unknown> and the like
                continue;

            default:
                // prepend `pwd` to relative path
                boost::filesystem::path fullPath = pwd + fileName;

                // convert "/a/b/../c" to "a/c"
                fileName = fullPath.lexically_normal().string();
        }
    }
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
    *def = Defect(d->singleChecker);

    // read "level" if available and propagate "error" to the "imp" flag
    const auto level = valueOf<std::string>(defNode, "level", "warning");
    if (level == "error")
        def->imp = 1;

    // initialize the key event
    def->events.push_back(DefEvent(level));
    DefEvent &keyEvent = def->events.back();

    // read "rule" that triggered the report
    const auto rule = valueOf<std::string>(defNode, "ruleId");
    if (!rule.empty()) {
        boost::smatch sm;
        if (boost::regex_match(rule, sm, d->reRuleId)) {
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
        const auto it = d->cweMap.find(rule);
        if (d->cweMap.end() != it)
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

    expandRelativePaths(def, d->pwd);
    d->digger.inferLangFromChecker(def);
    d->digger.inferToolFromChecker(def);

    return true;
}
