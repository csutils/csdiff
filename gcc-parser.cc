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

#include "gcc-parser.hh"

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

struct GccParser::Private {
    std::istream               &input;
    const std::string           fileName;
    const bool                  silent;
    const boost::regex          reLine;
    int                         lineNo;
    bool                        hasError;

    Private(
            std::istream       &input_,
            const std::string  &fileName_,
            const bool          silent_):
        input(input_),
        fileName(fileName_),
        silent(silent_),
        reLine("^([^:]+)(?::([0-9]+))?(?::([0-9]+))?: ([a-z]+): (.*)$"),
        lineNo(0),
        hasError(false)
    {
    }

    bool parseLine(Defect *def, const std::string &line);
};

GccParser::GccParser(
        std::istream           &input,
        const std::string      &fileName,
        const bool              silent):
    d(new Private(input, fileName, silent))
{
}

GccParser::~GccParser() {
    delete d;
}

bool GccParser::Private::parseLine(Defect *def, const std::string &line) {
    this->lineNo++;

    boost::smatch sm;
    if (!boost::regex_match(line, sm, this->reLine)) {
        this->hasError = true;
        if (!this->silent)
            std::cerr << this->fileName << ":" << this->lineNo
                << ": error: invalid syntax\n";

        return false;
    }

    // append a single event
    def->events.resize(1U);
    DefEvent &evt = def->events.front();

    // read file name, event, and msg
    evt.fileName    = sm[/* file */ 1];
    evt.event       = sm[/* evt  */ 4];
    evt.msg         = sm[/* msg  */ 5];

    // parse line number
    try {
        evt.line = boost::lexical_cast<int>(sm[/* line */ 2]);
    }
    catch (boost::bad_lexical_cast &) {
        evt.line = 0;
    }

    // parse column number
    try {
        evt.column = boost::lexical_cast<int>(sm[/* col */ 3]);
    }
    catch (boost::bad_lexical_cast &) {
        evt.column = 0;
    }

    return true;
}

bool GccParser::getNext(Defect *def) {
    // error recovery loop
    for (;;) {
        std::string line;
        if (!std::getline(d->input, line))
            return false;

        if (d->parseLine(def, line))
            return true;
    }
}

bool GccParser::hasError() const {
    return d->hasError;
}
