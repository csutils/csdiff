/*
 * Copyright (C) 2014 Red Hat, Inc.
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

#include "color.hh"

#include <unistd.h>

ColorWriter::ColorWriter(const std::ostream &str, const EColorMode cm)
{
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

const char* ColorWriter::setColor(const EColor color)
{
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

const char* ColorWriter::setColorIf(bool cond, const EColor color)
{
    return (cond) ? this->setColor(color) : "";
}
