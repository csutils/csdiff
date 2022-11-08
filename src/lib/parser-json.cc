/*
 * Copyright (C) 2011-2022 Red Hat, Inc.
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

#include "parser-json.hh"

#include "parser-json-cov.hh"
#include "parser-json-gcc.hh"
#include "parser-json-sarif.hh"
#include "parser-json-shchk.hh"
#include "parser-json-simple.hh"

#include <boost/property_tree/json_parser.hpp>

struct JsonParser::Private {
    using TDecoderPtr = std::unique_ptr<AbstractTreeDecoder>;

    InStream                       &input;
    TDecoderPtr                     decoder;
    pt::ptree                       root;
    int                             defNumber = 0;
    TScanProps                      scanProps;

    Private(InStream &input):
        input(input)
    {
    }

    void dataError(const std::string &msg);
};

void JsonParser::Private::dataError(const std::string &msg)
{
    this->input.handleError();
    if (this->input.silent())
        return;

    std::cerr
        << this->input.fileName() << ": error: failed to read defect #"
        << this->defNumber << ": " << msg << "\n";
}

JsonParser::JsonParser(InStream &input):
    d(new Private(input))
{
    try {
        // parse JSON
        read_json(input.str(), d->root);

        pt::ptree::const_iterator itFirst = d->root.begin();
        if (itFirst == d->root.end())
            // empty JSON, such as []
            return;

        const pt::ptree &first = itFirst->second;

        // recognize inner format of the JSON document
        pt::ptree *node = &d->root;
        if (findChildOf(&node, d->root, "defects"))
            // csdiff-native JSON format
            d->decoder.reset(new SimpleTreeDecoder(d->input));
        else if (findChildOf(&node, d->root, "issues"))
            // Coverity JSON format
            d->decoder.reset(new CovTreeDecoder);
        else if (findChildOf(&node, d->root, "runs"))
            // SARIF format
            d->decoder.reset(new SarifTreeDecoder);
        else if (findChildOf(&node, d->root, "comments"))
            // ShellCheck JSON format
            d->decoder.reset(new ShellCheckTreeDecoder);
        else if (first.not_found() != first.find("kind"))
            // GCC JSON format
            d->decoder.reset(new GccTreeDecoder);
        else
            throw pt::ptree_error("unknown JSON format");

        // read scan properties if available
        d->decoder->readScanProps(&d->scanProps, &d->root);

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

JsonParser::~JsonParser() = default;

bool JsonParser::hasError() const
{
    return d->input.anyError();
}

const TScanProps& JsonParser::getScanProps() const
{
    return d->scanProps;
}

bool JsonParser::getNext(Defect *def)
{
    // error recovery loop
    for (;;) {
        try {
            // make sure the Defect structure is properly initialized
            (*def) = Defect();

            // read the current node and move to the next one
            const bool ok = d->decoder->readNode(def);
            if (ok)
                d->defNumber++;

            return ok;
        }
        catch (pt::ptree_error &e) {
            d->dataError(e.what());
        }
    }
}
