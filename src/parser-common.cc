/*
 * Copyright (C) 2020 Red Hat, Inc.
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

#include "parser-common.hh"

#include "regex.hh"

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/lexical_cast.hpp>

int parse_int(const std::string &str, const int fallback)
{
    try {
        return boost::lexical_cast<int>(str);
    }
    catch (boost::bad_lexical_cast &) {
        return fallback;
    }
}

struct ImpliedAttrDigger::Private {
    typedef std::map<std::string, std::string>      TMap;
    TMap langByChecker;

    const RE reToolWarning = RE("^([A-Z_]+)_WARNING$");
};

ImpliedAttrDigger::ImpliedAttrDigger():
    d(new Private)
{
    d->langByChecker["CLANG_WARNING"]           = "c/c++";
    d->langByChecker["COMPILER_WARNING"]        = "c/c++";
    d->langByChecker["CPPCHECK_WARNING"]        = "c/c++";
    d->langByChecker["GCC_ANALYZER_WARNING"]    = "c/c++";
    d->langByChecker["PROSPECTOR_WARNING"]      = "python";
    d->langByChecker["SHELLCHECK_WARNING"]      = "shell";
    d->langByChecker["SMATCH_WARNING"]          = "c/c++";
}

ImpliedAttrDigger::~ImpliedAttrDigger()
{
    delete d;
}

void ImpliedAttrDigger::inferLangFromChecker(
        Defect         *pDef,
        const bool      onlyIfMissing)
    const
{
    if (onlyIfMissing && !pDef->language.empty())
        // language already assigned
        return;

    Private::TMap::const_iterator it = d->langByChecker.find(pDef->checker);
    if (d->langByChecker.end() == it)
        // not found
        return;

    // found --> assign from map
    pDef->language = it->second;
}

void ImpliedAttrDigger::inferToolFromChecker(
        Defect         *pDef,
        const bool      onlyIfMissing)
    const
{
    if (onlyIfMissing && !pDef->tool.empty())
        // tool already assigned
        return;

    boost::smatch sm;
    if (boost::regex_match(pDef->checker, sm, d->reToolWarning)) {
        // extract tool="gcc-analyzer" out of checker="GCC_ANALYZER_WARNING"
        std::string tool = sm[/* tool */ 1];
        boost::algorithm::to_lower(tool);
        boost::algorithm::replace_all(tool, "_", "-");

        if (tool == "compiler")
            // we use COMPILER_WARNING for "gcc" due to historical reasons
            tool = "gcc";

        pDef->tool = tool;
    }
    else
        // no tool matched --> assume coverity
        pDef->tool = "coverity";
}
