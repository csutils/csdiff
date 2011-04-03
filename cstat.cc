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

#include <cstdlib>
#include <fstream>
#include <map>

#include <boost/foreach.hpp>

typedef std::map<std::string, int> TDefCounter;

namespace {

bool countDeffects(TDefCounter &dc, std::istream &str, const char *fileName) {
    Parser parser(str, fileName);

    // go through the contents
    Defect def;
    while (parser.getNext(&def))
        ++dc[def.defClass];

    return !parser.hasError();
}

bool countDeffectsCin(TDefCounter &dc) {
    return countDeffects(dc, std::cin, "-");
}

void printStats(const TDefCounter &dc) {
    BOOST_FOREACH(TDefCounter::const_reference item, dc) {
        std::cout << item.second << "\t" << item.first << "\n";
    }
}

} // namespace

int main(int argc, char *argv[])
{
    using std::string;
    if (argc < 1)
        abort();

    // initialize counter
    TDefCounter dc;
    bool hasError = false;
    const string dash("-");

    if (1 == argc) {
        // read from stdin
        hasError = !countDeffectsCin(dc);
        printStats(dc);
        return !hasError;
    }

    // scan args for "-" and "--help"
    for (int i = 1; i < argc; ++i) {
        const string arg(argv[i]);
        if (arg == string("--help")) {
            std::cerr << "Usage: " << argv[0] << " [file1.err [...]]\n";
            return 0;
        }

        // "-" means "read from stdin"
        if (dash == arg && !countDeffectsCin(dc))
            hasError = true;
    }

    // go through the given arguments
    for (int i = 1; i < argc; ++i) {
        const char *fileName = argv[i];
        if (dash == string(fileName))
            // already handled
            continue;

        // open a file
        std::fstream fstr(fileName, std::ios::in);
        if (!fstr) {
            std::cerr << fileName << ": failed to open input file\n";
            return false;
        }

        // read from stream
        if (!countDeffects(dc, fstr, fileName))
            hasError = true;

        // close stream
        fstr.close();
    }

    // print the summarized statistics
    printStats(dc);
    return hasError;
}
