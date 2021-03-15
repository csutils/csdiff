/*
 * Copyright (C) 2011 Red Hat, Inc.
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

#include "csfilter.hh"
#include "regex.hh"

#include <iostream>

// Setup verbosity for debugging string substitions while matching them.
// Verbosity levels are from 0 to 3 (0 is off)
#define DEBUG_SUBST 0

inline std::string regexReplaceWrap(
        const std::string       &input,
        const RE                &re,
        const std::string       &fmt)
{
    std::string output(boost::regex_replace(input, re, fmt));
#if DEBUG_SUBST > 1
    if (input != output)
        std::cerr << "regex_replace: " << input << " -> " << output << "\n";
#endif
    return output;
}

MsgFilter* MsgFilter::self_;

struct MsgReplace {
    const RE                    regex;
    const std::string           replaceWith;

    MsgReplace(const std::string &regex_, const std::string &rpl) :
        regex(regex_),
        replaceWith(rpl)
    {
    }
};

typedef std::vector<MsgReplace *>               TRegexList;
typedef std::map<const std::string, TRegexList> TMsgFilterMap;

struct MsgFilter::Private {
    bool ignorePath = false;
    TMsgFilterMap msgFilterMap;
    TSubstMap fileSubsts;

    const std::string strKrn = "^[a-zA-Z+]+";
    const RE reKrn = RE(strKrn);
    const RE reDir = RE("^([^:]*/)");
    const RE reFile = RE("[^/]+$");
    const RE rePath = RE("^(?:/builddir/build/BUILD/)?([^/]+/)(.*)(\\.[ly])?$");
    const RE rePyBuild = RE("^((?:/builddir/build/BUILD/)?[^/]+/)build/lib/(.*)$");
    const RE reTmpPath = RE("^(/var)?/tmp/(.*)$");
    const RE reTmpCleaner = RE("(.*)");

    void addMsgFilter(
            const std::string          &checker,
            const std::string          &regexp,
            const std::string          &replacement = "")
    {
        struct MsgReplace *rpl = new MsgReplace(regexp, replacement);
        msgFilterMap[checker].push_back(rpl);
    }
};

MsgFilter::MsgFilter():
    d(new Private)
{
    d->addMsgFilter("", "[0-9][0-9]* out of [0-9][0-9]* times");
    d->addMsgFilter("UNUSED_VALUE",
            "\\(instance [0-9]+\\)");
    d->addMsgFilter("STRING_OVERFLOW",
            "You might overrun the [0-9][0-9]* byte");
    // ignore changes in parameters -> it is still the same UNUSED_VALUE
    d->addMsgFilter("UNUSED_VALUE",
            "returned by \"([^\\(]+)\\(.*\\)\"",
            "returned by \"\\1\\(\\)\"");

    // unify the format of glib/gnome dprecation warnings
    // NOTE: "\u007f\u007f\u007f" does not compile on el6
    static const char uniApos[] = { 0x7f, 0x7f, 0x7f, 0x00 };
    d->addMsgFilter("COMPILER_WARNING", uniApos, "'");

    // ignore embeded declaration location
    d->addMsgFilter("COMPILER_WARNING", " \\(declared at [^)]*\\)", "");

    // ignore suggestion for deprecation warnings
    d->addMsgFilter("COMPILER_WARNING", ": Use '[^']*' instead", "");

    // unify (per build random) names of temporary variables
    d->addMsgFilter("COMPILER_WARNING", "_tmp[0-9]+_", "_tmp_");

    // auxiliary info provided by valgrind directly in the key event message
    d->addMsgFilter("VALGRIND_WARNING",
            " lost in loss record [0-9,]+ of [0-9,]+$", "");

    // pylint reports, either raw, or prospector-wrapped
    const std::vector<std::string> pylintCheckers= {
        "PROSPECTOR_WARNING",
        "PYLINT_WARNING"
    };
    for (const std::string &checker : pylintCheckers) {
        // "Too many lines in module (1152/1000)" etc.
        d->addMsgFilter(checker, " \\([0-9]+/[0-9]+\\)$", "");

        // "... Redefining name 'desc' from outer scope (line 10)" etc.
        d->addMsgFilter(checker, " \\((?:imported )?line [0-9]+\\)$", "");
    }

    // "__coverity_strcmp" -> "strcmp", etc.
    d->addMsgFilter("", "__coverity_", "");

    // artificial field names of anonymous unions that Coverity produces
    d->addMsgFilter("", "__C[0-9]+");

    // used by IDENTIFIER_TYPO (but applies generally)
    d->addMsgFilter("", "at least [0-9][0-9]* times.$");
}

