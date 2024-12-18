/*
 * Copyright (C) 2012 Red Hat, Inc.
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

#ifndef H_GUARD_WRITER_COV_H
#define H_GUARD_WRITER_COV_H

#include "abstract-filter.hh"

class CovWriter: public AbstractWriter {
    public:
        CovWriter(std::ostream &, EColorMode cm = CM_AUTO);
        ~CovWriter() override;

        void handleDef(const Defect &def) override;
        void flush() override;
        void setScanProps(const TScanProps &) override;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_WRITER_COV_H */
