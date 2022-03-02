/*
 * Copyright (C) 2011-2021 Red Hat, Inc.
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

#include "json-parser.hh"

#include "abstract-tree.hh"
#include "csparser.hh"              // for KeyEventDigger

#include <set>

#include <boost/property_tree/json_parser.hpp>

/// tree decoder of the native JSON format of csdiff
class SimpleTreeDecoder: public AbstractTreeDecoder {
    public:
        SimpleTreeDecoder(InStream &input);

        virtual void readScanProps(
                TScanProps             *pDst,
                const pt::ptree        *root);

        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter);

    private:
        enum ENodeKind {
            NK_DEFECT,
            NK_EVENT,
            NK_LAST
        };

        void reportUnknownNodes(ENodeKind, const pt::ptree &) const;

        typedef std::set<std::string>       TNodeSet;
        typedef std::vector<TNodeSet>       TNodeStore;

        const std::string           fileName_;
        const bool                  silent_;
        TNodeStore                  nodeStore_;
        KeyEventDigger              keDigger_;
};

/// tree decoder of the Coverity JSON format
class CovTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter);

    private:
        KeyEventDigger              keDigger;
};

/// tree decoder of the JSON format produced by Snyk Code
class SnykTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual void readScanProps(
                TScanProps             *pDst,
                const pt::ptree        *root);

        virtual void readRoot(
                const pt::ptree       **pDefList,
                const pt::ptree        *root);

        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter);
};

struct JsonParser::Private {
    InStream                       &input;
    AbstractTreeDecoder            *decoder = nullptr;
    pt::ptree                       root;
    const pt::ptree                *defList = nullptr;
    pt::ptree::const_iterator       defIter;
    int                             defNumber = 0;
    TScanProps                      scanProps;

    Private(InStream &input):
        input(input)
    {
    }

    ~Private()
    {
        delete this->decoder;
    }

    void dataError(const std::string &msg);
    bool readNext(Defect *def);
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

        // recognize inner format of the JSON document
        pt::ptree *node = nullptr;
        if (findChildOf(&node, d->root, "defects"))
            // csdiff-native JSON format
            d->decoder = new SimpleTreeDecoder(d->input);
        else if (findChildOf(&node, d->root, "issues"))
            // Coverity JSON format
            d->decoder = new CovTreeDecoder;
        else if (findChildOf(&node, d->root, "runs"))
            // JSON format produced by Snyk Code
            d->decoder = new SnykTreeDecoder;
        else
            throw pt::ptree_error("unknown JSON format");

        // read scan properties if available
        d->decoder->readScanProps(&d->scanProps, &d->root);

        // process the root node
        d->decoder->readRoot(&d->defList, node);

        // initialize the traversal through the list of defects/issues
        if (d->defList)
            d->defIter = d->defList->begin();
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

JsonParser::~JsonParser()
{
    delete d;
}

bool JsonParser::hasError() const
{
    return d->input.anyError();
}

const TScanProps& JsonParser::getScanProps() const
{
    return d->scanProps;
}

bool JsonParser::Private::readNext(Defect *def)
{
    try {
        // make sure the Defect structure is properly initialized
        (*def) = Defect();

        // read the current node and move to the next one
        this->defNumber++;
        return this->decoder->readNode(def, this->defIter++);
    }
    catch (pt::ptree_error &e) {
        this->dataError(e.what());
        return false;
    }
}

bool JsonParser::getNext(Defect *def)
{
    if (!d->defList)
        return false;

    // error recovery loop
    for (;;) {
        if (d->defList->end() == d->defIter)
            return false;

        if (d->readNext(def))
            return true;
    }
}

SimpleTreeDecoder::SimpleTreeDecoder(InStream &input):
    fileName_(input.fileName()),
    silent_(input.silent())
{
    if (silent_)
        // skip initialization of nodeStore_ because no lookup will ever happen
        return;

    nodeStore_.resize(NK_LAST);

    // known per-defect subnodes
    nodeStore_[NK_DEFECT] = {
        "annotation",
        "checker",
        "cwe",
        "defect_id",
        "events",
        "function",
        "imp",
        "key_event_idx",
        "language",
    };

    // known per-event subnodes
    nodeStore_[NK_EVENT] = {
        "column",
        "event",
        "file_name",
        "line",
        "message",
        "verbosity_level",
    };
}

void SimpleTreeDecoder::reportUnknownNodes(ENodeKind nk, const pt::ptree &node)
    const
{
    if (silent_)
        return;

    const TNodeSet &nodeSet = nodeStore_[nk];

    for (const pt::ptree::value_type &item : node) {
        const std::string &name = item.first;
        if (nodeSet.end() == nodeSet.find(name))
            std::cerr << fileName_
                << ": warning: unknown JSON node: " << name
                << std::endl;
    }
}

void SimpleTreeDecoder::readScanProps(
        TScanProps                 *pDst,
        const pt::ptree            *root)
{
    const pt::ptree emp;
    const pt::ptree &scanNode =
        root->get_child_optional("scan").get_value_or(emp);

    for (const pt::ptree::value_type &item : scanNode)
        (*pDst)[item.first] = item.second.data();
}

bool SimpleTreeDecoder::readNode(
        Defect                      *def,
        pt::ptree::const_iterator    defIter)
{
    const pt::ptree &defNode = defIter->second;

    this->reportUnknownNodes(NK_DEFECT, defNode);

    // the checker field is mandatory
    def->checker = defNode.get<std::string>("checker");

    bool verbosityLevelNeedsInit = false;

    // read the events
    TEvtList &evtListDst = def->events;
    const pt::ptree &evtListSrc = defNode.get_child("events");
    for (const pt::ptree::value_type &evtItem : evtListSrc) {
        const pt::ptree &evtNode = evtItem.second;
        this->reportUnknownNodes(NK_EVENT, evtNode);

        DefEvent evt;
        evt.fileName    = valueOf<std::string   >(evtNode, "file_name"  , "");
        evt.line        = valueOf<int           >(evtNode, "line"       , 0);
        evt.column      = valueOf<int           >(evtNode, "column"     , 0);
        evt.event       = valueOf<std::string   >(evtNode, "event"      , "");
        evt.msg         = valueOf<std::string   >(evtNode, "message"    , "");
        evt.verbosityLevel = valueOf<int>(evtNode, "verbosity_level"    , -1);
        if (-1 == evt.verbosityLevel)
            verbosityLevelNeedsInit = true;

        evtListDst.push_back(evt);
    }

    // read "defect_id", "cwe", and "function" if available
    def->defectId = valueOf<int>        (defNode, "defect_id", 0);
    def->cwe      = valueOf<int>        (defNode, "cwe"      , 0);
    def->imp      = valueOf<int>        (defNode, "imp"      , 0);
    def->function = valueOf<std::string>(defNode, "function", "");
    def->language = valueOf<std::string>(defNode, "language", "");

    if (defNode.not_found() == defNode.find("key_event_idx")) {
        // key event not specified, try to guess it
        if (!keDigger_.guessKeyEvent(def))
            throw pt::ptree_error("failed to guess key event");
    }
    else {
        // use the provided key_event_idx unless it is out of range
        const int cntEvents = evtListDst.size();
        const int defKeyEvent = defNode.get<int>("key_event_idx");
        if (0 <= defKeyEvent && defKeyEvent < cntEvents)
            def->keyEventIdx = defKeyEvent;
        else
            throw pt::ptree_error("key event out of range");
    }

    if (verbosityLevelNeedsInit)
        // missing or incomplete verbosity_level, initialize it over
        keDigger_.initVerbosity(def);

    // read annotation if available
    def->annotation = valueOf<std::string>(defNode, "annotation", "");

    return true;
}

bool CovTreeDecoder::readNode(
        Defect                      *def,
        pt::ptree::const_iterator    defIter)
{
    const pt::ptree &defNode = defIter->second;

    // read per-defect properties
    def->checker = defNode.get<std::string>("checkerName");
    def->function = valueOf<std::string>(defNode, "functionDisplayName", "");
    def->language = valueOf<std::string>(defNode, "code-language", "");

    // read CWE if available
    const pt::ptree *checkerProps;
    if (findChildOf(&checkerProps, defNode, "checkerProperties"))
        def->cwe = valueOf<int>(*checkerProps, "cweCategory", 0);

    // count the events and allocate dst array
    const pt::ptree &evtList = defNode.get_child("events");
    def->events.resize(evtList.size());

    // decode events one by one
    unsigned idx = 0;
    pt::ptree::const_iterator it;
    for (it = evtList.begin(); it != evtList.end(); ++it, ++idx) {
        const pt::ptree &evtNode = it->second;
        DefEvent &evt = def->events[idx];

        evt.fileName    = valueOf<std::string>(evtNode, "filePathname"    , "");
        evt.line        = valueOf<int>        (evtNode, "lineNumber"      , 0 );
        // TODO: read column?
        evt.event       = valueOf<std::string>(evtNode, "eventTag"        , "");
        evt.msg         = valueOf<std::string>(evtNode, "eventDescription", "");

        if (evtNode.get<bool>("main"))
            // this is a key event
            // TODO: detect and report re-definitions of key events
            def->keyEventIdx = idx;
    }

    // initialize verbosity level of all events
    this->keDigger.initVerbosity(def);

    return true;
}

void SnykTreeDecoder::readScanProps(
        TScanProps                 *pDst,
        const pt::ptree            *root)
{
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

    const auto name = valueOf<std::string>(*driverNode, "name", "");
    if (name != "SnykCode")
        // not a supported tool
        return;

    const auto version = valueOf<std::string>(*driverNode, "version", "");
    if (version.empty())
        // no version provided
        return;

    // record tool version of Snyk Code
    (*pDst)["analyzer-version-snyk-code"] = version;
}

void SnykTreeDecoder::readRoot(
        const pt::ptree           **pDefList,
        const pt::ptree            *runs)
{
    // check that we have exactly one run and return its results
    if ((1U != runs->size())
            || !findChildOf(pDefList, runs->begin()->second, "results"))
        pDefList = nullptr;
}

void snykReadLocation(DefEvent *pEvt, const pt::ptree &defNode)
{
    const pt::ptree *locs;
    if (!findChildOf(&locs, defNode, "locations") || locs->empty())
        // no location info available
        return;

    const pt::ptree *pl;
    if (!findChildOf(&pl, locs->begin()->second, "physicalLocation"))
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

bool SnykTreeDecoder::readNode(
        Defect                      *def,
        pt::ptree::const_iterator    defIter)
{
    // initialize the defect structure
    *def = Defect("SNYK_CODE_WARNING");

    // the current node representing a single snyk's report
    const pt::ptree &defNode = defIter->second;

    // initialize the key event
    const auto level = valueOf<std::string>(defNode, "level", "warning");
    def->events.push_back(DefEvent(level));
    DefEvent &keyEvent = def->events.back();

    // read "rule" that triggered the report
    const auto rule = valueOf<std::string>(defNode, "ruleId", "");
    if (!rule.empty())
        keyEvent.event += "[" + rule + "]";

    // read location
    keyEvent.fileName = "<unknown>";
    snykReadLocation(&keyEvent, defNode);

    // read diagnostic message
    const pt::ptree *msgNode;
    if (findChildOf(&msgNode, defNode, "message"))
        keyEvent.msg = valueOf<std::string>(*msgNode, "text", "<unknown>");

    return true;
}
