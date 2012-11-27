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

#include <iostream>

#include <boost/regex.hpp>
#include <boost/foreach.hpp>

// if 1, debug string substitutions while matching them
#define DEBUG_SUBST 0

inline std::string regexReplaceWrap(
        const std::string       &input,
        const boost::regex      &re,
        const std::string       &fmt)
{
    std::string output(boost::regex_replace(input, re, fmt));
#if DEBUG_SUBST
    if (input != output)
        std::cerr << "regex_replace: " << input << " -> " << output << "\n";
#endif
    return output;
}

MsgFilter* MsgFilter::self_;

struct MsgReplace {
    const boost::regex         *regex;
    const std::string           replaceWith;

    MsgReplace(const std::string &regex_, const std::string &rpl) :
        regex(new boost::regex(regex_)),
        replaceWith(rpl)
    {
    }
};

typedef std::vector<MsgReplace *>               TRegexList;
typedef std::map<const std::string, TRegexList> TMsgFilterMap;

struct MsgFilter::Private {
    bool ignorePath;
    const std::string strKrn;
    const boost::regex reKrn;
    const boost::regex reMsgConstExprRes;
    const boost::regex reDir;
    const boost::regex rePath;
    const boost::regex reTmpPath;
    const boost::regex reTmpCleaner;
    TMsgFilterMap msgFilterMap;

    void addMsgFilter(
            const std::string          &checker,
            const std::string          &regexp,
            const std::string          &replacement = "")
    {
        struct MsgReplace *rpl = new MsgReplace(regexp, replacement);
        msgFilterMap[checker].push_back(rpl);
    }

    Private():
        ignorePath(false),
        strKrn("[a-zA-Z]"),
        reKrn(strKrn),
        reDir("^[^:]*/"),
        rePath("^(?:/builddir/build/BUILD/)?([^/]+/)(.*)(\\.[ly])?$"),
        reTmpPath("^(/var)?/tmp/(.*)$"),
        reTmpCleaner("([_A-Za-z-]+)[0-9]{3,}")
    {
        addMsgFilter("UNUSED_VALUE",
                "[0-9][0-9]* out of [0-9][0-9]* times");
        addMsgFilter("UNUSED_VALUE",
                "\\(instance [0-9]+\\)");
        addMsgFilter("STRING_OVERFLOW",
                "You might overrun the [0-9][0-9]* byte");
        addMsgFilter("CONSTANT_EXPRESSION_RESULT",
                "union __*C[0-9][0-9]*");
    }
};

MsgFilter::MsgFilter():
    d(new Private)
{
}

MsgFilter::~MsgFilter() {
    delete d;
}

void MsgFilter::setIgnorePath(bool enable) {
    d->ignorePath = enable;
}

std::string MsgFilter::filterMsg(
        const std::string &msg,
        const std::string &checker)
{
    std::string filtered = msg;
    BOOST_FOREACH(const struct MsgReplace *rpl, d->msgFilterMap[checker]) {
        filtered = regexReplaceWrap(filtered, *rpl->regex, rpl->replaceWith);
    }
    std::cerr << filtered << std::endl;
    return filtered;
}

std::string MsgFilter::filterPath(const std::string &path) {
    if (d->ignorePath)
        return regexReplaceWrap(path, d->reDir, "");

    if (boost::regex_match(path, d->reTmpPath)) {
        // filter random numbers in names of temporary generated files
        std::string tmpPath = boost::regex_replace(path, d->reTmpCleaner, "\\1");
        return tmpPath;
    }

    boost::smatch sm;
    if (!boost::regex_match(path, sm, d->rePath))
        // no match
        return path;

    std::string nvr (sm[/* NVR  */ 1]);
    std::string core(sm[/* core */ 2]);

    // try to kill the multiple version strings in paths (kernel, OpenLDAP, ...)
    nvr.resize(nvr.size() - 1);
    std::string ver(boost::regex_replace(nvr, d->reKrn, ""));
    const boost::regex reKill(d->strKrn + ver + "[^/]*/");
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
