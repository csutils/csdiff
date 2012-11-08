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

#include "deflookup.hh"

#include <boost/algorithm/string/replace.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

static int parsingRatioThr = 95;
static int parsingOldToNewRatioThr = 75;

namespace HtmlLib {

    void escapeText(std::string &text) {
        using namespace boost::algorithm;

        replace_all(text,  "&", "&amp;" );
        replace_all(text, "\"", "&quot;");
        replace_all(text, "\'", "&apos;");
        replace_all(text,  "<", "&lt;"  );
        replace_all(text,  ">", "&gt;"  );
    }

    std::string escapeTextInline(std::string text) {
        escapeText(text);
        return text;
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
        if (props.end() == it)
            return "";

        const std::string &args = it->second;
        const boost::regex reSrpm("^.*[ /]([^ /]*)\\.src\\.rpm.*$");

        boost::smatch sm;
        if (!boost::regex_match(args, sm, reSrpm))
            return "";

        return sm[/* NVR */ 1];
    }

    void writeParseWarnings(std::ostream &str, const TScanProps &props) {
        typedef TScanProps::const_iterator TIter;
        TIter itCount = props.find("compilation-unit-count");
        TIter itRatio = props.find("compilation-unit-ratio");
        if (props.end() == itCount || props.end() == itRatio)
            return;

        const int count = boost::lexical_cast<int>(itCount->second);
        const int ratio = boost::lexical_cast<int>(itRatio->second);
        if (ratio < parsingRatioThr)
            str << "<p><b style='color: #FF0000;'>warning:</b> "
                "low parsing ratio: " << ratio << "%</p>\n";

        itCount = props.find("diffbase-compilation-unit-count");
        itRatio = props.find("diffbase-compilation-unit-ratio");
        if (props.end() == itCount || props.end() == itRatio)
            return;

        const int baseCount = boost::lexical_cast<int>(itCount->second);
        const int baseRatio = boost::lexical_cast<int>(itRatio->second);
        if (baseRatio < parsingRatioThr && baseRatio < ratio)
            str << "<p><b style='color: #FF0000;'>warning:</b> "
                "low parsing ratio in diff base: "
                << baseRatio << "%</p>\n";

        if (!count || 100 * baseCount / count < parsingOldToNewRatioThr)
            str << "<p><b style='color: #FF0000;'>warning:</b> "
                "low count of parsed units in diff base: "
                << baseCount << "</p>\n";
    }

    void writeScanProps(std::ostream &str, const TScanProps &props) {
        if (props.empty())
            return;

        HtmlLib::initSection(str, "Scan Properties");

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
        HtmlWriterCore(
                std::ostream       &str,
                const std::string  &titleFallback,
                const std::string  &spPlacement);

        bool headerWritten() const {
            return headerWritten_;
        }

        void writeHeaderOnce(const TScanProps &);
        void closeDocument(const TScanProps &props);

    private:
        std::ostream       &str_;
        std::string         titleFallback_;
        bool                spOnTop_;
        bool                spBottom_;
        bool                headerWritten_;
        bool                documentClosed_;
};

HtmlWriterCore::HtmlWriterCore(
        std::ostream               &str,
        const std::string          &titleFb,
        const std::string          &spPlacement):
    str_(str),
    titleFallback_(titleFb),
    spOnTop_(!spPlacement.compare("top")),
    spBottom_(!spPlacement.compare("bottom")),
    headerWritten_(false),
    documentClosed_(false)
{
    if (titleFallback_.empty())
        titleFallback_ = "Scan Results";

    if (!spOnTop_ && !spBottom_ && !!spPlacement.compare("none"))
        std::cerr << "warning: unknown placement of scan properties table: "
            << spPlacement << "\n";
}

void HtmlWriterCore::writeHeaderOnce(const TScanProps &props) {
    assert(!documentClosed_);
    if (headerWritten_)
        // header already out
        return;

    // resolve title of the document
    std::string title = CsLib::digTitle(props);
    if (title.empty())
        title = titleFallback_;

    // initialize a HTML document
    HtmlLib::initHtml(str_, title);

    // write scan properties
    CsLib::writeParseWarnings(str_, props);
    if (spOnTop_)
        CsLib::writeScanProps(str_, props);

    // initialize the section for defects
    HtmlLib::initSection(str_, "List of Defects");
    HtmlLib::initPre(str_);

    headerWritten_ = true;
}

void HtmlWriterCore::closeDocument(const TScanProps &props) {
    assert(headerWritten_);
    assert(!documentClosed_);

    // close the HTML document
    HtmlLib::finalizePre(str_);

    if (spBottom_)
        CsLib::writeScanProps(str_, props);

    HtmlLib::finalizeHtml(str_);

    documentClosed_ = true;
}

struct HtmlWriter::Private {
    std::ostream                   &str;
    HtmlWriterCore                  core;
    TScanProps                      scanProps;
    const std::string               defUrlTemplate;
    const boost::regex              rePath;
    unsigned                        defCnt;
    DefLookup                      *baseLookup;
    std::string                     newDefMsg;

