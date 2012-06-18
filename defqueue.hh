/*
 * Copyright (C) 2011 - 2012 Red Hat, Inc.
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

#ifndef H_GUARD_DEFQUEUE_H
#define H_GUARD_DEFQUEUE_H

#include "abstract-parser.hh"

#include <list>

#include <boost/foreach.hpp>

class MsgFilter;

class DefQueue {
    private:
        typedef std::list<Defect>                       TDefList;
        typedef std::map<std::string, TDefList>         TDefByFile;
        typedef std::map<std::string, TDefByFile>       TDefByClass;

        TDefByClass                     stor_;
        MsgFilter                      *filt_;

    public:
        DefQueue();

        void hashDefect(const Defect &);

        bool lookup(
                Defect                  &dst,
                const std::string       &checker,
                const std::string       &fileName);

        bool empty() const {
            return stor_.empty();
        }

        template <class TVisitor> bool walk(TVisitor &);
};

template <class TVisitor> bool DefQueue::walk(TVisitor &visitor) {
    BOOST_FOREACH(const TDefByClass::const_reference iRow, stor_)
        BOOST_FOREACH(const TDefByFile::const_reference iCol, iRow.second)
            BOOST_FOREACH(const Defect &def, iCol.second)
                if (! /* continue */ visitor(def))
                    return false;

    return true;
}

class DefQueryParser {
    public:
        struct QRow {
            int                         cid;
            std::string                 checker;
            std::string                 fileName;
            std::string                 fnc;

            QRow(): cid(-1) { }
        };

        DefQueryParser():
            lineno_(0),
            hasError_(false)
        {
        }

        bool getNext(QRow &dst);

        bool hasError() const {
            return hasError_;
        }

    private:
        int lineno_;
        bool hasError_;
        bool parse(QRow &dst);
};

#endif /* H_GUARD_DEFQUEUE_H */
