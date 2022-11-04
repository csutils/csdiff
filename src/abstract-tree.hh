/*
 * Copyright (C) 2011-2022 Red Hat, Inc.
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
        virtual ~AbstractTreeDecoder() = default;

        /// read scan properties if available
        virtual void readScanProps(
                TScanProps             *pDst,
                const pt::ptree        *root)
        {
            (void) pDst;
            (void) root;
        }

        /// locate the list of defects within the inner document format
        virtual void readRoot(const pt::ptree *root)
        {
            defList_ = root;
            defIter_ = root->begin();
        }

        /// read the current node, decode into def, and move to the next one
        virtual bool readNode(Defect *def) = 0;

    protected:
        const pt::ptree                *defList_ = nullptr;
        pt::ptree::const_iterator       defIter_;

        virtual const pt::ptree* nextNode()
        {
            if (!defList_)
                // failed initialization
                return nullptr;

            if (defList_->end() == defIter_)
                // EOF
                return nullptr;

            // move the iterator after we get the current position
            const pt::ptree::const_iterator itNow = defIter_++;
            return &itNow->second;
        }
};

/// abstraction for higher-level encoders for various tree-based file formats
class AbstractTreeEncoder {
    public:
        virtual ~AbstractTreeEncoder() = default;

        /// import supported scan properties
        virtual void importScanProps(const TScanProps &) { }

        /// append single defect
        virtual void appendDef(const Defect &) = 0;

        /// write everything to the given output stream
        virtual void writeTo(std::ostream &) = 0;
};

template <typename TNode>
void appendNode(TNode *pDst, const TNode &src)
{
    pDst->push_back(std::make_pair("", src));
}

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
