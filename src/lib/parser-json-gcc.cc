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

#include "parser-json-gcc.hh"

#include "parser-gcc.hh"            // for GccPostProcessor

using std::string;

struct GccTreeDecoder::Private {
    GccPostProcessor            postProc;
};

GccTreeDecoder::GccTreeDecoder():
    d(new Private)
{
}

GccTreeDecoder::~GccTreeDecoder() = default;

static bool gccReadLocRegion(
        DefEvent           *pEvt,
        const pt::ptree    &start,
        const pt::ptree    &finish)
{
    // read file name
    pEvt->fileName = valueOf<string>(start, "file", "<unknown>");
    if (pEvt->fileName != valueOf<string>(finish, "file", "<unknown>"))
        return false;

    // read line
    if ((pEvt->line = valueOf<int>(start, "line"))) {
        const int endLine = valueOf<int>(finish, "line");
        pEvt->vSize = diffNums(pEvt->line, endLine);
    }

    // read column
    if ((pEvt->column = valueOf<int>(start, "byte-column"))) {
        const int endColumn = valueOf<int>(finish, "byte-column");
        pEvt->hSize = diffNums(pEvt->column, endColumn);
    }

    return true;
}

static void gccReadLocation(DefEvent *pEvt, const pt::ptree *locs)
{
    if (locs->empty())
        return;

    const pt::ptree &firstLoc = locs->begin()->second;

    // try to read a region between start..finish
    const pt::ptree *start, *finish;
    if (findChildOf(&start, firstLoc, "start")
            && findChildOf(&finish, firstLoc, "finish")
            && gccReadLocRegion(pEvt, *start, *finish))
        return;

    // fallback to caret
    const pt::ptree *caret;
    if (findChildOf(&caret, firstLoc, "caret")) {
        pEvt->fileName  = valueOf<string>(*caret, "file", "<unknown>");
        pEvt->line      = valueOf<int>   (*caret, "line");
        pEvt->column    = valueOf<int>   (*caret, "byte-column");
    }
}

static bool gccReadEvent(DefEvent *pEvt, const pt::ptree &evtNode)
{
    // read kind (error, warning, note)
    string &evtName = pEvt->event;
    evtName = valueOf<string>(evtNode, "kind");
    if (evtName.empty())
        return false;

    // read location
    pEvt->fileName = "<unknown>";
    const pt::ptree *locs;
    if (findChildOf(&locs, evtNode, "locations"))
        gccReadLocation(pEvt, locs);

    // read message
    pEvt->msg = valueOf<string>(evtNode, "message", "<unknown>");

    // read -W... if available
    const string option = valueOf<string>(evtNode, "option");
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
        def->cwe = valueOf<int>(*meta, "cwe");

    // apply post-processing rules
    d->postProc.apply(def);

    return true;
}
