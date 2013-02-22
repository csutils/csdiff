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

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>

// suppress strict-aliasing warnings in <boost/optional/optional.hpp> coming
// with gcc-4.4.x <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=41874>
#if defined(__GNUC_MINOR__) && (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#   pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

namespace pt = boost::property_tree;

struct JsonParser::Private {
    const std::string               fileName;
    const bool                      silent;
    bool                            jsonValid;
    bool                            hasError;
    pt::ptree                       defList;
    pt::ptree::const_iterator       defIter;
    int                             defNumber;
    TScanProps                      scanProps;

    Private(const std::string &fileName_, bool silent_):
        fileName(fileName_),
        silent(silent_),
        jsonValid(false),
        hasError(false),
        defNumber(-1)
    {
    }

    void parseError(const std::string &msg, unsigned long line = 0UL);
    void dataError(const std::string &msg);
    void readNode(Defect *def, const pt::ptree &defNode);
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

JsonParser::JsonParser(
        std::istream                &input,
        const std::string           &fileName,
        const bool                   silent):
    d(new Private(fileName, silent))
{
    try {
        // parse JSON
        pt::ptree root;
        read_json(input, root);

        // get the defect list
        d->defList = root.get_child("defects");
        d->defIter = d->defList.begin();
        d->jsonValid = true;

        // read scan properties if available
        pt::ptree emp;
        pt::ptree scanNode = root.get_child_optional("scan").get_value_or(emp);
        BOOST_FOREACH(const pt::ptree::value_type &item, scanNode)
            d->scanProps[item.first] = item.second.data();
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

void JsonParser::Private::readNode(
        Defect                      *def,
        const pt::ptree             &defNode)
{
    // make sure the Defect structure is properly initialized
    (*def) = Defect();

    // the checker field is mandatory
    def->checker = defNode.get<std::string>("checker");

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

        evtListDst.push_back(evt);
    }

    // read "defect_id", "cwe", and "function" if available
    def->defectId = valueOf<int>        (defNode, "defect_id", 0);
    def->cwe      = valueOf<int>        (defNode, "cwe"      , 0);
    def->function = valueOf<std::string>(defNode, "function", "");

    // assume the last event is the key event if not specified otherwise
    const int cntEvents = evtListDst.size();
    int defKeyEvent = cntEvents - 1;
    defKeyEvent = valueOf<int>(defNode, "key_event_idx", defKeyEvent);
    if (0 <= defKeyEvent && defKeyEvent < cntEvents)
        def->keyEventIdx = defKeyEvent;
    else
        throw pt::ptree_error("key event out of range");

    // read annotation if available
    def->annotation = valueOf<std::string>(defNode, "annotation", "");
}

bool JsonParser::Private::readNext(Defect *def) {
    try {
        // get the current node and move to the next one
        const pt::ptree &defNode = this->defIter->second;
        this->defIter++;
        this->defNumber++;

        // read the current node
        this->readNode(def, defNode);
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
        if (d->defList.end() == d->defIter)
            return false;

        if (d->readNext(def))
            return true;
    }
}
