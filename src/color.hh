/*
 * Copyright (C) 2014-2022 Red Hat, Inc.
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

#ifndef H_GUARD_COLOR_H
#define H_GUARD_COLOR_H

#include <iostream>

enum EColorMode {
    CM_AUTO,
    CM_NEVER,
    CM_ALWAYS
};

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
        const char* setColor(EColor) const;
        const char* setColorIf(bool, EColor) const;

    private:
        bool enabled_;
};

template <class TOptDesc>
void addColorOptions(TOptDesc *desc)
{
    desc->add_options()
        ("color",
         "use colorized console output (default if connected to a terminal)")
        ("no-color",
         "do not use colorized console output");
}

template <class TValMap>
bool readColorOptions(EColorMode *pDst, const char **pErr, const TValMap &vm)
{
    const bool colorAlways = vm.count("color");
    const bool colorNever = vm.count("no-color");
    if (colorAlways && colorNever) {
        *pErr = "options --color and --no-color are mutually exclusive";
        return false;
    }

    if (colorAlways)
        *pDst = CM_ALWAYS;
    else if (colorNever)
        *pDst = CM_NEVER;
    else
        *pDst = CM_AUTO;

    return true;
}

#endif /* H_GUARD_COLOR_H */
