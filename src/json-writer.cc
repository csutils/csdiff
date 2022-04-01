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

#include "json-writer.hh"

#include "abstract-tree.hh"
#include "regex.hh"
#include "shared-string-ptree.hh"

#include <queue>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/property_tree/json_parser.hpp>

typedef SharedStringPTree PTree;

class SimpleTreeEncoder: public AbstractTreeEncoder {
    public:
        /// import supported scan properties
        void importScanProps(const TScanProps &) override;

        /// append single defect
        void appendDef(const Defect &) override;

        /// write everything to the given output stream
        void writeTo(std::ostream &) override;

    private:
        PTree                       root_;
        PTree                      *pDefects_ = nullptr;
};

void SimpleTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    if (scanProps.empty())
        return;

    PTree scan;
    for (TScanProps::const_reference prop : scanProps)
        scan.put<std::string>(prop.first, prop.second);

    root_.put_child("scan", scan);
}

void SimpleTreeEncoder::appendDef(const Defect &def)
{
    using std::string;

    // go through events
    PTree evtList;
    for (const DefEvent &evt : def.events) {
        PTree evtNode;

        // describe the location
        evtNode.put<string>("file_name", evt.fileName);
        evtNode.put<int>("line", evt.line);
        if (0 < evt.column)
            evtNode.put<int>("column", evt.column);

        // describe the event
        evtNode.put<string>("event", evt.event);
        evtNode.put<string>("message", evt.msg);
        evtNode.put<int>("verbosity_level", evt.verbosityLevel);

        // append the event to the list
        evtList.push_back(std::make_pair("", evtNode));
    }

    // create a node for a single defect
    PTree defNode;
    defNode.put<string>("checker", def.checker);
    if (!def.annotation.empty())
        defNode.put<string>("annotation", def.annotation);

    // write "defect_id", "cwe", etc. if available
    if (0 < def.defectId)
        defNode.put<int>("defect_id", def.defectId);
    if (0 < def.cwe)
        defNode.put<int>("cwe", def.cwe);
    if (0 < def.imp)
        defNode.put<int>("imp", def.imp);
    if (!def.function.empty())
        defNode.put<string>("function", def.function);
    if (!def.language.empty())
        defNode.put<string>("language", def.language);

    defNode.put<int>("key_event_idx", def.keyEventIdx);
    defNode.put_child("events", evtList);

    // create the node representing the list of defects
    if (!pDefects_)
        pDefects_ = &root_.put_child("defects", PTree());

    // append the node to the list
    pDefects_->push_back(std::make_pair("", defNode));
}

void SimpleTreeEncoder::writeTo(std::ostream &str)
{
    write_json(str, root_);
}

struct JsonWriter::Private {
    std::ostream                   &str;
    std::queue<Defect>              defQueue;
    TScanProps                      scanProps;
    AbstractTreeEncoder            *encoder;

    Private(std::ostream &str_):
        str(str_)
    {
    }
};

JsonWriter::JsonWriter(std::ostream &str, const EFileFormat format):
    d(new Private(str))
{
    switch (format) {
        case FF_JSON:
            d->encoder = new SimpleTreeEncoder;
            break;

        default:
            throw std::runtime_error("unknown output format");
    }
}

JsonWriter::~JsonWriter()
{
    delete d->encoder;
    delete d;
}

const TScanProps& JsonWriter::getScanProps() const
{
    return d->scanProps;
}

void JsonWriter::setScanProps(const TScanProps &scanProps)
{
    d->scanProps = scanProps;
}

void JsonWriter::handleDef(const Defect &def)
{
    d->defQueue.push(def);
}

void JsonWriter::flush()
{
    boost::iostreams::filtering_ostream str;

    // create a regex-based filter to restore integral values wrapped as strings
    const RE reInt(": \"([0-9]+)\",$");
    boost::iostreams::basic_regex_filter<char> reFilter(reInt, ": \\1,");
    str.push(reFilter);

    // create a regex-based filter to replace \/ (produced by newer boost) by /
    const RE reSlash("([^\\\\]*(?:\\\\\\\\)*)(?:\\\\(/))?");
    boost::iostreams::basic_regex_filter<char> reFilterSlash(reSlash, "\\1\\2");
    str.push(reFilterSlash);

    // create a regex-based filter to replace \u0009 by \t
    const RE reTab("\\\\u0009");
    boost::iostreams::basic_regex_filter<char> reFilterTab(reTab, "\\\\t");
    str.push(reFilterTab);

    str.push(d->str);

    // transfer scan properties if available
    d->encoder->importScanProps(d->scanProps);

    // go through the queue and move defects one by one to the property tree
    for (; !d->defQueue.empty(); d->defQueue.pop())
        d->encoder->appendDef(d->defQueue.front());

    // finally encode the tree as JSON
    d->encoder->writeTo(str);
}
