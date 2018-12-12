/*
 * Copyright (C) 2011-2012 Red Hat, Inc.
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

#include "csparser.hh"              // for KeyEventDigger

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

// suppress strict-aliasing warnings in <boost/optional/optional.hpp> coming
// with gcc-4.4.x <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=41874>
#if defined(__GNUC_MINOR__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#   pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

namespace pt = boost::property_tree;

/// abstraction for higher-level decoders for various JSON-based tree formats
class AbstractTreeDecoder {
    public:
        virtual ~AbstractTreeDecoder() { }

        /// read the given ptree node, decode, and store the result into def
        virtual void readNode(Defect *def, const pt::ptree &node) = 0;
};

/// tree decoder of the native JSON format of csdiff
class SimpleTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual void readNode(Defect *def, const pt::ptree &node);

    private:
        KeyEventDigger              keDigger;
};

/// tree decoder of the Coverity JSON format
class CovTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual void readNode(Defect *def, const pt::ptree &node);

    private:
        KeyEventDigger              keDigger;
};

struct JsonParser::Private {
    const std::string               fileName;
    const bool                      silent;
    bool                            jsonValid;
    bool                            hasError;
    AbstractTreeDecoder            *decoder;
    pt::ptree                       root;
    pt::ptree                      *defList;
    pt::ptree::const_iterator       defIter;
    int                             defNumber;
    TScanProps                      scanProps;

    Private(const std::string &fileName_, bool silent_):
        fileName(fileName_),
        silent(silent_),
        jsonValid(false),
        hasError(false),
        decoder(0),
        defNumber(0)
    {
    }

    ~Private()
    {
        delete this->decoder;
    }

    void parseError(const std::string &msg, unsigned long line = 0UL);
    void dataError(const std::string &msg);
    bool readNext(Defect *def);
};

void JsonParser::Private::parseError(const std::string &msg, unsigned long line)
{
    this->hasError = true;
    if (this->silent)
        return;

    std::cerr << this->fileName;

    if (line)
        // line number available
        std::cerr << ":" << line;

    std::cerr << ": parse error: " << msg << "\n";
}

void JsonParser::Private::dataError(const std::string &msg) {
    this->hasError = true;
    if (this->silent)
        return;

    std::cerr
        << this->fileName << ": error: failed to read defect #"
        << this->defNumber << ": " << msg << "\n";
}

bool findChildOf(pt::ptree **pDst, pt::ptree &node, const char *key)
{
    if (node.not_found() == node.find(key))
        return false;

    *pDst = &node.get_child(key);
    return true;
}

JsonParser::JsonParser(
        std::istream                &input,
        const std::string           &fileName,
        const bool                   silent):
    d(new Private(fileName, silent))
{
    try {
        // parse JSON
        read_json(input, d->root);

        // read scan properties if available (csdiff-native JSON format only)
        pt::ptree emp;
        pt::ptree scanNode =
            d->root.get_child_optional("scan").get_value_or(emp);
        BOOST_FOREACH(const pt::ptree::value_type &item, scanNode)
            d->scanProps[item.first] = item.second.data();

        if (findChildOf(&d->defList, d->root, "defects"))
            // csdiff-native JSON format
            d->decoder = new SimpleTreeDecoder;
        else if (findChildOf(&d->defList, d->root, "issues"))
            // Coverity JSON format
            d->decoder = new CovTreeDecoder;
        else
            throw pt::ptree_error("unknown JSON format");

        // initialize the traversal through the list of defects/issues
        d->defIter = d->defList->begin();
        d->jsonValid = true;
    }
    catch (pt::file_parser_error &e) {
        d->parseError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->parseError(e.what());
    }
}

JsonParser::~JsonParser() {
    delete d;
}

bool JsonParser::hasError() const {
    return d->hasError;
}

const TScanProps& JsonParser::getScanProps() const {
    return d->scanProps;
}

template <typename T>
inline T valueOf(const pt::ptree &node, const char *path, const T &defVal)
{
    const boost::optional<T> &opt = node.get_optional<T>(path);
    return opt.get_value_or(defVal);
}

bool JsonParser::Private::readNext(Defect *def) {
    try {
        // get the current node and move to the next one
        const pt::ptree &defNode = this->defIter->second;
        this->defIter++;
        this->defNumber++;

        // read the current node
        this->decoder->readNode(def, defNode);
        return true;
    }
    catch (pt::ptree_error &e) {
        this->dataError(e.what());
        return false;
    }
}

bool JsonParser::getNext(Defect *def) {
    if (!d->jsonValid)
        return false;

    // error recovery loop
    for (;;) {
        if (d->defList->end() == d->defIter)
            return false;

        if (d->readNext(def))
            return true;
    }
}

void SimpleTreeDecoder::readNode(
        Defect                      *def,
        const pt::ptree             &defNode)
{
    // make sure the Defect structure is properly initialized
    (*def) = Defect();

    // the checker field is mandatory
    def->checker = defNode.get<std::string>("checker");

    bool verbosityLevelNeedsInit = false;

    // read the events
    TEvtList &evtListDst = def->events;
    const pt::ptree &evtListSrc = defNode.get_child("events");
    BOOST_FOREACH(const pt::ptree::value_type &evtItem, evtListSrc) {
        const pt::ptree &evtNode = evtItem.second;

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
    def->function = valueOf<std::string>(defNode, "function", "");

    if (defNode.not_found() == defNode.find("key_event_idx")) {
        // key event not specified, try to guess it
        if (!this->keDigger.guessKeyEvent(def))
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
        this->keDigger.initVerbosity(def);

    // read annotation if available
    def->annotation = valueOf<std::string>(defNode, "annotation", "");
}

void CovTreeDecoder::readNode(
        Defect                      *def,
        const pt::ptree             &defNode)
{
    // make sure the Defect structure is properly initialized
    (*def) = Defect();

    // read per-defect properties
    // TODO: read/propagate more properties from the Coverity JSON format
    def->checker = defNode.get<std::string>("checkerName");
    def->function = valueOf<std::string>(defNode, "functionDisplayName", "");

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
}
