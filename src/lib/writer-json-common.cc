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

/// return true if the given string represents a number
bool isNumber(const std::string &str)
{
    static auto isDigit = [](unsigned char c){ return std::isdigit(c); };

    return std::all_of(str.begin(), str.end(), isDigit);
}

// TODO: This should not necessary!  TScanProps should be able to contain
// any type so that no conversions here are needed.
object jsonSerializeScanProps(const TScanProps &scanProps)
{
    object scan;
    for (const auto &prop : scanProps) {
        const auto &val = prop.second;
        if (isNumber(val))
            scan[prop.first] = boost::lexical_cast<int>(val);
        else
            scan[prop.first] = val;
    }

    return scan;
}

static inline void prettyPrintArray(
        std::ostream           &os,
        const array            &arr,
        std::string            *indent = nullptr)
{
        os << '[';
        if (arr.empty()) {
            os << ']';
            return;
        }

        indent->append(4, ' ');

        std::string sep{'\n'};
        for (const auto &elem : arr) {
            os << sep << *indent;
            jsonPrettyPrint(os, elem, indent);
            sep = ",\n";
        }
        os << '\n';

        indent->resize(indent->size() - 4);
        os << *indent << ']';
}

static inline void prettyPrintObject(
        std::ostream           &os,
        const object           &obj,
        std::string            *indent = nullptr)
{
        os << '{';
        if (obj.empty()) {
            os << '}';
            return;
        }

        indent->append(4, ' ');

        std::string sep{'\n'};
        for (const auto &elem : obj) {
            os << sep << *indent << serialize(elem.key()) << ": ";
            jsonPrettyPrint(os, elem.value(), indent);
            sep = ",\n";
        }
        os << '\n';

        indent->resize(indent->size() - 4);
        os << *indent << '}';
}

void jsonPrettyPrint(
        std::ostream               &os,
        const value                &jv,
        std::string                *indent)
{
    std::string indent_;
    if (!indent)
        indent = &indent_;

    switch (jv.kind()) {
    case kind::array:
        prettyPrintArray(os, jv.get_array(), indent);
        break;

    case kind::object:
        prettyPrintObject(os, jv.get_object(), indent);
        break;

    case kind::string:
        os << serialize(jv.get_string());
        break;

    case kind::uint64:
        os << jv.get_uint64();
        break;

    case kind::int64:
        os << jv.get_int64();
        break;

    case kind::double_:
        os << jv.get_double();
        break;

    case kind::bool_:
        os << jv.get_bool();
        break;

    case kind::null:
        os << "null";
        break;
    }

    if (indent->empty())
        os << "\n";
}
