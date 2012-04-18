/*
 * Copyright (C) 2011-2012 Red Hat, Inc.
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

#include "json-parser.hh"

struct JsonParser::Private {
};

JsonParser::JsonParser(
        std::istream                &input,
        const std::string           &fileName,
        const bool                   silent):
    d(new Private)
{
    // TODO
    (void) input;
    (void) silent;

    std::cerr << fileName << ": error: JsonParser is not implemented yet\n";
}

JsonParser::~JsonParser() {
    delete d;
}

bool JsonParser::hasError() const {
    // TODO
    return true;
}

bool JsonParser::getNext(Defect *def) {
    // TODO
    (void) def;
    return false;
}
