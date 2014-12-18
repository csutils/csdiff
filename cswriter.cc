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

#include <unistd.h>

#include <boost/foreach.hpp>

enum EColor {
    C_NO_COLOR,
    C_DARK_GRAY,
    C_LIGHT_GREEN,
    C_LIGHT_CYAN,
    C_WHITE
};

class ColorWriter {
    public:
        ColorWriter(const std::ostream &str, EColorMode);
        const char* setColor(EColor);
        const char* setColorIf(bool, EColor);

    private:
        bool enabled_;
};

ColorWriter::ColorWriter(const std::ostream &str, const EColorMode cm) {
    switch (cm) {
        case CM_NEVER:
            enabled_ = false;
            break;

        case CM_ALWAYS:
            enabled_ = true;
            break;

        case CM_AUTO:
        default:
            enabled_ = (&str == &std::cout)
                && isatty(STDOUT_FILENO);
    }
}

const char* ColorWriter::setColor(const EColor color) {
    if (!enabled_)
        return "";

    switch (color) {
        case C_NO_COLOR:        return "\033[0m";
        case C_DARK_GRAY:       return "\033[1;30m";
        case C_LIGHT_GREEN:     return "\033[1;32m";
        case C_LIGHT_CYAN:      return "\033[1;36m";
        case C_WHITE:           return "\033[1;37m";
    }

    return "";
}

const char* ColorWriter::setColorIf(bool cond, const EColor color) {
    return (cond) ? this->setColor(color) : "";
}

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

CovWriter::~CovWriter() {
    delete d;
}

void CovWriter::handleDef(const Defect &def) {
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

    BOOST_FOREACH(const DefEvent &evt, def.events) {
        const bool isKeyEvt = !evt.verbosityLevel;
        if (!isKeyEvt)
            str << d->cw.setColor(C_DARK_GRAY);

        if (!evt.fileName.empty())
            str << evt.fileName << ":";
        
        if (0 < evt.line)
            str << evt.line << ":";

        if (0 < evt.column)
            str << evt.column << ":";

        if (evt.event == "#")
            str << d->cw.setColor(C_LIGHT_CYAN) << "#";

        else {
            str << " ";
            if (!evt.event.empty())
                str << d->cw.setColorIf(isKeyEvt, C_WHITE) << evt.event
                    << d->cw.setColorIf(isKeyEvt, C_NO_COLOR) << ": ";
        }

        str << evt.msg << d->cw.setColor(C_NO_COLOR) << "\n";
    }
}

void CovWriter::flush() {
    d->str.flush();
}
