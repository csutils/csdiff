/*
 * Copyright (C) 2013 Red Hat, Inc.
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

#ifndef H_GUARD_GCC_PARSER_H
#define H_GUARD_GCC_PARSER_H

#include "abstract-parser.hh"

class GccParser: public AbstractParser {
    public:
        GccParser(InStream &input);

        ~GccParser() override;
        bool getNext(Defect *) override;
        bool hasError() const override;

    private:
        GccParser(const Parser &);
        GccParser& operator=(const Parser &);

        struct Private;
        Private *d;
};

class GccPostProcessor {
    public:
        GccPostProcessor();
        ~GccPostProcessor();

        /// apply final transformations on a successfully parsed defect
        void apply(Defect *pDef) const;

    private:
        GccPostProcessor(const GccPostProcessor &);
        GccPostProcessor& operator=(const GccPostProcessor &);

        struct Private;
        Private *d;
};


#endif /* H_GUARD_GCC_PARSER_H */
