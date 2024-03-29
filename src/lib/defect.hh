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

#include <limits>
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

// FIXME: move this to a separate header file?
#define RETURN_BY_REF_IF_COMPARED(a, b, member) do {    \
    if (a.member < b.member)                            \
        *pResult = true;                                \
    else if (b.member < a.member)                       \
        *pResult = false;                               \
    else                                                \
        break;                                          \
    return true;                                        \
} while (0)


struct DefEvent {
    std::string         fileName;
    int                 line            = 0;
    int                 column          = 0;
    std::string         event;
    std::string         msg;

    /// 0 = key event,  1 = info event,  2 = trace event
    int                 verbosityLevel  = 0;

    using TNumDiff = unsigned short;
    TNumDiff            hSize           = 0; //< endColumn - startColumn
    TNumDiff            vSize           = 0; //< endLine - startLine

    DefEvent() { }

    explicit DefEvent(const std::string &event):
        event(event)
    {
    }
};

///< return (end - beg) if it is positive and fits into target type, 0 otherwise
inline DefEvent::TNumDiff diffNums(const int beg, const int end)
{
    const int diff = end - beg;
    return (0 < diff && diff < std::numeric_limits<DefEvent::TNumDiff>::max())
        ? diff
        : 0;
}

inline bool cmpEvents(bool *pResult, const DefEvent &a, const DefEvent &b)
{
    RETURN_BY_REF_IF_COMPARED(a, b, fileName);
    RETURN_BY_REF_IF_COMPARED(a, b, line);
    RETURN_BY_REF_IF_COMPARED(a, b, column);
    RETURN_BY_REF_IF_COMPARED(a, b, event);
    RETURN_BY_REF_IF_COMPARED(a, b, msg);
    RETURN_BY_REF_IF_COMPARED(a, b, verbosityLevel);
    RETURN_BY_REF_IF_COMPARED(a, b, hSize);
    RETURN_BY_REF_IF_COMPARED(a, b, vSize);

    // incomparable events
    return false;
}

inline bool operator<(const DefEvent &a, const DefEvent &b)
{
    bool result;
    return cmpEvents(&result, a, b)
        && result;
}

typedef std::vector<DefEvent> TEvtList;

struct Defect {
    std::string         checker;
    std::string         annotation;
    TEvtList            events;
    unsigned            keyEventIdx = 0U;   ///< in range 0..(events.size()-1)
    int                 cwe         = 0;    ///< CWE number, 0 means unused
    int                 imp         = 0;    ///< "important" flag, bool for now
    int                 defectId    = 0;    ///< used only by the JSON format
    std::string         function;           ///< used only by the JSON format
    std::string         language;           ///< used only by the JSON format
    std::string         tool;               ///< used only by the JSON format

    Defect() { }

    explicit Defect(const std::string &checker):
        checker(checker)
    {
    }
};

#endif /* H_GUARD_DEFECT_H */
