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
#include "color.hh"

// FIXME: misleading class name
class AbstractWriter {
    public:
        virtual void handleDef(const Defect &def) = 0;
        virtual void notifyFile(const std::string &) { }

    public:
        AbstractWriter():
            inputFormat_(FF_INVALID)
        {
        }

        virtual ~AbstractWriter() { }

        virtual void flush() { };

        bool handleFile(Parser &parser, const std::string &fileName);

        bool handleFile(InStream &, bool silent);

        bool handleFile(const std::string &fileName, bool silent);

        EFileFormat inputFormat() const {
            return inputFormat_;
        }

        virtual const TScanProps& getScanProps() const {
            return emptyProps_;
        }

        virtual void setScanProps(const TScanProps &);

    private:
        AbstractWriter(const AbstractWriter &);
        AbstractWriter& operator=(const AbstractWriter &);

    private:
        EFileFormat                 inputFormat_;
        const TScanProps            emptyProps_;
};

AbstractWriter* createWriter(
        std::ostream               &strDst,
        const EFileFormat           format,
        const EColorMode            cm        = CM_AUTO,
        const TScanProps           &scanProps = TScanProps());

class CtxEventDetector {
    public:
        CtxEventDetector();
        ~CtxEventDetector();

        bool isAnyCtxLine(const DefEvent &evt) const;
        bool isKeyCtxLine(const DefEvent &evt) const;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_ABSTRACT_WRITER_H */
