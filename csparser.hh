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

#ifndef H_GUARD_CSPARSER_H
#define H_GUARD_CSPARSER_H

#include "abstract-parser.hh"

class CovParser: public AbstractParser {
    public:
        CovParser(
                std::istream        &input,
                const std::string   &fileName,
                const bool           silent);

        virtual ~CovParser();
        bool getNext(Defect *);
        bool hasError() const;

    private:
        CovParser(const Parser &);
        CovParser& operator=(const Parser &);

        struct Private;
        Private *d;
};

class KeyEventDigger {
    public:
        KeyEventDigger();
        ~KeyEventDigger();

        /// initialize def->keyEventIdx, return true on success
        bool guessKeyEvent(Defect *def);

        /// initialize def->verbosityLevel
        void initVerbosity(Defect *def);

    private:
        KeyEventDigger(const KeyEventDigger &);
        KeyEventDigger& operator=(const KeyEventDigger &);

        struct Private;
        Private *d;
};

#endif /* H_GUARD_CSPARSER_H */
