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

#include "abstract-parser.hh"

#include "csparser.hh"
#include "json-parser.hh"

#include <boost/foreach.hpp>

AbstractParser* createParser(
        std::istream        &input,
        const std::string   &fileName,
        const bool          silent)
{
    bool jsonDetected = false;

    // sniff the first char from the input
    char c;
    if (input >> c) {
        if ('{' == c)
            jsonDetected = true;

        // now put the char back to the input stream
        input.putback(c);
    }

    if (jsonDetected)
        // create a JSON parser
        return new JsonParser(input, fileName, silent);

    // fall-back to default
    return new CovParser(input, fileName, silent);
}

EFileFormat Parser::inputFormat() const {
    return (dynamic_cast<JsonParser *>(parser_))\
        ? FF_JSON
        : FF_COVERITY;
}
