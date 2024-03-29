/*
 * Copyright (C) 2024 Red Hat, Inc.
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

#ifndef H_GUARD_FINGER_PRINT_H
#define H_GUARD_FINGER_PRINT_H

#include "defect.hh"

#include <memory>

enum EFingerPrintVer {
    FPV_CSDIFF = 0,
    FPV_CSDIFF_WITH_LINE_CONTENT,
    FPV_MAX                             ///< always the last item
};

class FingerPrinter {
    public:
        FingerPrinter(const Defect &);
        ~FingerPrinter();

        /// return fingerprint of the selected kind
        std::string getHash(EFingerPrintVer) const;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

#endif /* H_GUARD_FINGER_PRINT_H */
