/*
 * Copyright (C) 2011-2012 Red Hat, Inc.
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

#include "abstract-parser.hh"
#include "color.hh"

#include <iostream>
#include <string>

bool /* anyError */ diffScans(
        std::ostream               &strDst,
        std::istream               &strOld,
        std::istream               &strNew,
        const std::string          &fnOld       = std::string(),
        const std::string          &fnNew       = std::string(),
        bool                        showInternal= false,
        bool                        silent      = true,
        EFileFormat                 format      = FF_AUTO,
        EColorMode                  cm          = CM_AUTO);
