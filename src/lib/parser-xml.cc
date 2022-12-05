/*
 * Copyright (C) 2011-2021 Red Hat, Inc.
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

#include "parser-xml.hh"

#include "parser-xml-valgrind.hh"

#include <boost/property_tree/xml_parser.hpp>

struct XmlParser::Private {
    using TDecoderPtr = std::unique_ptr<AbstractTreeDecoder>;

    InStream                       &input;
    TDecoderPtr                     decoder;
    pt::ptree                       root;

    Private(InStream &input):
        input(input)
    {
    }
};

XmlParser::XmlParser(InStream &input):
    d(new Private(input))
{
    try {
        // parse XML
        read_xml(d->input.str(), d->root);

        // recognize inner format of the XML document
        pt::ptree *node = nullptr;
        if (findChildOf(&node, d->root, "valgrindoutput"))
            // valgrind XML format
            d->decoder.reset(new ValgrindTreeDecoder);
        else
            throw pt::ptree_error("unknown XML format");

        // process the root node
        d->decoder->readRoot(node);
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

XmlParser::~XmlParser() = default;

bool XmlParser::hasError() const
{
    return d->input.anyError();
}

bool XmlParser::getNext(Defect *pDef)
{
    if (!d->decoder)
        // no decoder --> no data to read
        return false;

    // error recovery loop
    for (;;) {
        try {
            return d->decoder->readNode(pDef);
        }
        catch (pt::ptree_error &e) {
            d->input.handleError(e.what());
        }
    }
}
