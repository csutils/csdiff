/*
 * Copyright (C) 2020-2023 Red Hat, Inc.
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

#ifndef H_GUARD_CSV_PARSER_H
#define H_GUARD_CSV_PARSER_H

#include "instream.hh"

#include <vector>
#include <string>

class AbstractCsvParser {
    public:
        AbstractCsvParser();
        virtual ~AbstractCsvParser();
        bool parse(InStream &str);

        void setSilent(const bool silent) {
            this->silent = silent;
        }

    protected:
        using TStringList = std::vector<std::string>;

        virtual bool /* continue */ handleLine(const TStringList &) = 0;
        void parseError(const std::string &msg);

        bool silent = false;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_CSV_PARSER_H */
