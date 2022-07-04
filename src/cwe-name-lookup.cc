/*
 * Copyright (C) 2020 Red Hat, Inc.
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

#include "cwe-name-lookup.hh"

#include "parser-common.hh"

#include <map>

struct CweNameLookup::Private {
    typedef std::map<int, std::string> TMap;
    TMap nameByCwe;
    const std::string emp;
};

CweNameLookup::CweNameLookup():
    d(new Private)
{
}

CweNameLookup::~CweNameLookup()
{
    delete d;
}

bool CweNameLookup::handleLine(const TStringList &fields)
{
    if (2U != fields.size()) {
        this->parseError("invalid count of fields");
        return /* continue */ true;
    }

    // parse CWE number
    const std::string &cweId = fields[/* CWE */ 0];
    const int cwe = parse_int(cweId, -1);
    if (cwe < 0) {
        // we use "unmapped" for findings without any CWE assigned
        // as discussed in https://github.com/csutils/csdiff/pull/61
        if (cweId != "unmapped")
            this->parseError("invalid CWE ID");

        return /* continue */ true;
    }

    // lookup by CWE number
    if (d->nameByCwe.count(cwe))
        this->parseError("CWE name redefinition");

    // define the mapping
    const std::string &cweName = fields[/* name */ 1];
    d->nameByCwe[cwe] = cweName;

    return /* continue */ true;
}

const std::string& CweNameLookup::lookup(const int cwe) const
{
    const Private::TMap::const_iterator it = d->nameByCwe.find(cwe);
    return (d->nameByCwe.end() == it)
        ? d->emp
        : it->second;
}
