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
#include <map>
#include <string>
#include <vector>

struct DefEvent {
    std::string             fileName;
    int                     line;
    int                     column;
    std::string             event;
    std::string             msg;

    DefEvent():
        line(0),
        column(0)
    {
    }
};

typedef std::vector<DefEvent> TEvtList;

struct Defect {
    std::string             checker;
    std::string             annotation;
    TEvtList                events;
    unsigned                keyEventIdx;    ///< in range 0..(events.size()-1)
    int                     defectId;       ///< used only by the JSON format
    std::string             function;       ///< used only by the JSON format

    Defect():
        keyEventIdx(0U),
        defectId(0)
    {
    }
};

/// used only by the JSON format
typedef std::map<std::string, std::string> TScanProps;

enum EFileFormat {
    FF_INVALID = 0,                         ///< for signalling errors
    FF_COVERITY,                            ///< what cov-format-errors produces
    FF_JSON                                 ///< JSON format
};

// abstract class with a factory method
class AbstractParser {
    public:
        virtual ~AbstractParser() { }
        virtual bool getNext(Defect *) = 0;
        virtual bool hasError() const = 0;

        /// used only by the JSON format
        virtual const TScanProps& getScanProps() const {
            return emptyProps_;
        }

    private:
        const TScanProps emptyProps_;
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

        const TScanProps& getScanProps() const {
            return parser_->getScanProps();
        }

        EFileFormat inputFormat() const;

        bool isJson() const {
            return FF_JSON == this->inputFormat();
        }

    private:
        Parser(const Parser &);
        Parser& operator=(const Parser &);

        AbstractParser *parser_;
};

#endif /* H_GUARD_ABSTRACT_PARSER_H */
