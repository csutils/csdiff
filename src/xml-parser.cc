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

#include "xml-parser.hh"

#include "abstract-tree.hh"

#include <boost/property_tree/xml_parser.hpp>

/// tree decoder for valgrind XML output
class ValgrindTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter);

        virtual void readRoot(
                const pt::ptree       **pDefList,
                const pt::ptree        *root);

    private:
        Defect defPrototype = Defect("VALGRIND_WARNING");
};

void ValgrindTreeDecoder::readRoot(
                const pt::ptree       **pDefList,
                const pt::ptree        *root)
{
    // TODO: read path to the binary and command-line args
    *pDefList = root;
}

bool ValgrindTreeDecoder::readNode(Defect *pDef, pt::ptree::const_iterator defIter)
{
    static const std::string errorKey = "error";
    if (errorKey != defIter->first)
        // not a node we are interested in
        return false;

    // initialize the defect structure
    Defect &def = *pDef;
    def = this->defPrototype;

    // initialize the key event
    def.keyEventIdx = def.events.size();
    def.events.push_back(DefEvent());
    DefEvent &keyEvent = def.events.back();
    keyEvent.event = "warning";

    // read "kind" of the report
    const pt::ptree &defNode = defIter->second;
    pt::ptree::const_assoc_iterator itKind = defNode.find("kind");
    if (defNode.not_found() != itKind)
        keyEvent.event += "[" + itKind->second.get_value<std::string>() + "]";

    // TODO
    return true;
}

struct XmlParser::Private {
    InStream                       &input;
    AbstractTreeDecoder            *decoder = nullptr;
    pt::ptree                       root;
    const pt::ptree                *defList = nullptr;
    pt::ptree::const_iterator       defIter = root.end();

    Private(InStream &input):
        input(input)
    {
    }

    ~Private()
    {
        delete this->decoder;
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
            d->decoder = new ValgrindTreeDecoder;
        else
            throw pt::ptree_error("unknown XML format");

        // process the root node
        d->decoder->readRoot(&d->defList, node);

        // initialize the traversal through the list of defects/issues
        d->defIter = d->defList->begin();
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

XmlParser::~XmlParser()
{
    delete d;
}

bool XmlParser::hasError() const
{
    return d->input.anyError();
}

bool XmlParser::getNext(Defect *pDef)
{
    if (!d->defList)
        // initialization failed, error has already been reported
        return false;

    while (d->defList->end() != d->defIter) {
        // get the current node and move to the next one
        try {
            if (d->decoder->readNode(pDef, d->defIter++))
                return true;
        }
        catch (pt::ptree_error &e) {
            d->input.handleError(e.what());
        }
    }

    // EOF
    return false;
}
