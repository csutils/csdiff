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

#include <stack>

struct CovTreeDecoder::Private {
    KeyEventDigger              keDigger;
    InStream                   &input;
    const pt::ptree            *pSrc;

    Private(InStream &input_):
        input(input_)
    {
    }

    void readEvents(Defect *def);
};

CovTreeDecoder::CovTreeDecoder(InStream &input):
    d(new Private(input))
{
}

CovTreeDecoder::~CovTreeDecoder() = default;

/// decode single event
static DefEvent covDecodeEvt(const pt::ptree &evtNode)
{
    DefEvent evt;

    evt.fileName    = valueOf<std::string>(evtNode, "filePathname");
    evt.line        = valueOf<int>        (evtNode, "lineNumber");
    evt.column      = valueOf<int>        (evtNode, "columnNumber");
    evt.event       = valueOf<std::string>(evtNode, "eventTag");
    evt.msg         = valueOf<std::string>(evtNode, "eventDescription");

    return evt;
}

struct CovEvtStackItem {
    const pt::ptree             &evts;
    pt::ptree::const_iterator    iter;

    CovEvtStackItem(const pt::ptree &evts_):
        evts(evts_),
        iter(evts_.begin())
    {
    }
};

void CovTreeDecoder::Private::readEvents(Defect *def)
{
    // stack to traverse events recursively (without recursive fnc call)
    std::stack<CovEvtStackItem> todo;
    todo.push(this->pSrc->get_child("events"));

    do {
        CovEvtStackItem &si = todo.top();
        if (si.evts.end() == si.iter) {
            // no more events at this level to iterate through
            todo.pop();
            continue;
        }

        // get current event and move to the next one
        const pt::ptree &evtNode = (si.iter++)->second;

        if (evtNode.get<bool>("main")) {
            // this is a key event

            if (def->keyEventIdx)
                // key event redefinition (TODO: more detailed diagnostic msg)
                std::cerr << this->input.fileName()
                    << ": warning: key event redefinition detected"
                    << std::endl;

            // record key event index
            def->keyEventIdx = def->events.size();
        }

        // push the event to the list of events
        DefEvent evt = covDecodeEvt(evtNode);
        def->events.push_back(std::move(evt));
    }
    while (!todo.empty());
}

bool CovTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    d->pSrc = this->nextNode();
    if (!d->pSrc)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *d->pSrc;

    // read per-defect properties
    def->checker = defNode.get<std::string>("checkerName");
    def->function = valueOf<std::string>(defNode, "functionDisplayName");
    def->language = valueOf<std::string>(defNode, "code-language");

    // out of the supported tools, only Coverity produces this data format
    def->tool = "coverity";

    // extract checker properties if available
    const pt::ptree *checkerProps;
    if (findChildOf(&checkerProps, defNode, "checkerProperties")) {
        // read CWE if available
        def->cwe = valueOf<int>(*checkerProps, "cweCategory");

        // treat defects with high impact as important
        if ("High" == valueOf<std::string>(*checkerProps, "impact"))
            def->imp = 1;
    }

    // read all events
    d->readEvents(def);

    // initialize verbosity level of all events
    d->keDigger.initVerbosity(def);

    return true;
}
