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

#ifndef H_GUARD_SHARED_STRING_H
#define H_GUARD_SHARED_STRING_H

#include <set>
#include <string>

class SharedStr {
    public:
        SharedStr();
        SharedStr(int i);
        SharedStr(const std::string &str);
        void writeOut(std::string *pDst) const;
        void swap(SharedStr &);

    private:
        typedef std::set<std::string>   TStor;
        static TStor                    stor_;
        TStor::iterator                 iter_;
        void hashStr(const std::string &);
};

#endif /* H_GUARD_SHARED_STRING_H */
