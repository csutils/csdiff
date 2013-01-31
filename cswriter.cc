/*
 * Copyright (C) 2012 Red Hat, Inc.
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

#include "cswriter.hh"

#include <boost/foreach.hpp>

struct CovWriter::Private {
    std::ostream       &str;
    bool                writing;

    Private(std::ostream &str_):
        str(str_),
        writing(false)
    {
    }
};

CovWriter::CovWriter(std::ostream &str):
    d(new Private(str))
{
}

CovWriter::~CovWriter() {
    delete d;
}

void CovWriter::handleDef(const Defect &def) {
    std::ostream &str = d->str;

    if (d->writing)
        str << std::endl;
    else
        d->writing = true;

    str << "Error: " << def.checker;
    if (def.cwe)
        str << " (CWE-" << def.cwe << ")";
    else
        str << def.annotation;
    str << ":\n";

    BOOST_FOREACH(const DefEvent &evt, def.events) {
        str << evt.fileName << ":";
        
        if (0 < evt.line)
            str << evt.line << ":";

        if (0 < evt.column)
            str << evt.column << ":";

        str << " ";

        if (!evt.event.empty())
            str << evt.event << ": ";

        str << evt.msg << "\n";
    }
}

void CovWriter::flush() {
    d->str.flush();
}
