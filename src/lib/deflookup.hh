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

#ifndef H_GUARD_DEFLOOKUP_H
#define H_GUARD_DEFLOOKUP_H

struct Defect;

class DefLookup {
    public:
        DefLookup(bool usePartialResults = false);
        ~DefLookup();

        DefLookup(const DefLookup &);
        DefLookup& operator=(const DefLookup &);

        void hashDefect(const Defect &);
        bool lookup(const Defect &);

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_DEFLOOKUP_H */
