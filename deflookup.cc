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
typedef std::map<std::string, TDefByMsg>        TDefByFile;
typedef std::map<std::string, TDefByFile>       TDefByClass;

struct DefLookup::Private {
    TDefByClass                      stor;
    MsgFilter                       *filt;
};

DefLookup::DefLookup():
    d(new Private)
{
    d->filt = MsgFilter::inst();
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
    TDefByFile &row = d->stor[def.defClass];

    const DefEvent &evt = def.events.front();
    MsgFilter *filter = MsgFilter::inst();
    TDefByMsg &col = row[filter->filterPath(evt.fileName)];
    TDefList &cell = col[filter->filterMsg(evt.msg)];

    cell.push_back(def);
}

bool DefLookup::lookup(const Defect &def) {
    // look for defect class
    TDefByClass::iterator iRow = d->stor.find(def.defClass);
    if (d->stor.end() == iRow)
        return false;

    // simplify path
    const DefEvent &evt = def.events.front();
    const std::string path(d->filt->filterPath(evt.fileName));

    // look for file name
    TDefByFile &row = iRow->second;
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol)
        return false;

    // look by msg
    TDefByMsg &col = iCol->second;
    TDefByMsg::iterator iCell = col.find(d->filt->filterMsg(evt.msg));
    if (col.end() == iCell)
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
