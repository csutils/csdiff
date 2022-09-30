/*
 * Copyright (C) 2011-2020 Red Hat, Inc.
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

#ifndef H_GUARD_PARSER_COMMON_H
#define H_GUARD_PARSER_COMMON_H

#include "defect.hh"

#include <string>

#define RE_CHECKER_NAME_SA "(?:[A-Za-z][0-9A-Za-z_.]+)"
#define RE_CHECKER_NAME_CERT "(?:CERT [0-9A-Z-]+-C)"
#define RE_CHECKER_NAME_MISRA "(?:MISRA C(?:\\+\\+)?-[0-9]+ (?:Directive|Rule) [0-9.-]+)"
#define RE_CHECKER_NAME RE_CHECKER_NAME_SA "|" RE_CHECKER_NAME_CERT "|" RE_CHECKER_NAME_MISRA

#define RE_EVENT_GCC "(?:(?:(?:fatal|internal) )?[A-Za-z][A-Za-z0-9_-]+)(?:\\[[^ \\]]+\\])?"
#define RE_EVENT_PROSPECTOR "(?:[A-Z]+[0-9]+\\[[a-z0-9-]+\\])"
#define RE_EVENT RE_EVENT_GCC "|" RE_EVENT_PROSPECTOR

int parse_int(const std::string &, int fallback = 0);

class ImpliedAttrDigger {
    public:
        ImpliedAttrDigger();
        ~ImpliedAttrDigger();

        void inferLangFromChecker(Defect *, bool onlyIfMissing = true) const;
        void inferToolFromChecker(Defect *, bool onlyIfMissing = true) const;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_PARSER_COMMON_H */
