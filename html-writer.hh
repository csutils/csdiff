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

#ifndef H_GUARD_HTML_WRITER_H
#define H_GUARD_HTML_WRITER_H

#include "abstract-writer.hh"

class DefLookup;

class HtmlWriter: public AbstractWriter {
    public:
        HtmlWriter(
                std::ostream                &outputStream,
                const std::string           &titleFallback,
                const std::string           &defUrlTemplate,
                const std::string           &spPlacement);

        virtual ~HtmlWriter();

        virtual const TScanProps& getScanProps() const;
        virtual void setScanProps(const TScanProps &);

        virtual void handleDef(const Defect &def);
        virtual void flush();

        /// @attention baseLookup needs to stay valid long enough (no deep copy)
        void setDiffBase(
                DefLookup                   *baseLookup,
                const TScanProps            &baseProps,
                const std::string           &baseTitleFallback);

        void setPlainTextUrl(const std::string &);

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_HTML_WRITER_H */
