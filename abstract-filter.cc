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

#include "abstract-filter.hh"

#include <errno.h>
#include <error.h>
#include <fstream>

bool AbstractEngine::handleFile(const std::string &fileName, bool silent) {
    std::fstream fstr;
    std::istream *pStr = &fstr;

    const char *szFileName = fileName.c_str();
    const bool isFile = !!fileName.compare("-");
    if (isFile)
        fstr.open(szFileName, std::ios::in);
    else
        pStr = &std::cin;

    if (!fstr) {
        error(0, errno, "failed to open %s", szFileName);
        return false;
    }

    this->notifyFile(fileName);

    Parser parser(*pStr, fileName, silent);
    Defect def;
    while (parser.getNext(&def))
        this->handleDef(def);

    if (isFile)
        fstr.close();

    return !parser.hasError();
}
