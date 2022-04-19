/*
 * Copyright (C) 2011-2022 Red Hat, Inc.
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

#include "defect.hh"
#include "instream.hh"

#include <memory>

/// used only by the JSON format
typedef std::map<std::string, std::string> TScanProps;

enum EFileFormat {
    FF_INVALID = 0,                         ///< for signalling errors
    FF_AUTO,                                ///< choose format automatically
    FF_COVERITY,                            ///< what cov-format-errors produces
    FF_GCC,                                 ///< GCC format
    FF_JSON,                                ///< JSON format
    FF_HTML,                                ///< HTML format (output only)
    FF_SARIF                                ///< SARIF format (used by GitHub)
};

// abstract class with a factory method
class AbstractParser {
    public:
        virtual ~AbstractParser() = default;
        virtual bool getNext(Defect *) = 0;
        virtual bool hasError() const = 0;

        /// used only by the JSON format
        virtual const TScanProps& getScanProps() const {
            return emptyProps_;
        }

    protected:
        AbstractParser() = default;

    private:
        const TScanProps emptyProps_{};
};

using AbstractParserPtr = std::unique_ptr<AbstractParser>;

AbstractParserPtr createParser(InStream &input);

// RAII
class Parser {
    public:
        Parser(InStream &input):
            input_(input),
            parser_(createParser(input))
        {
        }

        ~Parser() = default;

        InStream &input() const {
            return input_;
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

    private:
        Parser(const Parser &);
        Parser& operator=(const Parser &);

        InStream                         &input_;
        std::unique_ptr<AbstractParser>   parser_;
};

#endif /* H_GUARD_ABSTRACT_PARSER_H */
