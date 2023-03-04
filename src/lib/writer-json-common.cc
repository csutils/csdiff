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

std::string sanitizeUTF8(const std::string &str)
{
    using boost::nowide::utf::convert_string;

    // every non-UTF8 sequence will be replaced with 0xEF 0xBF 0xBD which
    // corresponds to REPLACEMENT CHARACTER U+FFFD
    return convert_string<char>(str.data(), str.data() + str.size());
}
