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

#include <cstdio>

#include <boost/tokenizer.hpp>

// /////////////////////////////////////////////////////////////////////////////
// implementation of CweMap
struct CweMap::Private {
    typedef std::map<std::string, int>              TNumByEvent;
    typedef std::map<std::string, TNumByEvent>      TMapByChk;

    std::string         fileName;
    std::string         line;
    int                 lineno;
    bool                hasError;
    TMapByChk           mapByChk;

    void parseError(const std::string &msg);
    void parseLine();
};

CweMap::CweMap():
    d(new Private)
{
    d->hasError = false;
}

CweMap::~CweMap() {
    delete d;
}

bool CweMap::empty() const {
    return d->mapByChk.empty();
}

void CweMap::Private::parseError(const std::string &msg) {
    this->hasError = true;
    std::cerr
        << this->fileName << ":"
        << this->lineno << ": error: "
        << msg << "\n";
}

void CweMap::Private::parseLine() {
    // initialize tokenizer
    typedef boost::escaped_list_separator<char>     TSeparator;
    typedef boost::tokenizer<TSeparator>            TTokenizer;
    TTokenizer tok(this->line);

    // break the current line into fields
    typedef std::vector<std::string>                TStringList;
    TStringList fields(tok.begin(), tok.end());
    if (3U != fields.size()) {
        this->parseError("invalid count of fields");
        return;
    }

    // parse CWE number
    char c;
    unsigned cwe;
    if (1 != sscanf(fields[/* CWE */ 2].c_str(), "CWE-%u%c", &cwe, &c) || !cwe)
    {
        this->parseError("invalid CWE ID");
        return;
    }

    // lookup by checker
    const std::string &chk = fields[/* chk */ 0];
    TNumByEvent &row = this->mapByChk[chk];

    // lookup by event
    const std::string &evt = fields[/* evt */ 1];
    if (row.count(evt))
        this->parseError("CWE redefinition");

    // store the mapping
    row[evt] = cwe;
}

bool CweMap::loadCweMap(std::istream &str, const std::string &fileName) {
    d->fileName = fileName;
    d->lineno = 0;

    while (std::getline(str, d->line)) {
        d->lineno++;
        d->parseLine();
    }

    return !d->hasError;
}

bool CweMap::assignCwe(Defect &def) const {
    // lookup by checker
    Private::TMapByChk::const_iterator rowIt = d->mapByChk.find(def.checker);
    if (d->mapByChk.end() == rowIt) {
        std::cerr << "warning: CWE not found: checker = " << def.checker <<"\n";
        return false;
    }

    // lookup by event
    const Private::TNumByEvent &row = rowIt->second;
    const DefEvent &evt = def.events[def.keyEventIdx];
    Private::TNumByEvent::const_iterator cweIt = row.find(evt.event);
    if (row.end() == cweIt) {
        std::cerr << "warning: CWE not found: checker = " << def.checker
            << ", event = " << evt.event << "\n";
        cweIt = row.begin();
    }

    const int cweSrc = cweIt->second;
    int &cweDst = def.cwe;
    if (cweSrc == cweDst)
        // already assigned
        return true;

    if (cweDst)
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
    AbstractWriter     *slave;
    CweMap              cweMap;
};

CweMapDecorator::CweMapDecorator(AbstractWriter *writer):
    d(new Private)
{
    d->slave = writer;
}

CweMapDecorator::~CweMapDecorator() {
    delete d->slave;
    delete d;
}

const TScanProps& CweMapDecorator::getScanProps() const {
    return d->slave->getScanProps();
}

void CweMapDecorator::setScanProps(const TScanProps &props) {
    d->slave->setScanProps(props);
}

void CweMapDecorator::handleDef(const Defect &orig) {
    if (d->cweMap.empty()) {
        // CweMap not populated
        d->slave->handleDef(orig);
        return;
    }

    Defect def(orig);
    d->cweMap.assignCwe(def);
    d->slave->handleDef(def);
}

void CweMapDecorator::flush() {
    d->slave->flush();
}

CweMap& CweMapDecorator::cweMap() {
    return d->cweMap;
}
