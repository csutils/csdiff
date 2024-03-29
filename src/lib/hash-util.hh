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

#include <string>
#include <vector>

#include <boost/algorithm/hex.hpp>
#include <boost/algorithm/string.hpp>

/// compute TEng hash of `src` and return it as hex-encoded string
template <typename TEng, typename TSrc>
std::string hexHashStr(const TSrc &src)
{
    // create hash engine and process the input
    TEng eng;
    eng.process_bytes(src.data(), src.size());

    // export the hash as an array of unsigned int
    // FIXME: std::remove_reference is needed on el7 (boost-1.53)
    using TDst = typename TEng::digest_type;
    typename std::remove_reference<TDst>::type dst;
    eng.get_digest(dst);

    // convert the hash to a vector of unsigned int
    static const size_t len = sizeof(dst) / sizeof(dst[0]);
    const std::vector<unsigned> hash(dst, dst + len);

    // convert the hash to a hex string
    std::string result;
    boost::algorithm::hex(hash.begin(), hash.end(), back_inserter(result));

    // convert uppercase letters to lowercase
    boost::algorithm::to_lower(result);
    return result;
}
