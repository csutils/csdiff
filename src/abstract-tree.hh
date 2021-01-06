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

#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

struct Defect;

/// abstraction for higher-level decoders for various tree-based file formats
class AbstractTreeDecoder {
    public:
        virtual ~AbstractTreeDecoder() { }

        /// read the given ptree node, decode, and store the result into def
        virtual void readNode(Defect *def, const pt::ptree &node) = 0;
};

#endif /* H_GUARD_ABSTRACT_TREE_H */
