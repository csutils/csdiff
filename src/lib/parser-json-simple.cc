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

#include "parser-json-simple.hh"

#include "abstract-tree.hh"         // for findChildOf()
#include "parser-cov.hh"            // for KeyEventDigger

#include <set>

struct SimpleTreeDecoder::Private {
    enum ENodeKind {
        NK_DEFECT,
        NK_EVENT,
        NK_LAST
    };

    void reportUnknownNodes(ENodeKind, const pt::ptree &) const;

    typedef std::set<std::string>       TNodeSet;
    typedef std::vector<TNodeSet>       TNodeStore;

    InStream                   &input;
    TNodeStore                  nodeStore;
    KeyEventDigger              keDigger;

    Private(InStream &input);
};

SimpleTreeDecoder::Private::Private(InStream &input):
    input(input)
{
    if (input.silent())
        // skip initialization of nodeStore_ because no lookup will ever happen
        return;

    this->nodeStore.resize(NK_LAST);

    // known per-defect subnodes
    this->nodeStore[NK_DEFECT] = {
        "annotation",
        "checker",
        "cwe",
        "defect_id",
        "events",
        "function",
        "imp",
        "key_event_idx",
        "language",
        "tool",
    };

    // known per-event subnodes
    this->nodeStore[NK_EVENT] = {
        "column",
        "event",
        "file_name",
        "line",
        "message",
        "verbosity_level",
    };
}

void SimpleTreeDecoder::Private::reportUnknownNodes(
        const ENodeKind             nk,
        const pt::ptree            &node)
    const
{
    if (this->input.silent())
        return;

    const TNodeSet &nodeSet = this->nodeStore[nk];

    for (const pt::ptree::value_type &item : node) {
        const std::string &name = item.first;
        if (nodeSet.end() == nodeSet.find(name))
            std::cerr << this->input.fileName()
                << ": warning: unknown JSON node: " << name
                << std::endl;
    }
}

SimpleTreeDecoder::SimpleTreeDecoder(InStream &input):
    d(new Private(input))
{
}

SimpleTreeDecoder::~SimpleTreeDecoder() = default;

void SimpleTreeDecoder::readScanProps(
        TScanProps                 *pDst,
        const pt::ptree            *root)
{
    const pt::ptree *scanNode;
    if (findChildOf(&scanNode, *root, "scan"))
        for (const pt::ptree::value_type &item : *scanNode)
            (*pDst)[item.first] = item.second.data();
}

bool SimpleTreeDecoder::readNode(Defect *def)
{
    // move the iterator after we get the current position
    const pt::ptree *pNode = this->nextNode();
    if (!pNode)
        // failed initialization or EOF
        return false;

    const pt::ptree &defNode = *pNode;

    d->reportUnknownNodes(Private::NK_DEFECT, defNode);

    // the checker field is mandatory
    def->checker = defNode.get<std::string>("checker");

    bool verbosityLevelNeedsInit = false;

    // read the events
    TEvtList &evtListDst = def->events;
    const pt::ptree &evtListSrc = defNode.get_child("events");
    for (const pt::ptree::value_type &evtItem : evtListSrc) {
        const pt::ptree &evtNode = evtItem.second;
        d->reportUnknownNodes(Private::NK_EVENT, evtNode);

        DefEvent evt;
        evt.fileName    = valueOf<std::string   >(evtNode, "file_name");
        evt.line        = valueOf<int           >(evtNode, "line");
        evt.column      = valueOf<int           >(evtNode, "column");
        evt.event       = valueOf<std::string   >(evtNode, "event");
        evt.msg         = valueOf<std::string   >(evtNode, "message");
        evt.verbosityLevel = valueOf<int>(evtNode, "verbosity_level", -1);
        if (-1 == evt.verbosityLevel)
            verbosityLevelNeedsInit = true;

        evtListDst.push_back(evt);
    }

    // read "defect_id", "cwe", and "function" if available
    def->defectId = valueOf<int>        (defNode, "defect_id");
    def->cwe      = valueOf<int>        (defNode, "cwe");
    def->imp      = valueOf<int>        (defNode, "imp");
    def->function = valueOf<std::string>(defNode, "function");
    def->language = valueOf<std::string>(defNode, "language");
    def->tool     = valueOf<std::string>(defNode, "tool");

    if (defNode.not_found() == defNode.find("key_event_idx")) {
        // key event not specified, try to guess it
        if (!d->keDigger.guessKeyEvent(def))
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
        d->keDigger.initVerbosity(def);

    // read annotation if available
    def->annotation = valueOf<std::string>(defNode, "annotation");

    return true;
}

