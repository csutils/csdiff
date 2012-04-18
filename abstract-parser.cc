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

std::ostream& operator<<(std::ostream &str, const Defect &def) {
    str << "\nError: " << def.defClass << def.annotation << ":\n";

    BOOST_FOREACH(const DefEvent &evt, def.events) {
        str << evt.fileName << ":" << evt.line << ":";

        if (0 < evt.column)
            str << evt.column << ":";

        str << " ";

        if (!evt.event.empty())
            str << evt.event << ": ";

        str << evt.msg << "\n";
    }

    return str;
}

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
