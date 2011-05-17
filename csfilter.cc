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

struct MsgFilter::Private {
    const boost::regex reMsg;
    const boost::regex rePath;
    const boost::regex rePathFlex;

    Private():
        reMsg("[0-9][0-9]* out of [0-9][0-9]* times"),
        rePath("^(?:/builddir/build/BUILD/)?[^/]+/"),
        rePathFlex("\\.l$")
    {
    }
};

MsgFilter::MsgFilter():
    d(new Private)
{
}

MsgFilter::~MsgFilter() {
    delete d;
}

std::string MsgFilter::filterMsg(const std::string &msg) {
    return regexReplaceWrap(msg, d->reMsg, "");
}

std::string MsgFilter::filterPath(const std::string &path) {
    return regexReplaceWrap(
            regexReplaceWrap(path, d->rePath, ""),
            d->rePathFlex, ".c");
}
