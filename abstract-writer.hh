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

#ifndef H_GUARD_ABSTRACT_WRITER_H
#define H_GUARD_ABSTRACT_WRITER_H

#include "abstract-parser.hh"

class AbstractWriter {
    public:
        virtual void handleDef(const Defect &def) = 0;
        virtual void notifyFile(const std::string &) { }

    public:
        AbstractWriter() { }
        virtual ~AbstractWriter() { }

        bool handleFile(const std::string &fileName, bool silent);

        virtual void flush() { };

    private:
        AbstractWriter(const AbstractWriter &);
        AbstractWriter& operator=(const AbstractWriter &);
};

#endif /* H_GUARD_ABSTRACT_WRITER_H */
