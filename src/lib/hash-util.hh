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

/// compute TEng hash of `src` and return it as hex-encoded string
template <typename TEng, typename TSrc>
std::string hexHashStr(const TSrc &src)
{
    // create hash engine and process the input
    TEng eng;
    eng.process_bytes(src.data(), src.size());

    // export the hash as an array
    using TDst = typename TEng::digest_type;
    TDst dst;
    eng.get_digest(dst);

    // convert the hash to a vector
    static const size_t len = sizeof(dst) / sizeof(dst[0]);
    using TElem = typename std::remove_extent<TDst>::type;
    const std::vector<TElem> hash(dst, dst + len);

    // convert the hash to a hex string
    std::string result;
    boost::algorithm::hex_lower(hash.begin(), hash.end(), back_inserter(result));
    return result;
}
