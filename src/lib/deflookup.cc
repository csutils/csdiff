/*
 * Copyright (C) 2011-2023 Red Hat, Inc.
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

#include "deflookup.hh"

#include "finger-print.hh"
#include "msg-filter.hh"
#include "parser.hh"

#include <cassert>
#include <map>

typedef std::vector<Defect>                     TDefList;
typedef std::map<std::string, TDefList>         TDefByMsg;
typedef std::map<std::string, TDefByMsg>        TDefByEvt;
typedef std::map<std::string, TDefByEvt>        TDefByFile;
typedef std::map<std::string, TDefByFile>       TDefByChecker;

struct DefLookup::Private {
    TDefByChecker                    byChecker;
    bool                             usePartialResults;
};

DefLookup::DefLookup(const bool usePartialResults):
    d(new Private)
{
    d->usePartialResults = usePartialResults;
}

DefLookup::DefLookup(const DefLookup &ref):
    d(new Private(*ref.d))
{
}

DefLookup& DefLookup::operator=(const DefLookup &ref)
{
    if (&ref == this)
        return *this;

    delete d;
    d = new Private(*ref.d);
    return *this;
}

DefLookup::~DefLookup()
{
    delete d;
}

void DefLookup::hashDefect(const Defect &def)
{
    // categorize by checker
    TDefByFile &byPath = d->byChecker[def.checker];

    // categorize by path
    const DefEvent &evt = def.events[def.keyEventIdx];
    const MsgFilter &filter = MsgFilter::inst();
    TDefByEvt &byEvt = byPath[filter.filterPath(evt.fileName)];

    // categorize by key event and msg
    TDefByMsg &byMsg = byEvt[evt.event];
    TDefList &defList = byMsg[filter.filterMsg(evt.msg, def.checker)];

    defList.push_back(def);
}

static bool defLookupCore(TDefList &defList, const Defect &lookFor)
{
    // look by line content without spaces if available
    const std::string lineCont = FingerPrinter(lookFor).getLineContent();
    if (!lineCont.empty()) {
        bool fullLineContCoverage = true;

        for (auto it = defList.begin(); it != defList.end(); ++it) {
            const std::string lineContNow = FingerPrinter(*it).getLineContent();
            if (lineContNow.empty())
                fullLineContCoverage = false;
            else if (lineCont == lineContNow) {
                // matched by line content without spaces
                defList.erase(it);
                return true;
            }
        }

        if (fullLineContCoverage)
            // we had line content for all lines but none of them matched
            return false;
    }

    // just remove an arbitrary one
    // TODO: add some other criteria in order to make the match more precise
    defList.resize(defList.size() - 1U);

    return true;
}

bool DefLookup::lookup(const Defect &def)
{
    // look for defect class
    TDefByChecker::iterator itByChecker = d->byChecker.find(def.checker);
    if (d->byChecker.end() == itByChecker)
        return false;

    // simplify path
    const MsgFilter &filter = MsgFilter::inst();
    const DefEvent &evt = def.events[def.keyEventIdx];
    const std::string path = filter.filterPath(evt.fileName);

    // look for file name
    TDefByFile &byPath = itByChecker->second;
    assert(!byPath.empty());
    TDefByFile::iterator itByPath = byPath.find(path);
    if (byPath.end() == itByPath)
        return false;

    TDefByEvt &byEvt = itByPath->second;
    assert(!byEvt.empty());
    if (!d->usePartialResults && byEvt.end() != byEvt.find("internal warning"))
        // if the analyzer produced an "internal warning" diagnostic message,
        // we assume partial results, which cannot be reliably used for
        // differential scan ==> pretend we found what we had been looking
        // for, but do not remove anything from the store
        return true;

    // look by key event
    TDefByEvt::iterator itByEvent = byEvt.find(evt.event);
    if (byEvt.end() == itByEvent)
        return false;

    // look by msg
    TDefByMsg &byMsg = itByEvent->second;
    assert(!byMsg.empty());
    const std::string msg = filter.filterMsg(evt.msg, def.checker);
    TDefByMsg::iterator itByMsg = byMsg.find(msg);
    if (byMsg.end() == itByMsg)
        return false;

    // process the resulting list of defects sequentially
    TDefList &defList = itByMsg->second;
    assert(!defList.empty());
    if (!defLookupCore(defList, def))
        return false;

    // remove empty maps to speed up subsequent lookups
    if (defList.empty()) {
        byMsg.erase(itByMsg);
        if (byMsg.empty()) {
            byEvt.erase(itByEvent);
            if (byEvt.empty()) {
                byPath.erase(itByPath);
                if (byPath.empty())
                    d->byChecker.erase(itByChecker);
            }
        }
    }

    // found!
    return true;
}
