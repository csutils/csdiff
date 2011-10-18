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

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

class AnnotationTable {
    public:
        AnnotationTable(std::istream &input, std::string fileName);

        bool lookup(std::string &dst, const std::string &defClass) const;

        bool hasError() const { return hasError_; }

    private:
        typedef std::map<std::string, std::string> TCont;

        TCont       cont_;
        bool        hasError_;
};

AnnotationTable::AnnotationTable(std::istream &input, std::string fileName):
    hasError_(false)
{
    // go through the input line by line
    std::string line;
    for (int lineno = 1; std::getline(input, line); ++lineno) {

        // tokenize the line
        std::vector<std::string> tokens;
        boost::split(tokens, line, boost::algorithm::is_any_of("\t"));
        const unsigned cnt = tokens.size();
        if (2 != cnt) {
            hasError_ = true;
            std::cerr << fileName << ":" << lineno
                << ": error: column count mismatch: " << cnt
                << " (expected 2)\n";

            continue;
        }

        const std::string &ann = tokens[/* ann */ 1];
        if (!ann.compare("N/A"))
            // FIXME: this should be better documented
            continue;

        const std::string &def = tokens[/* def */ 0];
        cont_[def] = ann;
    }
}

bool AnnotationTable::lookup(std::string &dst, const std::string &defClass)
    const
{
    TCont::const_iterator it = cont_.find(defClass);
    if (cont_.end() == it)
        return false;

    // annotation found!
    dst = " (";
    dst += it->second;
    dst += ")";
    return true;
}

int main(int argc, char *argv[])
{
    // check if file names were given
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " annotation_table.txt\n";
        return EXIT_FAILURE;
    }

    // open old
    const char *fileName = argv[1];
    std::fstream str(fileName, std::ios::in);
    if (!str) {
        std::cerr << fileName << ": failed to open input file\n";
        return EXIT_FAILURE;
    }

    AnnotationTable tbl(str, fileName);
    str.close();

    // read from stdin
    Parser pInput(std::cin, "-");
    Defect def;
    while (pInput.getNext(&def)) {
        std::string annotation;

        if (tbl.lookup(annotation, def.defClass))
            // update annotation
            annotation.swap(def.annotation);

        std::cout << def;
    }

    return tbl.hasError()
        || pInput.hasError();
}
