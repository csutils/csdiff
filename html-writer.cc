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
<body style='background: white;'>\n<h1>" << title << "</h1>\n";
    }

    void writeLink(
            std::ostream           &str,
            const std::string      &url,
            const std::string      &name)
    {
        str << "<a href='" << url << "'>" << name << "</a>\n";
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
    std::string digTitle(const TScanProps &props) {
        const TScanProps::const_iterator NA = props.end();
        TScanProps::const_iterator it = props.find("title");
        if (NA != it)
            return it->second;

        std::string title;
        it = props.find("project-name");
        if (NA == it) {
            it = props.find("tool-args");
            if (props.end() == it)
                return "";

            const std::string &args = it->second;
            const boost::regex reSrpm("^.*[ /']([^ /']*)\\.src\\.rpm.*$");

            boost::smatch sm;
            if (!boost::regex_match(args, sm, reSrpm))
                return "";

            title = sm[/* NVR */ 1];
        }
        else
            title = it->second;

        it = props.find("diffbase-project-name");
        if (NA != it) {
            title += " - defects not occurring in ";
            title += it->second;
        }

        return title;
    }

    void writeParseWarnings(std::ostream &str, const TScanProps &props) {
        TScanProps::const_iterator itCount, itRatio;
        itCount = props.find("cov-compilation-unit-count");
        itRatio = props.find("cov-compilation-unit-ratio");
        if (props.end() == itCount || props.end() == itRatio) {
            // fallback to deprecated format produced by cov-mockbuild
            itCount = props.find("compilation-unit-count");
            itRatio = props.find("compilation-unit-ratio");
        }
        if (props.end() == itCount || props.end() == itRatio)
            return;

        const int count = boost::lexical_cast<int>(itCount->second);
        const int ratio = boost::lexical_cast<int>(itRatio->second);
        if (ratio < parsingRatioThr)
            str << "<p><b style='color: #FF0000;'>warning:</b> "
                "low parsing ratio: " << ratio << "%</p>\n";

        itCount = props.find("diffbase-cov-compilation-unit-count");
        itRatio = props.find("diffbase-cov-compilation-unit-ratio");
        if (props.end() == itCount || props.end() == itRatio) {
            // fallback to deprecated format produced by cov-mockbuild
            itCount = props.find("diffbase-compilation-unit-count");
            itRatio = props.find("diffbase-compilation-unit-ratio");
        }
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

        // FIXME: the API needs to be improved
        void writeHeaderOnce(
                const TScanProps   &props,
                const std::string  &plainTextUrl);

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

void HtmlWriterCore::writeHeaderOnce(
        const TScanProps           &props,
        const std::string          &plainTextUrl)
{
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
    if (!plainTextUrl.empty())
        HtmlLib::writeLink(str_, plainTextUrl, "[Show plain-text results]");

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
    const boost::regex              reEvent;
    unsigned                        defCnt;
    DefLookup                      *baseLookup;
    std::string                     newDefMsg;
    std::string                     plainTextUrl;

    Private(
            std::ostream           &str_,
            const std::string      &titleFallback_,
            const std::string      &defUrlTemplate_,
            const std::string      &spPlacement_):
        str(str_),
        core(str_, titleFallback_, spPlacement_),
        defUrlTemplate(defUrlTemplate_),
        rePath("^/builddir/build/BUILD/"),
        reEvent("^([^\\[]*\\[)?([^\\]]+)(])?$"),
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
    TScanProps::const_iterator it = baseProps.find("cov-compilation-unit-count");
    if (baseProps.end() != it)
        d->scanProps["diffbase-cov-compilation-unit-count"] = it->second;
    it = baseProps.find("cov-compilation-unit-ratio");
    if (baseProps.end() != it)
        d->scanProps["diffbase-cov-compilation-unit-ratio"] = it->second;

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

void HtmlWriter::setPlainTextUrl(const std::string &url) {
    d->plainTextUrl = url;
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

void linkifyShellCheckMsg(std::string *pMgs) {
    static boost::regex reShellCheckMsg(" \\[SC([0-9]+)\\]$");
    *pMgs = boost::regex_replace(*pMgs, reShellCheckMsg,
            " <a href=\"https://github.com/koalaman/shellcheck/wiki/SC\\1\""
            " title=\"description of ShellCheck's checker SC\\1\">"
            "[SC\\1]</a>");
}

void HtmlWriter::handleDef(const Defect &def) {
    d->core.writeHeaderOnce(d->scanProps, d->plainTextUrl);

    // HTML anchor
    d->str << "<a name='def" << ++(d->defCnt) << "'/>";

    d->str << "<b>Error: <span style='background: #C0FF00;'>"
        << HtmlLib::escapeTextInline(def.checker) << "</span>";
    if (def.cwe)
        d->str << " (CWE-" << def.cwe << ")";
    else
        d->str << HtmlLib::escapeTextInline(def.annotation);
    d->str << ":</b>";

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
        const bool isComment = (evt.event == "#");

        switch (evt.verbosityLevel) {
            case 1:
                if (isComment)
                    d->str << "<span style='color: #00C0C0;'>";
                else
                    d->str << "<span style='color: #808080;'>";
                break;

            case 2:
                d->str << "<span style='color: #C0C0C0;'>";
                break;
        }

        if (!evt.fileName.empty())
            d->str << boost::regex_replace(evt.fileName, d->rePath, "") << ":";
        
        if (0 < evt.line)
            d->str << evt.line << ":";

        if (0 < evt.column)
            d->str << evt.column << ":";

        if (isComment) {
            d->str << "#";
        }
        else {
            d->str << " ";

            boost::smatch sm;
            const std::string &evtName = evt.event;
            if (boost::regex_match(evtName, sm, d->reEvent))
                d->str
                    << HtmlLib::escapeTextInline(sm[1]) << "<b>"
                    << HtmlLib::escapeTextInline(sm[2]) << "</b>"
                    << HtmlLib::escapeTextInline(sm[3]);
            else
                d->str << "<b>" << HtmlLib::escapeTextInline(evtName) << "</b>";

            d->str << ": ";
        }

        static CtxEventDetector detector;
        const bool isCtxLine = detector.isAnyCtxLine(evt);
        if (isCtxLine) {
            const char *color = (detector.isKeyCtxLine(evt))
                ? "000000"
                : "C0C0C0";
            d->str << "<span style='color: #" << color << ";'>";
        }

        // translate message text
        std::string msgText = HtmlLib::escapeTextInline(evt.msg);
        if (def.checker == "SHELLCHECK_WARNING")
            linkifyShellCheckMsg(&msgText);
        d->str << msgText;

        if (isCtxLine)
            d->str << "</span>";

        switch (evt.verbosityLevel) {
            case 1:
            case 2:
                d->str << "</span>";
        }

        d->str << "\n";
    }

    d->str << "\n";
}

void HtmlWriter::flush() {
    d->core.writeHeaderOnce(d->scanProps, d->plainTextUrl);
    d->core.closeDocument(d->scanProps);
}
