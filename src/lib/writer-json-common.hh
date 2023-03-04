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

#ifndef H_GUARD_WRITER_JSON_COMMON_H
#define H_GUARD_WRITER_JSON_COMMON_H

#include "parser.hh"            // for TScanProps

#include <string>

#include <boost/json.hpp>

/// sanitize byte sequences that are not valid in UTF-8 encoding
std::string sanitizeUTF8(const std::string &str);

/// serialize scan properties as a JSON object
boost::json::object jsonSerializeScanProps(const TScanProps &scanProps);

#endif /* H_GUARD_WRITER_JSON_COMMON_H */
