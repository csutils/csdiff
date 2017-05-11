/*
 * Copyright (C) 2011 Red Hat, Inc.
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

#include "abstract-parser.hh"
#include "csfilter.hh"

#include <map>

typedef std::vector<Defect>                     TDefList;
typedef std::map<std::string, TDefList>         TDefByMsg;
typedef std::map<std::string, TDefByMsg>        TDefByEvt;
typedef std::map<std::string, TDefByEvt>        TDefByFile;
typedef std::map<std::string, TDefByFile>       TDefByChecker;

struct DefLookup::Private {
    TDefByChecker                    stor;
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

DefLookup& DefLookup::operator=(const DefLookup &ref) {
    if (&ref == this)
        return *this;

    delete d;
    d = new Private(*ref.d);
    return *this;
}

DefLookup::~DefLookup() {
    delete d;
}

void DefLookup::hashDefect(const Defect &def) {
    TDefByFile &row = d->stor[def.checker];

    const DefEvent &evt = def.events[def.keyEventIdx];
    MsgFilter *filter = MsgFilter::inst();
    TDefByEvt &col = row[filter->filterPath(evt.fileName)];
    TDefByMsg &zCol = col[evt.event];
    TDefList &cell = zCol[filter->filterMsg(evt.msg, def.checker)];

    cell.push_back(def);
}

bool DefLookup::lookup(const Defect &def) {
    // look for defect class
    TDefByChecker::iterator iRow = d->stor.find(def.checker);
    if (d->stor.end() == iRow)
        return false;

    // simplify path
    MsgFilter *filter = MsgFilter::inst();
    const DefEvent &evt = def.events[def.keyEventIdx];
    const std::string path(filter->filterPath(evt.fileName));

    // look for file name
    TDefByFile &row = iRow->second;
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol)
        return false;

    TDefByEvt &col = iCol->second;
    if (!d->usePartialResults && col.end() != col.find("internal warning"))
        // if the analyzer produced an "internal warning" diagnostic message,
        // we assume partial results, which cannot be reliably used for
        // differential scan ==> pretend we found what we had been looking
        // for, but do not remove anything from the store
        return true;

    // look by key event
    TDefByEvt::iterator iZCol = col.find(evt.event);
    if (col.end() == iZCol)
        return false;

    // look by msg
    TDefByMsg &zCol = iZCol->second;
    TDefByMsg::iterator iCell = zCol.find(
            filter->filterMsg(evt.msg, def.checker));
    if (zCol.end() == iCell)
        return false;

    // FIXME: nasty over-approximation
    TDefList &defs = iCell->second;
    unsigned cnt = defs.size();
    if (cnt)
        // just remove an arbitrary one
        defs.resize(cnt - 1);
    else
        return false;

    // TODO: add some other criteria in order to make the match more precise
    return true;
}
