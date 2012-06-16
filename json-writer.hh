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

#ifndef H_GUARD_JSON_WRITER_H
#define H_GUARD_JSON_WRITER_H

#include "abstract-writer.hh"

class JsonWriter: public AbstractWriter {
    public:
        JsonWriter();
        virtual ~JsonWriter();

        virtual const TScanProps& getScanProps() const;
        virtual void setScanProps(const TScanProps &);

        virtual void handleDef(const Defect &def);
        virtual void flush();

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_JSON_WRITER_H */
