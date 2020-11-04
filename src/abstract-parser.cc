/*
 * Copyright (C) 2011-2013 Red Hat, Inc.
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

#include "abstract-parser.hh"

#include "csparser.hh"
#include "gcc-parser.hh"
#include "json-parser.hh"

#include <boost/foreach.hpp>

AbstractParser* createParser(
        std::istream        &input,
        const std::string   &fileName,
        const bool          silent)
{
    // sniff the first char from the input
    unsigned char c = 'E';
    if (input >> c)
        // ... and put the char back to the input stream
        input.putback(c);

    switch (c) {
        case '{':
            // JSON
            return new JsonParser(input, fileName, silent);

        case 'E':
        case '#':
            // Coverity
            return new CovParser(input, fileName, silent);

        default:
            // GCC
            return new GccParser(input, fileName, silent);
    }
}

EFileFormat Parser::inputFormat() const
{
    if (dynamic_cast<JsonParser *>(parser_))
        return FF_JSON;

    if (dynamic_cast<CovParser *>(parser_))
        return FF_COVERITY;

    if (dynamic_cast<GccParser *>(parser_))
        return FF_GCC;

    return FF_INVALID;
}
