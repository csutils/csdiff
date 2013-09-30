/*
 * Copyright (C) 2011-2013 Red Hat, Inc.
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

#ifndef H_GUARD_DEFECT_H
#define H_GUARD_DEFECT_H

#include <map>
#include <string>
#include <vector>

// FIXME: move this to a separate header file?
#define RETURN_IF_COMPARED(a, b, member) do {   \
    if (a.member < b.member)                    \
        return true;                            \
    if (b.member < a.member)                    \
        return false;                           \
} while (0)


struct DefEvent {
    std::string             fileName;
    int                     line;
    int                     column;
    std::string             event;
    std::string             msg;

    /// 0 = key event,  2 = trace event,  3 = comment
    int                     verbosityLevel;

    DefEvent():
        line(0),
        column(0),
        verbosityLevel(0)
    {
    }
};

inline bool operator<(const DefEvent &a, const DefEvent &b) {
    RETURN_IF_COMPARED(a, b, fileName);
    RETURN_IF_COMPARED(a, b, line);
    RETURN_IF_COMPARED(a, b, column);
    RETURN_IF_COMPARED(a, b, event);
    RETURN_IF_COMPARED(a, b, msg);
    RETURN_IF_COMPARED(a, b, verbosityLevel);
    return false;
}

typedef std::vector<DefEvent> TEvtList;

struct Defect {
    std::string             checker;
    std::string             annotation;
    TEvtList                events;
    unsigned                keyEventIdx;    ///< in range 0..(events.size()-1)
    int                     cwe;            ///< CWE number, 0 means unused
    int                     defectId;       ///< used only by the JSON format
    std::string             function;       ///< used only by the JSON format

    Defect():
        keyEventIdx(0U),
        cwe(0),
        defectId(0)
    {
    }
};

#endif /* H_GUARD_DEFECT_H */
