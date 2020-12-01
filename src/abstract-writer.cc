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

#include "abstract-writer.hh"

#include "cswriter.hh"
#include "html-writer.hh"
#include "instream.hh"
#include "json-writer.hh"
#include "regex.hh"

// /////////////////////////////////////////////////////////////////////////////
// implementation of AbstractWriter

bool AbstractWriter::handleFile(Parser &parser, const std::string &fileName)
{
        this->notifyFile(fileName);

        // detect the input format and create the parser
        if (inputFormat_ == FF_INVALID)
            inputFormat_ = parser.inputFormat();

        // read scan properties if still empty
        if (this->getScanProps().empty())
            this->setScanProps(parser.getScanProps());

        Defect def;
        while (parser.getNext(&def))
            this->handleDef(def);

        return !parser.hasError();
}

bool AbstractWriter::handleFile(
        std::istream               &str,
        const std::string          &fileName,
        const bool                  silent)
{
    Parser parser(str, fileName, silent);
    return this->handleFile(parser, fileName);
}

bool AbstractWriter::handleFile(const std::string &fileName, bool silent)
{
    try {
        InStream str(fileName);
        return this->handleFile(str.str(), fileName, silent);
    }
    catch (const InFileException &e) {
        std::cerr << e.fileName << ": failed to open input file\n";
        return false;
    }
}

void AbstractWriter::setScanProps(const TScanProps &scanProps)
{
    if (scanProps.empty())
        return;

    std::cerr << "warning: scan properties not supported by output format\n";
}

AbstractWriter* createWriter(
        std::ostream               &strDst,
        const EFileFormat           format,
        const EColorMode            cm,
        const TScanProps           &scanProps)
{
    AbstractWriter *writer = 0;

    switch (format) {
        case FF_GCC:
            // we have no writer for GCC format, fallback to Coverity
            // fall through!

        case FF_INVALID:
        case FF_COVERITY:
            writer = new CovWriter(strDst, cm);
            break;

        case FF_AUTO:
            // TODO

        case FF_JSON:
            writer = new JsonWriter(strDst);
            break;

        case FF_HTML: {
            const std::string emp;
            const std::string spPlacement = "bottom";
            writer = new HtmlWriter(strDst, emp, emp, spPlacement);
            break;
        }
    }

    if (!scanProps.empty())
        writer->setScanProps(scanProps);

    return writer;
}


// /////////////////////////////////////////////////////////////////////////////
// implementation of CtxEventDetector

struct CtxEventDetector::Private {
    const RE reAnyCtxLine = RE("^ *[0-9]+\\|(?:->)? .*$");
    const RE reKeyCtxLine = RE("^ *[0-9]+\\|-> .*$");
};

CtxEventDetector::CtxEventDetector():
    d(new Private)
{
}

CtxEventDetector::~CtxEventDetector()
{
    delete d;
}

bool CtxEventDetector::isAnyCtxLine(const DefEvent &evt) const
{
    return (evt.event == "#")
        && boost::regex_match(evt.msg, d->reAnyCtxLine);
}

bool CtxEventDetector::isKeyCtxLine(const DefEvent &evt) const
{
    return (evt.event == "#")
        && boost::regex_match(evt.msg, d->reKeyCtxLine);
}
