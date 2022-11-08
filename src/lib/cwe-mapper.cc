/*
 * Copyright (C) 2013 Red Hat, Inc.
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

#include "cwe-mapper.hh"

#include "parser-common.hh"

#include <cstdio>

// /////////////////////////////////////////////////////////////////////////////
// implementation of CweMap
struct CweMap::Private {
    typedef std::map<std::string, int>              TNumByEvent;
    typedef std::map<std::string, TNumByEvent>      TMapByChk;

    TMapByChk           mapByChk;
    ImpliedAttrDigger   digger;

    bool detectedByTool(Defect def, const char *tool);
};

bool CweMap::Private::detectedByTool(Defect def, const char *tool)
{
    // detect tool in case it is not explicitly specified
    this->digger.inferToolFromChecker(&def);

    return (def.tool == tool);
}

CweMap::CweMap():
    d(new Private)
{
}

CweMap::~CweMap()
{
    delete d;
}

bool CweMap::empty() const
{
    return d->mapByChk.empty();
}

bool CweMap::handleLine(const TStringList &fields)
{
    if (3U != fields.size()) {
        this->parseError("invalid count of fields");
        return /* continue */ true;
    }

    // parse CWE number
    char c;
    unsigned cwe;
    if (1 != sscanf(fields[/* CWE */ 2].c_str(), "CWE-%u%c", &cwe, &c) || !cwe)
    {
        this->parseError("invalid CWE ID");
        return /* continue */ true;
    }

    // lookup by checker
    const std::string &chk = fields[/* chk */ 0];
    Private::TNumByEvent &row = d->mapByChk[chk];

    // lookup by event
    const std::string &evt = fields[/* evt */ 1];
    if (row.count(evt))
        this->parseError("CWE redefinition");

    // store the mapping
    row[evt] = cwe;

    return /* continue */ true;
}

bool CweMap::assignCwe(Defect &def) const
{
    int &cweDst = def.cwe;

    // lookup by checker
    Private::TMapByChk::const_iterator rowIt = d->mapByChk.find(def.checker);
    if (d->mapByChk.end() == rowIt) {
        if (cweDst)
            // CWE already assigned, stay silent
            return true;

        if (!this->silent)
            std::cerr << "warning: CWE not found: checker = "
                << def.checker <<"\n";
        return false;
    }

    // lookup by event
    const Private::TNumByEvent &row = rowIt->second;
    const DefEvent &evt = def.events[def.keyEventIdx];
    Private::TNumByEvent::const_iterator cweIt = row.find(evt.event);
    if (row.end() == cweIt) {
        if (cweDst)
            // CWE already assigned, stay silent
            return true;

        if (!this->silent)
            std::cerr << "warning: CWE not found: checker = " << def.checker
                << ", event = " << evt.event << "\n";

        if (d->detectedByTool(def, "coverity")) {
            // we assign per-checker CWE only for Coverity
            cweIt = row.begin();
        }
        else {
            // for other tools there is no fallback if the event is not found
            cweDst = 0;
            return false;
        }
    }

    const int cweSrc = cweIt->second;
    if (cweSrc == cweDst)
        // already assigned to the requested value
        return true;

    if (cweDst && !this->silent)
        // we are rewriting the CWE
        std::cerr << "warning: CWE overriden: "
            << cweSrc << " -> "
            << cweDst << "\n";

    // now assign the CWE
    cweDst = cweSrc;
    return true;
}


// /////////////////////////////////////////////////////////////////////////////
// implementation of CweMapDecorator
struct CweMapDecorator::Private {
    CweMap              cweMap;
};

CweMapDecorator::CweMapDecorator(AbstractWriter *writer, bool silent):
    GenericAbstractFilter(writer),
    d(new Private)
{
    d->cweMap.setSilent(silent);
}

CweMapDecorator::~CweMapDecorator()
{
    delete d;
}

void CweMapDecorator::handleDef(const Defect &orig)
{
    if (d->cweMap.empty()) {
        // CweMap not populated
        agent_->handleDef(orig);
        return;
    }

    Defect def(orig);
    d->cweMap.assignCwe(def);
    agent_->handleDef(def);
}

CweMap& CweMapDecorator::cweMap()
{
    return d->cweMap;
}
