/*
 * Copyright (C) 2011-2021 Red Hat, Inc.
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

#ifndef H_GUARD_ABSTRACT_TREE_H
#define H_GUARD_ABSTRACT_TREE_H

#include "abstract-parser.hh"       // for TScanProps

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

struct Defect;

/// abstraction for higher-level decoders for various tree-based file formats
class AbstractTreeDecoder {
    public:
        virtual ~AbstractTreeDecoder() { }

        /// read scan properties if available
        virtual void readScanProps(
                TScanProps             *pDst,
                const pt::ptree        *root)
        {
            (void) pDst;
            (void) root;
        }

        /// locate the list of defects within the inner document format
        virtual void readRoot(
                const pt::ptree       **pDefList,
                const pt::ptree        *root)
        {
            *pDefList = root;
        }

        /// read the given ptree node, decode, and store the result into def
        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter)
            = 0;
};

template <typename TNode>
bool findChildOf(TNode **pDst, TNode &node, const char *key)
{
    if (node.not_found() == node.find(key))
        return false;

    *pDst = &node.get_child(key);
    return true;
}

template <typename T>
inline T valueOf(const pt::ptree &node, const char *path, const T &defVal)
{
    const boost::optional<T> &opt = node.get_optional<T>(path);
    return opt.get_value_or(defVal);
}

inline std::string getStringValue(const pt::ptree &node)
{
    return node.get_value<std::string>();
}

inline std::string getStringValue(const pt::ptree::const_iterator it)
{
    return getStringValue(it->second);
}

#endif /* H_GUARD_ABSTRACT_TREE_H */
