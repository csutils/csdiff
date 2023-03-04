/*
 * Copyright (C) 2011 - 2023 Red Hat, Inc.
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

#include "writer-json-common.hh"

#include <boost/nowide/utf/convert.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::json;

std::string sanitizeUTF8(const std::string &str)
{
    using boost::nowide::utf::convert_string;

    // every non-UTF8 sequence will be replaced with 0xEF 0xBF 0xBD which
    // corresponds to REPLACEMENT CHARACTER U+FFFD
    return convert_string<char>(str.data(), str.data() + str.size());
}

// TODO: This should not necessary!  TScanProps should be able to contain
// any type so that no conversions here are needed.
object jsonSerializeScanProps(const TScanProps &scanProps)
{
    static auto isDigit = [](unsigned char c){ return std::isdigit(c); };

    object scan;
    for (const auto &prop : scanProps) {
        const auto &val = prop.second;
        if (std::all_of(val.begin(), val.end(), isDigit))
            scan[prop.first] = boost::lexical_cast<int>(val);
        else
            scan[prop.first] = val;
    }

    return scan;
}
