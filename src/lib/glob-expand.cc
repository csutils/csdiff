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

#include "glob-expand.hh"

#include <glob.h>

bool globExpand(TStringList *pDst, const std::string &globPat)
{
    // use POSIX glob() to expand the glob pattern
    glob_t results;
    results.gl_pathc = 0U;
    const bool success = !glob(globPat.c_str(), 0, nullptr, &results);

    // store the results to *pDst
    for (unsigned i = 0U; i < results.gl_pathc; ++i)
        pDst->push_back(results.gl_pathv[i]);

    // free the original data structure returned by glob()
    globfree(&results);
    return success;
}

bool globExpand(TStringList *pDstSrc)
{
    bool success = true;

    // expand all globs one by one
    TStringList dst;
    for (const auto &globPat : *pDstSrc)
        success &= globExpand(&dst, globPat);

    // store the results to *pDstSrc
    *pDstSrc = std::move(dst);
    return success;
}
