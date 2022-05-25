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

#include "abstract-filter.hh"

#include "instream.hh"

#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>

#include <boost/algorithm/string/replace.hpp>

// /////////////////////////////////////////////////////////////////////////////
// implementation of PredicateFilter

struct PredicateFilter::Private {
    using IPredicatePtr = std::unique_ptr<IPredicate>;
    using TList         = std::vector<IPredicatePtr>;

    bool                invertEach_ = false;
    TList               preds_;

    Private()
    {
    }
};

PredicateFilter::PredicateFilter(AbstractWriter *agent):
    AbstractFilter(agent),
    d(new Private)
{
}

PredicateFilter::~PredicateFilter() = default;

void PredicateFilter::append(IPredicate *pred)
{
    d->preds_.emplace_back(pred);
}

void PredicateFilter::setInvertEachMatch(bool enabled)
{
    d->invertEach_ = enabled;
}

bool PredicateFilter::matchDef(const Defect &def)
{
    const bool neg = d->invertEach_;

    for (const auto &pred : d->preds_) {
        if (neg == pred->matchDef(def))
            return false;
    }

    return true;
}


// /////////////////////////////////////////////////////////////////////////////
// implementation of EventPrunner

void EventPrunner::handleDef(const Defect &defOrig)
{
    Defect def(defOrig);
    def.events.clear();

    const unsigned cnt = defOrig.events.size();
    for (unsigned i = 0; i < cnt; ++i) {
        const DefEvent &evt = defOrig.events[i];

        if (evt.verbosityLevel <= thr_)
            def.events.push_back(evt);
        else if (i < defOrig.keyEventIdx)
            def.keyEventIdx--;
    }

    agent_->handleDef(def);
}


// /////////////////////////////////////////////////////////////////////////////
// implementation of CtxEmbedder

void dropCtxLines(TEvtList *pEvtList)
{
    static CtxEventDetector detector;

    TEvtList dst;
    for (const DefEvent &evt : *pEvtList) {
        if (detector.isAnyCtxLine(evt))
            continue;

        dst.push_back(evt);
    }

    pEvtList->swap(dst);
}

void appendCtxLines(
        TEvtList       *pDst,
        std::istream   &inStr,
        const int       defLine,
        const int       ctxLines)
{
    if (ctxLines < 0)
        return;

    const int firstLine = defLine - ctxLines;
    const int lastLine  = defLine + ctxLines;

    int line = 1;
    std::string text;
    for (; line <= lastLine; ++line) {
        if (!std::getline(inStr, text))
            // premature end of input
            break;

        if (line < firstLine)
            // skip lines before the context lines
            continue;

        // quote embedded NULs as they cause problems to some JSON parsers
        std::string nul;
        nul.push_back('\0');
        boost::algorithm::replace_all(text, nul, "[NUL]");

        // format a single line of the comment
        std::ostringstream str;
        str << std::fixed << std::setw(5) << line;
        if (defLine == line)
            str << "|-> ";
        else
            str << "|   ";
        str << text;

        // append the comment as a new event
        DefEvent evt;
        evt.event = "#";
        evt.msg = str.str();
        evt.verbosityLevel = /* not a key event */ 1;
        pDst->push_back(evt);
    }
}

void CtxEmbedder::handleDef(const Defect &defOrig)
{
    const DefEvent &evt = defOrig.events[defOrig.keyEventIdx];
    if (!evt.line) {
        // no line number for the key event
        agent_->handleDef(defOrig);
        return;
    }

    std::ifstream fstr(evt.fileName);
    if (!fstr) {
        // failed to open input file
        agent_->handleDef(defOrig);
        return;
    }

    // clone defOrig and append the context lines
    Defect def(defOrig);
    dropCtxLines(&def.events);
    appendCtxLines(&def.events, fstr, evt.line, ctxLines_ - 1);

    // close the file stream and forward the result
    fstr.close();
    agent_->handleDef(def);
}
