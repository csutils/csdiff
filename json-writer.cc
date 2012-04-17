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

#include <boost/foreach.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/property_tree/json_parser.hpp>

struct JsonWriter::Private {
    boost::property_tree::ptree defList;
};

JsonWriter::JsonWriter():
    d(new Private)
{
}

JsonWriter::~JsonWriter() {
    delete d;
}

void JsonWriter::handleDef(const Defect &def) {
    using std::string;

    // go through events
    boost::property_tree::ptree evtList;
    BOOST_FOREACH(const DefEvent &evt, def.events) {
        boost::property_tree::ptree evtNode;

        // describe the location
        evtNode.put<string>("file_name", evt.fileName);
        evtNode.put<int>("line", evt.line);
        if (0 < evt.column)
            evtNode.put<int>("column", evt.column);

        // describe the event
        evtNode.put<string>("event", evt.event);
        evtNode.put<string>("message", evt.msg);

        // append the event to the list
        evtList.push_back(std::make_pair("", evtNode));
    }

    // create a node for a single defect
    boost::property_tree::ptree defNode;
    defNode.put<string>("checker", def.defClass);
    defNode.put<int>("key_event_idx", def.keyEventIdx);
    defNode.put_child("events", evtList);

    // append the node to the list
    d->defList.push_back(std::make_pair("", defNode));
}

void JsonWriter::flush() {
    // create a regex-based filter to restore integral values wrapped as strings
    const boost::regex re(": \"([0-9])+\",$");
    boost::iostreams::basic_regex_filter<char> reFilter(re, ": \\1,");
    boost::iostreams::filtering_ostream str;
    str.push(reFilter);
    str.push(std::cout);

    // finally create the root node and stream out the defect list
    boost::property_tree::ptree root;
    root.put_child("defects", d->defList);
    write_json(str, root);
}