    Private(
            std::ostream           &str_,
            const std::string      &titleFallback_,
            const std::string      &defUrlTemplate_,
            const std::string      &spPlacement_):
        str(str_),
        core(str_, titleFallback_, spPlacement_),
        defUrlTemplate(defUrlTemplate_),
        rePath("^/builddir/build/BUILD/"),
        defCnt(0),
        baseLookup(0)
    {
        if (!defUrlTemplate.empty())
            // just make sure that the format string is correct
            boost::format(defUrlTemplate) % 1 % 2;
    }

    void writeLinkToDetails(const Defect &);
    void writeNewDefWarning(const Defect &);
};

HtmlWriter::HtmlWriter(
        std::ostream               &outputStream,
        const std::string          &titleFallback,
        const std::string          &defUrlTemplate,
        const std::string          &spPlacement):
    d(new Private(outputStream, titleFallback, defUrlTemplate, spPlacement))
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

void HtmlWriter::setDiffBase(
        DefLookup                   *baseLookup,
        const TScanProps            &baseProps,
        const std::string           &baseTitleFallback)
{
    assert(baseLookup);
    d->baseLookup = baseLookup;

    // TODO: merge with already existing metadata stomping on the same keys
    TScanProps::const_iterator it = baseProps.find("compilation-unit-count");
    if (baseProps.end() != it)
        d->scanProps["diffbase-compilation-unit-count"] = it->second;
    it = baseProps.find("compilation-unit-ratio");
    if (baseProps.end() != it)
        d->scanProps["diffbase-compilation-unit-ratio"] = it->second;

    it = baseProps.find("project-name");
    const std::string projName = (baseProps.end() == it)
        ? baseTitleFallback
        : it->second;

    if (projName.empty()) {
        d->newDefMsg = "newly introduced defect";
        return;
    }

    d->newDefMsg += "defect not occurring in <b>";
    d->newDefMsg += projName;
    d->newDefMsg += "</b>";
}

void HtmlWriter::Private::writeLinkToDetails(const Defect &def) {
    const int defId = def.defectId;
    if (!defId)
        // no defect ID
        return;

    if (this->defUrlTemplate.empty())
        // no defect URL template
        return;

    const TScanProps::const_iterator it = this->scanProps.find("project-id");
    if (this->scanProps.end() == it)
        // no project ID
        return;

    const int projId = boost::lexical_cast<int>(it->second);

    // write the link
    this->str << " <a href ='"
        << boost::format(this->defUrlTemplate) % projId % defId
        << "'>[Show Details]</a>";
}

void HtmlWriter::Private::writeNewDefWarning(const Defect &def) {
    if (!this->baseLookup || this->baseLookup->lookup(def))
        return;

    // a newly introduced defect
    this->str << " <span style='color: #00FF00;'>[<b>warning:</b> "
        << this->newDefMsg << "]</span>";
}

void HtmlWriter::handleDef(const Defect &def) {
    d->core.writeHeaderOnce(d->scanProps);

    // HTML anchor
    d->str << "<a name='def" << ++(d->defCnt) << "'/>";

    d->str << "<b>Error: <span style='background: #C0FF00;'>"
        << HtmlLib::escapeTextInline(def.checker) << "</span>"
        << HtmlLib::escapeTextInline(def.annotation)
        << ":</b>";

    d->writeLinkToDetails(def);

    // link to self
    d->str << " <a href ='#def"
        << d->defCnt << "'>[#def"
        << d->defCnt << "]</a>";

    d->writeNewDefWarning(def);
    
    d->str << "\n";

    const unsigned cntEvents = def.events.size();
    for (unsigned idx = 0; idx < cntEvents; ++idx) {
        const DefEvent &evt = def.events[idx];

        const bool isKeyEvent = (def.keyEventIdx == idx);
        if (!isKeyEvent)
            d->str << "<span style='color: #808080;'>";

        d->str << boost::regex_replace(evt.fileName, d->rePath, "") << ":";
        
        if (0 < evt.line)
            d->str << evt.line << ":";

        if (0 < evt.column)
            d->str << evt.column << ":";

        d->str << " ";

        if (!evt.event.empty())
            d->str << "<b>" << HtmlLib::escapeTextInline(evt.event) << "</b>: ";

        d->str << HtmlLib::escapeTextInline(evt.msg);

        if (!isKeyEvent)
            d->str << "</span>";

        d->str << "\n";
    }

    d->str << "\n";
}

void HtmlWriter::flush() {
    d->core.writeHeaderOnce(d->scanProps);
    d->core.closeDocument(d->scanProps);
}
