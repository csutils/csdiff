/*
 * Copyright (C) 2011 Red Hat, Inc.
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

#ifndef H_GUARD_CSFILTER_H
#define H_GUARD_CSFILTER_H

#include "instream.hh"

#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> TStringList;
typedef std::map<std::string, std::string> TSubstMap;

class MsgFilter {
    public:
        // singleton
        static MsgFilter* inst() {
            return (self_)
                ? (self_)
                : (self_ = new MsgFilter);
        }

        void setIgnorePath(bool);
        bool setFilterFiles(const TStringList &fileNames,
                            bool               silent);
        void setFileNameSubstitution(
                const std::string      &oldFile,
                const std::string      &newFile);

        std::string filterMsg(
                const std::string &msg,
                const std::string &checker);
        std::string filterPath(const std::string &path);

    private:
        MsgFilter();
        ~MsgFilter();

        bool setJSONFilter(InStream &filter);

        static MsgFilter *self_;
        struct Private;
        Private *d;
};

#endif /* H_GUARD_CSFILTER_H */
