/*
 * Copyright (C) 2011-2020 Red Hat, Inc.
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

#ifndef H_GUARD_PARSER_COMMON_H
#define H_GUARD_PARSER_COMMON_H

#define RE_EVENT_GCC "(?:(?:(?:fatal|internal) )?[a-z][\\[\\]A-Za-z0-9_-]+)"
#define RE_EVENT_PROSPECTOR "(?:[A-Z]+[0-9]+\\[[a-z0-9]+\\])"
#define RE_EVENT RE_EVENT_GCC "|" RE_EVENT_PROSPECTOR

#endif /* H_GUARD_PARSER_COMMON_H */
