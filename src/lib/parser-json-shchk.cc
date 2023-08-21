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

#include "parser-json-shchk.hh"

#include "parser-gcc.hh"            // for GccPostProcessor

struct ShellCheckTreeDecoder::Private {
    GccPostProcessor            postProc;
};

ShellCheckTreeDecoder::ShellCheckTreeDecoder():
    d(new Private)
{
}

ShellCheckTreeDecoder::~ShellCheckTreeDecoder() = default;

static bool scReadEvent(DefEvent *pEvt, const pt::ptree &evtNode)
{
    using std::string;

    // read level (error, warning, note)
    string &evtName = pEvt->event;
    evtName = valueOf<string>(evtNode, "level");
    if (evtName.empty())
        return false;

    // read location
    pEvt->fileName = valueOf<string>(evtNode, "file", "<unknown>");
    pEvt->line     = valueOf<int>   (evtNode, "line");
    pEvt->column   = valueOf<int>   (evtNode, "column");

    // read message
    pEvt->msg = valueOf<string>(evtNode, "message", "<unknown>");

    // append [SC...] if available
    const string code = valueOf<string>(evtNode, "code");
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
    d->postProc.apply(def);

    return true;
}
