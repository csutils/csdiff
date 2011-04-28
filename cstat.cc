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

#include <errno.h>
#include <error.h>

#include <cstdlib>
#include <fstream>
#include <map>

#include <boost/foreach.hpp>

class AbstractEngine {
    protected:
        virtual void handleDef(const Defect &def) = 0;

    public:
        virtual ~AbstractEngine() { }

        bool handleFile(const std::string &fileName) {
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

            Parser parser(*pStr, fileName);
            Defect def;
            while (parser.getNext(&def))
                this->handleDef(def);

            if (isFile)
                fstr.close();

            return !parser.hasError();
        }

        virtual void flush() { };
};

class DefCounter: public AbstractEngine {
    private:
        typedef std::map<std::string, int> TMap;
        TMap cnt_;

    public:
        virtual void handleDef(const Defect &def) {
            ++cnt_[def.defClass];
        }

        virtual void flush() {
            BOOST_FOREACH(TMap::const_reference item, cnt_) {
                std::cout << item.second << "\t" << item.first << "\n";
            }
        }
};

int main(int argc, char *argv[])
{
    using std::string;
    if (argc < 1)
        abort();

    DefCounter dc;
    bool hasError = false;
    const string dash("-");

    if (1 == argc) {
        // read from stdin
        hasError = !dc.handleFile("-");
        dc.flush();
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
        if (dash == arg && !dc.handleFile("-"))
            hasError = true;
    }

    // go through the given arguments
    for (int i = 1; i < argc; ++i) {
        const char *fileName = argv[i];
        if (dash == string(fileName))
            // already handled
            continue;

        if (!dc.handleFile(fileName))
            hasError = true;
    }

    // print the summarized statistics
    dc.flush();
    return hasError;
}
