/*
 * Copyright (C) 2018 Red Hat, Inc.
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

#ifndef H_GUARD_SHARED_STRING_PTREE_H
#define H_GUARD_SHARED_STRING_PTREE_H

#include "shared-string.hh"

#include <boost/property_tree/ptree.hpp>

template <typename T>
struct SharedStrTrans {
    typedef SharedStr internal_type;
    typedef SharedStr external_type;

    boost::optional<SharedStr> put_value(const T &val) const {
        const SharedStr ss(val);
        return ss;
    }

    boost::optional<T> get_value(const SharedStr &ss) const {
        T val;
        ss.writeOut(&val);
        return val;
    }
};

namespace boost {
    namespace property_tree {
        template <typename T>
        struct translator_between<SharedStr, T> {
            typedef SharedStrTrans<T> type;
        };
    }
}

typedef boost::property_tree::basic_ptree<std::string, SharedStr>
    SharedStringPTree;

#endif /* H_GUARD_SHARED_STRING_PTREE_H */
