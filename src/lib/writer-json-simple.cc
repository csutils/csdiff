/*
 * Copyright (C) 2011 - 2023 Red Hat, Inc.
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

#include "writer-json-simple.hh"

#include "writer-json-common.hh"

using namespace boost::json;

void SimpleTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    if (scanProps.empty())
        return;

    root_["scan"] = jsonSerializeScanProps(scanProps);
}

void SimpleTreeEncoder::appendDef(const Defect &def)
{
    // go through events
    array evtList;
    for (const DefEvent &evt : def.events) {
        object evtNode;

        // describe the location
        evtNode["file_name"] = evt.fileName;
        evtNode["line"] = evt.line;
        if (0 < evt.column)
            evtNode["column"] = evt.column;
        if (0 < evt.hSize)
            evtNode["h_size"] = evt.hSize;
        if (0 < evt.vSize)
            evtNode["v_size"] = evt.vSize;

        // describe the event
        evtNode["event"] = evt.event;
        evtNode["message"] = sanitizeUTF8(evt.msg);
        evtNode["verbosity_level"] = evt.verbosityLevel;

        // append the event to the list
        evtList.push_back(std::move(evtNode));
    }

    // create a node for a single defect
    object defNode;
    defNode["checker"] = def.checker;
    if (!def.annotation.empty())
        defNode["annotation"] = def.annotation;

    // write "defect_id", "cwe", etc. if available
    if (0 < def.defectId)
        defNode["defect_id"] = def.defectId;
    if (0 < def.cwe)
        defNode["cwe"] = def.cwe;
    if (0 < def.imp)
        defNode["imp"] = def.imp;
    if (!def.function.empty())
        defNode["function"] = def.function;
    if (!def.language.empty())
        defNode["language"] = def.language;
    if (!def.tool.empty())
        defNode["tool"] = def.tool;

    defNode["key_event_idx"] = def.keyEventIdx;
    defNode["events"] = std::move(evtList);

    // create the node representing the list of defects
    if (!pDefects_)
        pDefects_ = &root_["defects"].emplace_array();

    // append the node to the list
    pDefects_->push_back(std::move(defNode));
}

void SimpleTreeEncoder::writeTo(std::ostream &str)
{
    if (!pDefects_)
        // create an empty "defects" node to keep format detection working
        pDefects_ = &root_["defects"].emplace_array();

    jsonPrettyPrint(str, root_);
}
