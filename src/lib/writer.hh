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

#ifndef H_GUARD_WRITER_H
#define H_GUARD_WRITER_H

#include "parser.hh"
#include "color.hh"

#include <memory>

// FIXME: misleading class name
class AbstractWriter {
    public:
        virtual void handleDef(const Defect &def) = 0;
        virtual void notifyFile(const std::string &) { }

        AbstractWriter() = default;

        AbstractWriter(const AbstractWriter &) = delete;
        AbstractWriter& operator=(const AbstractWriter &) = delete;
        AbstractWriter(AbstractWriter &&) noexcept = delete;
        AbstractWriter& operator=(AbstractWriter &&) noexcept = delete;

        virtual ~AbstractWriter() = default;

        virtual void flush() { };

        bool handleFile(Parser &parser);

        bool handleFile(InStream &);

        bool handleFile(const std::string &fileName, bool silent);

        EFileFormat inputFormat() const {
            return inputFormat_;
        }

        virtual const TScanProps& getScanProps() const {
            return emptyProps_;
        }

        virtual void setScanProps(const TScanProps &);


    private:
        EFileFormat                 inputFormat_ = FF_INVALID;
        const TScanProps            emptyProps_{};
};

using TWriterPtr = std::unique_ptr<AbstractWriter>;

TWriterPtr createWriter(
        std::ostream               &strDst,
        EFileFormat                 format,
        EColorMode                  cm        = CM_AUTO,
        const TScanProps           &scanProps = TScanProps());

class CtxEventDetector {
    public:
        CtxEventDetector();
        ~CtxEventDetector();

        bool isAnyCtxLine(const DefEvent &evt) const;
        bool isKeyCtxLine(const DefEvent &evt) const;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

#endif /* H_GUARD_WRITER_H */
