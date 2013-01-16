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

#include "gcc-parser.hh"

struct GccParser::Private {
    std::istream               &input;
    const std::string           fileName;
    const bool                  silent;
    bool                        hasError;

    Private(
            std::istream       &input_,
            const std::string  &fileName_,
            const bool          silent_):
        input(input_),
        fileName(fileName_),
        silent(silent_),
        hasError(false)
    {
    }
};

GccParser::GccParser(
        std::istream           &input,
        const std::string      &fileName,
        const bool              silent):
    d(new Private(input, fileName, silent))
{
}

GccParser::~GccParser() {
    delete d;
}

bool GccParser::getNext(Defect *) {
    // TODO
    return false;
}

bool GccParser::hasError() const {
    return d->hasError;
}
