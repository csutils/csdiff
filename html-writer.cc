/*
 * Copyright (C) 2012 Red Hat, Inc.
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

#include "html-writer.hh"

// TODO: drop this!
#include "cswriter.hh"

#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>
#include <boost/regex.hpp>

namespace HtmlLib {

    void escapeText(std::string &text) {
        using namespace boost::algorithm;

        replace_all(text,  "&", "&amp;" );
        replace_all(text, "\"", "&quot;");
        replace_all(text, "\'", "&apos;");
        replace_all(text,  "<", "&lt;"  );
        replace_all(text,  ">", "&gt;"  );
    }

    void initHtml(std::ostream &str, std::string title) {
        escapeText(title);

        str << "<?xml version='1.0' encoding='utf-8'?>\n\
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.1//EN' \
'http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd'>\n\
<html xmlns='http://www.w3.org/1999/xhtml'>\n\
<head><title>" << title << "</title></head>\n\
<body>\n<h1>" << title << "</h1>\n";
    }

    void finalizeHtml(std::ostream &str) {
        str << "</body>\n</html>\n";
    }

    void initSection(std::ostream &str, std::string name) {
        escapeText(name);
        str << "<h2>" << name << "</h2>\n";
    }

    void initPre(std::ostream &str) {
        str << "<pre style='white-space: pre-wrap;'>\n";
    }

    void finalizePre(std::ostream &str) {
        str << "</pre>\n";
    }

} // namespace HtmlLib

namespace CsLib {

#define RETURN_IF_FOUND(props, key) do {                \
    TScanProps::const_iterator it = props.find(key);    \
    if (props.end() != it)                              \
        return it->second;                              \
} while (0)

    std::string digTitle(const TScanProps &props) {
        RETURN_IF_FOUND(props, "title");
        RETURN_IF_FOUND(props, "project-name");

        TScanProps::const_iterator it = props.find("tool-args");
        if (props.end() != it) {
            const std::string &args = it->second;
            const boost::regex reSrpm("^.*[ /]([^ /]*)\\.src\\.rpm.*$");

            boost::smatch sm;
            if (!boost::regex_match(args, sm, reSrpm))
                goto fail;

            return sm[/* NVR */ 1];
        }

fail:
        return "Scan Results";
    }

    void writeScanProps(std::ostream &str, const TScanProps &props) {
        if (props.empty())
            return;

        str << "<table style='font-family: monospace;'>\n";
        int i = 0;

        BOOST_FOREACH(TScanProps::const_reference item, props) {
            const char *trStyle = "";
            if (++i & 1)
                trStyle = " style='background-color: #EEE;'";

            str << "<tr" << trStyle << "><td style='padding-right: 8px;'>"
                << item.first << "</td><td>" << item.second << "</td></tr>\n";
        }

        str << "</table>\n";
    }

} // namespace CsLib

class HtmlWriterCore {
    public:
        HtmlWriterCore(std::ostream &str):
            str_(str),
            headerWritten_(false),
            documentClosed_(false)
        {
        }

        ~HtmlWriterCore();

        bool headerWritten() const {
            return headerWritten_;
        }

        void writeHeaderOnce(const TScanProps &);
        void closeDocument();

    private:
        std::ostream       &str_;
        bool                headerWritten_;
        bool                documentClosed_;
};

HtmlWriterCore::~HtmlWriterCore() {
    assert(headerWritten_);
    assert(documentClosed_);
}

void HtmlWriterCore::writeHeaderOnce(const TScanProps &props) {
    assert(!documentClosed_);
    if (headerWritten_)
        // header already out
        return;

    // initialize a HTML document
    const std::string title = CsLib::digTitle(props);
    HtmlLib::initHtml(str_, title);

    // write scan propreties
    CsLib::writeScanProps(str_, props);

    // initialize the section for defects
    HtmlLib::initSection(str_, "List of Defects");
    HtmlLib::initPre(str_);

    headerWritten_ = true;
}

void HtmlWriterCore::closeDocument() {
    assert(headerWritten_);
    assert(!documentClosed_);

    // clsoe the HTML docuemnt
    HtmlLib::finalizePre(str_);
    HtmlLib::finalizeHtml(str_);

    documentClosed_ = true;
}

struct HtmlWriter::Private {
    std::ostream                   &str;
    HtmlWriterCore                  core;
    TScanProps                      scanProps;

    // TODO: drop this!
    CovWriter                       cWriter;

    Private(std::ostream &str_):
        str(str_),
        core(str_)
    {
    }
};

HtmlWriter::HtmlWriter(std::ostream &str):
    d(new Private(str))
{
}

HtmlWriter::~HtmlWriter() {
    delete d;
}

const TScanProps& HtmlWriter::getScanProps() const {
    return d->scanProps;
}

void HtmlWriter::setScanProps(const TScanProps &scanProps) {
    assert(!d->core.headerWritten());
    d->scanProps = scanProps;
}

void HtmlWriter::handleDef(const Defect &def) {
    d->core.writeHeaderOnce(d->scanProps);

    // FIXME: escape special characters!
    d->cWriter.handleDef(def);
}

void HtmlWriter::flush() {
    d->cWriter.flush();
    d->core.closeDocument();
}
