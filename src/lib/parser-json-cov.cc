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

#include "parser-json-cov.hh"

#include "parser-cov.hh"            // for KeyEventDigger

struct CovTreeDecoder::Private {
    KeyEventDigger              keDigger;
};

CovTreeDecoder::CovTreeDecoder():
    d(new Private)
{
}

CovTreeDecoder::~CovTreeDecoder() = default;

bool CovTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    const pt::ptree *pNode = this->nextNode();
    if (!pNode)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *pNode;

    // read per-defect properties
    def->checker = defNode.get<std::string>("checkerName");
    def->function = valueOf<std::string>(defNode, "functionDisplayName");
    def->language = valueOf<std::string>(defNode, "code-language");

    // out of the supported tools, only Coverity produces this data format
    def->tool = "coverity";

    // read CWE if available
    const pt::ptree *checkerProps;
    if (findChildOf(&checkerProps, defNode, "checkerProperties"))
        def->cwe = valueOf<int>(*checkerProps, "cweCategory");

    // count the events and allocate dst array
    const pt::ptree &evtList = defNode.get_child("events");
    def->events.resize(evtList.size());

    // decode events one by one
    unsigned idx = 0;
    pt::ptree::const_iterator it;
    for (it = evtList.begin(); it != evtList.end(); ++it, ++idx) {
        const pt::ptree &evtNode = it->second;
        DefEvent &evt = def->events[idx];

        evt.fileName    = valueOf<std::string>(evtNode, "filePathname");
        evt.line        = valueOf<int>        (evtNode, "lineNumber");
        // TODO: read column?
        evt.event       = valueOf<std::string>(evtNode, "eventTag");
        evt.msg         = valueOf<std::string>(evtNode, "eventDescription");

        if (evtNode.get<bool>("main"))
            // this is a key event
            // TODO: detect and report re-definitions of key events
            def->keyEventIdx = idx;
    }

    // initialize verbosity level of all events
    d->keDigger.initVerbosity(def);

    return true;
}

