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

#ifndef H_GUARD_INSTREAM_H
#define H_GUARD_INSTREAM_H

#include <fstream>
#include <iostream>
#include <string>

struct InFileException {
    std::string fileName;
    // TODO: details (errno?)

    InFileException(const std::string &fileName_):
        fileName(fileName_)
    {
    }
};

class InStream {
    public:
        InStream(const std::string &fileName);
        ~InStream();

        const std::string& fileName()   const { return fileName_;   }
        std::istream& str()             const { return str_;        }

    private:
        std::string         fileName_;
        std::fstream        fileStr_;
        std::istream       &str_;
};

#endif /* H_GUARD_INSTREAM_H */
