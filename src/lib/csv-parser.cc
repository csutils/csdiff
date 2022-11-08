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

#include "csv-parser.hh"

#include <boost/tokenizer.hpp>

#include <cassert>

struct AbstractCsvParser::Private {
    const std::string      *pFileName   = nullptr;
    int                     lineno      = 0;
    bool                    hasError    = false;
};

AbstractCsvParser::AbstractCsvParser():
    d(new Private)
{
}

AbstractCsvParser::~AbstractCsvParser()
{
    delete d;
}

bool AbstractCsvParser::parse(InStream &ins)
{
    assert(!d->pFileName);
    d->pFileName = &ins.fileName();
    d->hasError = false;

    std::istream &str = ins.str();
    std::string line;
    for (d->lineno = 1; std::getline(str, line); d->lineno++) {
        // initialize tokenizer
        typedef boost::escaped_list_separator<char>     TSeparator;
        typedef boost::tokenizer<TSeparator>            TTokenizer;
        TTokenizer tok(line);

        // break the current line into fields
        const TStringList fields(tok.begin(), tok.end());

        // call the template method
        if (!/* continue */this->handleLine(fields))
            break;
    }

    d->pFileName = nullptr;
    return !d->hasError;
}

void AbstractCsvParser::parseError(const std::string &msg)
{
    assert(d->pFileName);
    d->hasError = true;
    if (this->silent)
        return;

    std::cerr
        << *(d->pFileName) << ":"
        << d->lineno << ": error: "
        << msg << "\n";
}
