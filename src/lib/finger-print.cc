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

#include "finger-print.hh"

#include "hash-util.hh"
#include "msg-filter.hh"

#include <cassert>

#include <boost/uuid/name_generator.hpp>    // for boost::uuids::detail::sha1

/// return SHA1 hash of `str` as hex-encoded string
static inline std::string computeHexSHA1(const std::string &str)
{
    using boost::uuids::detail::sha1;
    return hexHashStr<sha1>(str);
}

struct FingerPrinter::Private {
    std::string basicData;
    std::string lineContent;
};

// separator used for hashing of data composed from multiple strings
static const std::string sep = "\n";

// TODO: consider lazy evaluation of basicData/lineContent
FingerPrinter::FingerPrinter(const Defect &def):
    d(new Private)
{
    // filter that csdiff uses to drop details insignificant for matching
    const MsgFilter &filt = MsgFilter::inst();

    // read and transform file path
    const DefEvent &keyEvt = def.events[def.keyEventIdx];
    const std::string path =
        filt.filterPath(keyEvt.fileName, /* forceFullPath */ true);

    // initialize basicData by taking all that DefLookup::lookup() looks at
    d->basicData =
        /* checker   */ def.checker     + sep +
        /* file path */ path            + sep +
        /* key event */ keyEvt.event    + sep +
        /* message   */ filt.filterMsg(keyEvt.msg, def.checker);
}

FingerPrinter::~FingerPrinter() = default;

// TODO: consider caching of SHA1 hashes for subsequent calls
std::string FingerPrinter::getHash(const EFingerPrintVer fpv) const
{
    if (d->basicData.empty())
        // not enough data to compute the hash from
        return "";

    if (fpv == FPV_CSDIFF)
        // return SHA1 hash from basicData
        return computeHexSHA1(d->basicData);

    assert(fpv == FPV_CSDIFF_WITH_LINE_CONTENT);
    if (d->lineContent.empty())
        // no line content available
        return "";

    // return SHA1 hash from basicData AND lineContent
    return computeHexSHA1(d->basicData + sep + d->lineContent);
}
