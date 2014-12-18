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
        const char* setColor(EColor);
        const char* setColorIf(bool, EColor);

    private:
        bool enabled_;
};

#endif /* H_GUARD_COLOR_H */
