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

// /////////////////////////////////////////////////////////////////////////////
// implementation of CweMap
struct CweMap::Private {
};

CweMap::CweMap():
    d(new Private)
{
}

CweMap::~CweMap() {
    delete d;
}

bool CweMap::loadCweMap(std::istream &str, const std::string &fileName) {
    // TODO
    (void) str;
    (void) fileName;
    __asm__("INT3");
    return false;
}

bool CweMap::assignCwe(Defect &def) const {
    // TODO
    (void) def;
    return false;
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
