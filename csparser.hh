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

#ifndef H_GUARD_CSPARSER_H
#define H_GUARD_CSPARSER_H

#include <iostream>
#include <string>
#include <vector>

struct DefEvent {
    std::string             fileName;
    int                     line;
    int                     column;
    std::string             event;
    std::string             msg;
};

struct Defect {
    std::string             defClass;
    std::string             annotation;
    std::vector<DefEvent>   events;
    unsigned                keyEventIdx;    ///< in range 0..(events.size()-1)
};

std::ostream& operator<<(std::ostream &str, const Defect &def);

class Parser {
    public:
        Parser(std::istream &input, std::string fileName, bool silent = false);
        ~Parser();
        bool getNext(Defect *);
        bool hasError() const;

    private:
        Parser(const Parser &);
        Parser& operator=(const Parser &);

        struct Private;
        Private *d;
};

#endif /* H_GUARD_CSPARSER_H */
