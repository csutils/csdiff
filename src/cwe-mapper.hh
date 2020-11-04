/*
 * Copyright (C) 2013 Red Hat, Inc.
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

#ifndef H_GUARD_CWE_MAPPER_H
#define H_GUARD_CWE_MAPPER_H

#include "abstract-filter.hh"

#include <iostream>

class CweMap {
    public:
        CweMap();
        ~CweMap();

        bool loadCweMap(std::istream &, const std::string &fileName);
        bool assignCwe(Defect &def) const;
        bool empty() const;
        void setSilent(bool);

    private:
        struct Private;
        Private *d;
};

class CweMapDecorator: public GenericAbstractFilter {
    public:
        /// @param writer the instance will be deleted on destruction
        CweMapDecorator(AbstractWriter *writer, bool silent);
        virtual ~CweMapDecorator();

        virtual void handleDef(const Defect &def);

        CweMap& cweMap();

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_CWE_MAPPER_H */