MsgFilter::~MsgFilter()
{
    for (TMsgFilterMap::const_reference item : d->msgFilterMap)
        for (struct MsgReplace *rpl : item.second)
            delete rpl;

    delete d;
}

void MsgFilter::setIgnorePath(bool enable)
{
    d->ignorePath = enable;
}

void MsgFilter::setFileNameSubstitution(
                const std::string      &oldFile,
                const std::string      &newFile)
{
    d->fileSubsts[oldFile] = newFile;
}

std::string MsgFilter::filterMsg(
        const std::string &msg,
        const std::string &checker)
{
    std::string filtered = msg;
    for (const struct MsgReplace *rpl : d->msgFilterMap[checker]) {
        filtered = regexReplaceWrap(filtered, rpl->regex, rpl->replaceWith);
    }

    // these substitutions are common for all checkers
    for (const struct MsgReplace *rpl : d->msgFilterMap[""]) {
        filtered = regexReplaceWrap(filtered, rpl->regex, rpl->replaceWith);
    }

#if DEBUG_SUBST > 1
    std::cerr << "filterMsg: " << filtered << "\n";
#endif
    return filtered;
}

std::string MsgFilter::filterPath(const std::string &origPath)
{
    std::string path = origPath;

    TSubstMap &substMap = d->fileSubsts;
    if (!substMap.empty()) {
        std::string base = regexReplaceWrap(origPath, d->reDir, "");
        std::string dir = regexReplaceWrap(origPath, d->reFile, "");
        if (substMap.find(base) != substMap.end()) {
            const std::string &substWith = substMap[base];
            path = dir + substWith;
        }
    }

    if (d->ignorePath)
        return regexReplaceWrap(path, d->reDir, "");

    if (boost::regex_match(path, d->reTmpPath)) {
        // filter random numbers in names of temporary generated files
        std::string tmpPath = boost::regex_replace(path, d->reTmpCleaner, "/tmp/tmp.c");
        return tmpPath;
    }

    boost::smatch sm;
    if (boost::regex_match(path, sm, d->rePyBuild)) {
        // %{_builddir}/build/lib/setuptools/glob.py ->
        // %{_builddir}/setuptools/glob.py
        path = sm[1] + sm[2];
    }

    if (!boost::regex_match(path, sm, d->rePath))
        // no match
        return path;

    std::string nvr (sm[/* NVR  */ 1]);
    std::string core(sm[/* core */ 2]);

    // try to kill the multiple version strings in paths (kernel, OpenLDAP, ...)
    nvr.resize(nvr.size() - 1);
    std::string ver(boost::regex_replace(nvr, d->reKrn, ""));
    const std::string krnPattern = d->strKrn + ver + "[^/]*/";

#if DEBUG_SUBST > 2
    std::cerr << "nvr: " << nvr << "\n";
    std::cerr << "ver: " << ver << "\n";
    std::cerr << "krnPattern: " << krnPattern << "\n";
#endif

    const RE reKill(krnPattern);
    core = boost::regex_replace(core, reKill, "");

    // quirk for Coverity inconsistency in handling bison-generated file names
    std::string suff(sm[/* Bison suffix */ 3]);
    if (!suff.empty())
        core += ".c";

#if DEBUG_SUBST
    std::cerr << "filterPath: " << path << " -> " << core << "\n";
#endif
    return core;
}
