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

#include "csparser.hh"
#include "deflookup.hh"

#include <cstdlib>
#include <fstream>

int main(int argc, char *argv[])
{
    // check if file names were given
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " old.err new.err\n";
        return EXIT_FAILURE;
    }

    // open old
    const char *fnOld = argv[1];
    std::fstream strOld(fnOld, std::ios::in);
    if (!strOld) {
        std::cerr << fnOld << ": failed to open input file\n";
        return EXIT_FAILURE;
    }

    // open new
    const char *fnNew = argv[2];
    std::fstream strNew(fnNew, std::ios::in);
    if (!strNew) {
        std::cerr << fnNew << ": failed to open input file\n";
        strOld.close();
        return EXIT_FAILURE;
    }

    // read old
    Parser pOld(strOld, fnOld);
    DefLookup stor;
    Defect def;
    while (pOld.getNext(&def))
        stor.hashDefect(def);

    // read new
    Parser pNew(strNew, fnNew);
    while (pNew.getNext(&def)) {
        if (stor.lookup(def))
            continue;

        // a newly added defect found
        std::cout << def;
    }

    // close streams
    strOld.close();
    strNew.close();

    return pOld.hasError()
        || pNew.hasError();
}
