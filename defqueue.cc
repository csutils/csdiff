/*
 * Copyright (C) 2011 - 2012 Red Hat, Inc.
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

#include "defqueue.hh"
#include "csfilter.hh"

#define DEBUG_DEF_MATCH                 0
#define DEBUG_LOOKUP_OFFSET             0

// /////////////////////////////////////////////////////////////////////////////
// implementation of DefQueue

DefQueue::DefQueue():
    filt_(MsgFilter::inst())
{
}

void DefQueue::hashDefect(const Defect &def)
{
    TDefByFile &row = stor_[def.checker];
    const std::string &fileName = def.events[def.keyEventIdx].fileName;
    TDefList &col = row[filt_->filterPath(fileName)];
    col.push_back(def);
}

bool DefQueue::lookup(
        Defect                  &dst,
        const std::string       &checker,
        const std::string       &fileName)
{
    // look for the given defect class
    TDefByClass::iterator iRow = stor_.find(checker);
    if (stor_.end() == iRow) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": not found\n";
#endif
        return false;
    }

    TDefByFile &row = iRow->second;
    if (row.empty()) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": row empty\n";
#endif
        return false;
    }

    // look for the given file name
    std::string path = filt_->filterPath(fileName);
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": " << path << ": not found\n";
#endif
        return false;
    }

    TDefList &col = iCol->second;
    if (col.empty()) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": " << path << ": list empty\n";
#endif
        return false;
    }

    // remove the first defect in the list...
    dst = col.front();
    col.pop_front();
    if (col.empty()) {
        // ... and subsequently the list itself once it becomes empty
        row.erase(iCol);
#if DEBUG_LOOKUP_OFFSET
        std::cerr << checker << ": " << path
            << ": list removed, row.size() = " << row.size() << "\n";
#endif
        if (row.empty()) {
            // ... and eventually also the row where the list belongs to
            stor_.erase(iRow);
#if DEBUG_LOOKUP_OFFSET
            std::cerr << checker << ": row removed, stor_.size() = "
                << stor_.size() << "\n";
#endif
        }
    }

    // TODO: What else should we (and are we able to) check? fnc names?
    return true;
}
