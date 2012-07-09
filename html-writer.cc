/*
 * Copyright (C) 2012 Red Hat, Inc.
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

#include "html-writer.hh"

#include <boost/foreach.hpp>

struct HtmlWriter::Private {
    std::ostream                   &str;
    TScanProps                      scanProps;

    Private(std::ostream &str_):
        str(str_)
    {
    }
};

HtmlWriter::HtmlWriter(std::ostream &str):
    d(new Private(str))
{
}

HtmlWriter::~HtmlWriter() {
    delete d;
}

const TScanProps& HtmlWriter::getScanProps() const {
    return d->scanProps;
}

void HtmlWriter::setScanProps(const TScanProps &scanProps) {
    d->scanProps = scanProps;
}

void HtmlWriter::handleDef(const Defect &def) {
    // TODO
    (void) def;
}

void HtmlWriter::flush() {
    // TODO
}
