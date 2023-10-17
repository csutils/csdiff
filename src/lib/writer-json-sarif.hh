/*
 * Copyright (C) 2011 - 2023 Red Hat, Inc.
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

#ifndef H_GUARD_WRITER_JSON_SARIF_H
#define H_GUARD_WRITER_JSON_SARIF_H

#include "abstract-tree.hh"
#include "writer.hh"                // for CtxEventDetector

#include <boost/json.hpp>

// SARIF 2.1.0 is documented at:
// https://docs.github.com/en/code-security/code-scanning/integrating-with-code-scanning/sarif-support-for-code-scanning
// specification: https://docs.oasis-open.org/sarif/sarif/v2.1.0/os/sarif-v2.1.0-os.html
// validation: https://sarifweb.azurewebsites.net/Validation
class SarifTreeEncoder: public AbstractTreeEncoder {
    public:
        SarifTreeEncoder();
        ~SarifTreeEncoder();

        /// import supported scan properties
        void importScanProps(const TScanProps &) override;

        /// append single defect
        void appendDef(const Defect &) override;

        /// write everything to the given output stream
        void writeTo(std::ostream &) override;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

#endif /* H_GUARD_WRITER_JSON_SARIF_H */
