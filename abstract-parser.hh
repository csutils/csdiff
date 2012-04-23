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

#ifndef H_GUARD_ABSTRACT_PARSER_H
#define H_GUARD_ABSTRACT_PARSER_H

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

typedef std::vector<DefEvent> TEvtList;

struct Defect {
    std::string             defClass;
    std::string             annotation;
    TEvtList                events;
    unsigned                keyEventIdx;    ///< in range 0..(events.size()-1)
};

// abstract class with a factory method
class AbstractParser {
    public:
        virtual ~AbstractParser() { }
        virtual bool getNext(Defect *) = 0;
        virtual bool hasError() const = 0;
};

AbstractParser* createParser(
        std::istream        &input,
        const std::string   &fileName,
        const bool          silent);

// RAII
class Parser {
    public:
        Parser(
                std::istream        &input,
                const std::string   &fileName,
                const bool          silent = false):
            parser_(createParser(input, fileName, silent))
        {
        }

        ~Parser() {
            delete parser_;
        }

        bool getNext(Defect *def) {
            return parser_->getNext(def);
        }

        bool hasError() const {
            return parser_->hasError();
        }

        bool isJson() const;

    private:
        Parser(const Parser &);
        Parser& operator=(const Parser &);

        AbstractParser *parser_;
};

#endif /* H_GUARD_ABSTRACT_PARSER_H */
