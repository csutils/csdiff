/*
 * Copyright (C) 2012 - 2014 Red Hat, Inc.
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

#include "writer-cov.hh"

struct CovWriter::Private {
    std::ostream       &str;
    ColorWriter         cw;
    bool                writing;

    Private(std::ostream &str_, const EColorMode cm_):
        str(str_),
        cw(str_, cm_),
        writing(false)
    {
    }
};

CovWriter::CovWriter(std::ostream &str, const EColorMode cm):
    d(new Private(str, cm))
{
}

CovWriter::~CovWriter()
{
    delete d;
}

void CovWriter::handleDef(const Defect &def)
{
    std::ostream &str = d->str;

    if (d->writing)
        str << std::endl;
    else
        d->writing = true;

    str << d->cw.setColor(C_WHITE) << "Error: "
        << d->cw.setColor(C_LIGHT_GREEN) << def.checker
        << d->cw.setColor(C_WHITE);
    if (def.cwe)
        str << " (CWE-" << def.cwe << ")";
    else
        str << def.annotation;
    str << d->cw.setColor(C_NO_COLOR) << ":\n";

    for (const DefEvent &evt : def.events) {
        const bool isKeyEvt = !evt.verbosityLevel;
        if (!isKeyEvt)
            str << d->cw.setColor(C_DARK_GRAY);

        if (evt.event == "#") {
            // comment --> ignore location info
            str << d->cw.setColor(C_LIGHT_CYAN) << "#";

            static CtxEventDetector detector;
            if (detector.isAnyCtxLine(evt)) {
                const EColor color = detector.isKeyCtxLine(evt)
                    ? C_WHITE
                    : C_DARK_GRAY;
                str << d->cw.setColor(color);
            }
        }
        else {
            // write file name
            std::string fn = evt.fileName;
            if (fn.empty())
                fn = "<unknown>";
            str << fn << ":";
        
            // write line/col
            if (0 < evt.line) {
                str << evt.line << ":";
                if (0 < evt.column)
                    str << evt.column << ":";
            }

            // write event
            str << " ";
            if (!evt.event.empty())
                str << d->cw.setColorIf(isKeyEvt, C_WHITE) << evt.event
                    << d->cw.setColorIf(isKeyEvt, C_NO_COLOR) << ": ";
        }

        str << evt.msg << d->cw.setColor(C_NO_COLOR) << "\n";
    }
}

void CovWriter::flush()
{
    d->str.flush();
}

// only to prevent AbstractWriter::setScanProps() from printing a warning
void CovWriter::setScanProps(const TScanProps &)
{
}
