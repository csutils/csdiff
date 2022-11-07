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

#include "writer.hh"

class CweNameLookup;
class DefLookup;

class HtmlWriter: public AbstractWriter {
    public:
        HtmlWriter(
                std::ostream                &outputStream,
                const std::string           &titleFallback,
                const std::string           &defUrlTemplate,
                const std::string           &spPlacement);

        ~HtmlWriter() override;

        const TScanProps& getScanProps() const override;
        void setScanProps(const TScanProps &) override;

        void handleDef(const Defect &def) override;
        void flush() override;

        /// @attention baseLookup needs to stay valid long enough (no deep copy)
        void setDiffBase(
                DefLookup                   *baseLookup,
                const std::string           &checkerIgnRegex,
                const TScanProps            &baseProps,
                const std::string           &baseTitleFallback);

        void setPlainTextUrl(const std::string &);

        /// @attention cweNames needs to stay valid long enough (no deep copy)
        void setCweNameLookup(const CweNameLookup *cweNames);

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_HTML_WRITER_H */
