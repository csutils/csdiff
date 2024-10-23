/*
 * Copyright (C) 2024 Red Hat, Inc.
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

#ifndef H_GUARD_GLOB_EXPAND_H
#define H_GUARD_GLOB_EXPAND_H

#include <string>
#include <vector>

using TStringList = std::vector<std::string>;

/// expand the `globPat` pattern and store resulting file names to `*pDst`
bool globExpand(TStringList *pDst, const std::string &globPat);

/// expand all glob patterns in `*pDstSrc` and store results to `*pDstSrc`
bool globExpand(TStringList *pDstSrc);

#endif /* H_GUARD_GLOB_EXPAND_H */
