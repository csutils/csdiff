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

#include "writer-html.hh"

#include "cwe-name-lookup.hh"
#include "deflookup.hh"
#include "regex.hh"

#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

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

        str << R"(<!DOCTYPE html>
<html>
<head>
    <title>)" << title << R"(</title>
    <style>
        body { background-color: white; }
        pre { white-space: pre-wrap; }
        .checker { background:#C0FF00; }
        .ctxLine { color:#000000; }
        .infoEvent { color:#808080; }
        .infoEventComment { color:#00C0C0; }
        .traceEvent { color: #C0C0C0; }
        .newFinding { color: #00FF00; }
        .parseWarning { color: #FF0000; }
        .impFlag { color: #FF0000; font-weight: bold; }
        #scanProps { font-family: monospace; }
        .oddRow { background-color: #EEE; }
        .scanPropName { padding-right: 8px; white-space: nowrap; }
    </style>
</head>
<body>
<h1>)" << title << "</h1>\n";
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
        str << "<pre>\n";
    }

    void finalizePre(std::ostream &str) {
        str << "</pre>\n";
    }

} // namespace HtmlLib

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
        const RE reSrpm("^.*[ /']([^ /']*)\\.src\\.rpm.*$");

        boost::smatch sm;
        if (!boost::regex_match(args, sm, reSrpm))
            return "";

        title = sm[/* NVR */ 1];
    }
    else
        title = it->second;

    it = props.find("diffbase-project-name");
    if (NA != it) {
        title += " - findings not occurring in ";
        title += it->second;
    }

    return title;
}

void writeParseWarnings(std::ostream &str, const TScanProps &props) {
    TScanProps::const_iterator itCount, itRatio;
    itCount = props.find("cov-compilation-unit-count");
    itRatio = props.find("cov-compilation-unit-ratio");
    if (props.end() == itCount || props.end() == itRatio)
        return;

    try {
        const int count = boost::lexical_cast<int>(itCount->second);
        const int ratio = boost::lexical_cast<float>(itRatio->second);
        if (ratio < parsingRatioThr)
            str << "<p><b class='parseWarning'>warning:</b> "
                "low parsing ratio: " << ratio << "%</p>\n";

        itCount = props.find("diffbase-cov-compilation-unit-count");
        itRatio = props.find("diffbase-cov-compilation-unit-ratio");
        if (props.end() == itCount || props.end() == itRatio)
            return;

        const int baseCount = boost::lexical_cast<int>(itCount->second);
        const int baseRatio = boost::lexical_cast<float>(itRatio->second);
        if (baseRatio < parsingRatioThr && baseRatio < ratio)
            str << "<p><b class='parseWarning'>warning:</b> "
                "low parsing ratio in diff base: "
                << baseRatio << "%</p>\n";

        if (!count || 100 * baseCount / count < parsingOldToNewRatioThr)
            str << "<p><b class='parseWarning'>warning:</b> "
                "low count of parsed units in diff base: "
                << baseCount << "</p>\n";
    }
    catch (boost::bad_lexical_cast &) {
        // failed to parse count/ratio
    }
}

void writeScanProps(std::ostream &str, const TScanProps &props) {
    if (props.empty())
        return;

    HtmlLib::initSection(str, "Scan Properties");

    str << "<table id='scanProps'>\n";
    int i = 0;

    for (TScanProps::const_reference item : props) {
        const char *trClass = "";
        if (++i & 1)
            trClass = " class='oddRow'";

        str << "<tr" << trClass << "><td class='scanPropName'>"
            << item.first << "</td><td>" << item.second << "</td></tr>\n";
    }

    str << "</table>\n";
}

void linkifyShellCheckMsg(std::string *pMsg)
{
    static const RE reShellCheckMsg("(\\[)?SC([0-9]+)(\\])?$");
    *pMsg = boost::regex_replace(*pMsg, reShellCheckMsg,
            "<a href=\"https://github.com/koalaman/shellcheck/wiki/SC\\2\""
            " title=\"description of ShellCheck's checker SC\\2\">"
            "\\1SC\\2\\3</a>");
}

void printCweLink(std::ostream &str, const int cwe, const std::string &cweName)
{
    str << "<a href=\"https://cwe.mitre.org/data/definitions/"
        << cwe << ".html\" title=\"";
    if (cweName.empty())
        str << "definition of CWE-" << cwe << " by MITRE";
    else
        str << "CWE-" << cwe << ": " << cweName;

    str << "\">"
        << "CWE-" << cwe
        << "</a>";
}

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
    std::string title = digTitle(props);
    if (title.empty())
        title = titleFallback_;

    // initialize a HTML document
    HtmlLib::initHtml(str_, std::move(title));
    if (!plainTextUrl.empty())
        HtmlLib::writeLink(str_, plainTextUrl, "[Show plain-text results]");

    // write scan properties
    writeParseWarnings(str_, props);
    if (spOnTop_)
        writeScanProps(str_, props);

    // initialize the section for defects
    HtmlLib::initSection(str_, "List of Findings");
    HtmlLib::initPre(str_);

    headerWritten_ = true;
}

void HtmlWriterCore::closeDocument(const TScanProps &props)
{
    assert(headerWritten_);
    assert(!documentClosed_);

    // close the HTML document
    HtmlLib::finalizePre(str_);

    if (spBottom_)
        writeScanProps(str_, props);

    HtmlLib::finalizeHtml(str_);

    documentClosed_ = true;
}

struct HtmlWriter::Private {
    std::ostream                   &str;
    HtmlWriterCore                  core;
    TScanProps                      scanProps;
    const std::string               defUrlTemplate;
    unsigned                        defCnt = 0U;
    DefLookup                      *baseLookup = nullptr;
    RE                              checkerIgnRegex;
    std::string                     newDefMsg;
    std::string                     plainTextUrl;
    const CweNameLookup            *cweNames = nullptr;

    Private(
            std::ostream           &str_,
            const std::string      &titleFallback_,
            const std::string      &defUrlTemplate_,
            const std::string      &spPlacement_):
        str(str_),
        core(str_, titleFallback_, spPlacement_),
        defUrlTemplate(defUrlTemplate_)
    {
        if (!defUrlTemplate.empty())
            // just make sure that the format string is correct
            boost::format(defUrlTemplate) % 1 % 2;
    }

    void writeLinkToDetails(const Defect &);
    void writeNewDefWarning(const Defect &);

    const RE reEvent = RE("^([^\\[]*\\[)?([^\\]]+)(])?$");
};

HtmlWriter::HtmlWriter(
        std::ostream               &outputStream,
        const std::string          &titleFallback,
        const std::string          &defUrlTemplate,
        const std::string          &spPlacement):
    d(new Private(outputStream, titleFallback, defUrlTemplate, spPlacement))
{
}

HtmlWriter::~HtmlWriter()
{
    delete d;
}

const TScanProps& HtmlWriter::getScanProps() const
{
    return d->scanProps;
}

void HtmlWriter::setScanProps(const TScanProps &scanProps)
{
    assert(!d->core.headerWritten());
    d->scanProps = scanProps;
}

void HtmlWriter::setDiffBase(
        DefLookup                   *baseLookup,
        const std::string           &checkerIgnRegex,
        const TScanProps            &baseProps,
        const std::string           &baseTitleFallback)
{
    assert(baseLookup);
    d->baseLookup = baseLookup;
    d->checkerIgnRegex = checkerIgnRegex;

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
        d->newDefMsg = "newly introduced finding";
        return;
    }

    d->newDefMsg += "finding not occurring in <b>";
    d->newDefMsg += projName;
    d->newDefMsg += "</b>";
}

void HtmlWriter::setPlainTextUrl(const std::string &url)
{
    d->plainTextUrl = url;
}

void HtmlWriter::setCweNameLookup(const CweNameLookup *cweNames)
{
    d->cweNames = cweNames;
}

void HtmlWriter::Private::writeLinkToDetails(const Defect &def)
{
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

    try {
        const int projId = boost::lexical_cast<int>(it->second);

        // write the link
        this->str << " <a href ='"
            << boost::format(this->defUrlTemplate) % projId % defId
            << "'>[Show Details]</a>";
    }
    catch (boost::bad_lexical_cast &) {
        // failed to parse project ID
    }
}

void HtmlWriter::Private::writeNewDefWarning(const Defect &def)
{
    if (!this->baseLookup)
        // not lookup set
        return;

    if (boost::regex_match(def.checker, this->checkerIgnRegex))
        // user requested to ignore this checker for lookup
        return;

    if (this->baseLookup->lookup(def))
        // defect found in the lookup
        return;

    // a newly introduced defect
    this->str << " <span class='newFinding'>[<b>warning:</b> "
        << this->newDefMsg << "]</span>";
}

void HtmlWriter::handleDef(const Defect &def)
{
    d->core.writeHeaderOnce(d->scanProps, d->plainTextUrl);

    // HTML anchor
    d->str << "<a id='def" << ++(d->defCnt) << "'></a>";

    d->str << "<b>Error: <span class='checker'>"
        << HtmlLib::escapeTextInline(def.checker) << "</span>";

    const int cwe = def.cwe;
    if (cwe) {
        std::string cweName;
        if (d->cweNames)
            cweName = d->cweNames->lookup(cwe);
        d->str << " (";
        printCweLink(d->str, cwe, cweName);
        d->str << ")";
    }
    else
        d->str << HtmlLib::escapeTextInline(def.annotation);

    d->str << ":</b>";

    d->writeLinkToDetails(def);

    // link to self
    d->str << " <a href='#def"
        << d->defCnt << "'>[#def"
        << d->defCnt << "]</a>";

    if (0 < def.imp) {
        // highlight the "imp" flag
        d->str << " <span class='impFlag'>"
            "[important]</span>";
    }

    d->writeNewDefWarning(def);
    
    d->str << "\n";

    const unsigned cntEvents = def.events.size();
    for (unsigned idx = 0; idx < cntEvents; ++idx) {
        const DefEvent &evt = def.events[idx];
        const bool isComment = (evt.event == "#");

        switch (evt.verbosityLevel) {
            case 1:
                if (isComment)
                    d->str << "<span class='infoEventComment'>";
                else
                    d->str << "<span class='infoEvent'>";
                break;

            case 2:
                d->str << "<span class='traceEvent'>";
                break;
        }

        if (!evt.fileName.empty())
            d->str << HtmlLib::escapeTextInline(evt.fileName) << ":";
        
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
            if (boost::regex_match(evtName, sm, d->reEvent)) {
                std::string msgId = HtmlLib::escapeTextInline(sm[/* id */ 2]);
                if (def.checker == "SHELLCHECK_WARNING")
                    linkifyShellCheckMsg(&msgId);
                d->str
                    << HtmlLib::escapeTextInline(sm[1])
                    << "<b>" << msgId << "</b>"
                    << HtmlLib::escapeTextInline(sm[3]);
            }
            else
                d->str << "<b>" << HtmlLib::escapeTextInline(evtName) << "</b>";

            d->str << ": ";
        }

        static CtxEventDetector detector;
        const bool isCtxLine = detector.isAnyCtxLine(evt);
        if (isCtxLine) {
            const char *styleClass = (detector.isKeyCtxLine(evt))
                ? "ctxLine"
                : "traceEvent";
            d->str << "<span class='" << styleClass << "'>";
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

void HtmlWriter::flush()
{
    d->core.writeHeaderOnce(d->scanProps, d->plainTextUrl);
    d->core.closeDocument(d->scanProps);
}
