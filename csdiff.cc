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
#include "instream.hh"

#include <cstdlib>

int main(int argc, char *argv[])
{
    // check if file names were given
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " old.err new.err\n";
        return EXIT_FAILURE;
    }

    try {
        // open old
        const char *fnOld = argv[1];
        InStream strOld(fnOld);

        // open new
        const char *fnNew = argv[2];
        InStream strNew(fnNew);

        // read old
        Parser pOld(strOld.str(), fnOld);
        DefLookup stor;
        Defect def;
        while (pOld.getNext(&def))
            stor.hashDefect(def);

        // read new
        Parser pNew(strNew.str(), fnNew);
        while (pNew.getNext(&def)) {
            if (stor.lookup(def))
                continue;

            // a newly added defect found
            std::cout << def;
        }

        return pOld.hasError()
            || pNew.hasError();
    }
    catch (const InFileException &e) {
        std::cerr << e.fileName << ": failed to open input file\n";
        return EXIT_FAILURE;
    }
}
