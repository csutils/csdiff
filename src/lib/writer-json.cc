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

#include "writer-json.hh"

#include "abstract-tree.hh"
#include "regex.hh"
#include "shared-string-ptree.hh"
#include "version.hh"

#include <queue>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/nowide/utf/convert.hpp>
#include <boost/property_tree/json_parser.hpp>

static inline std::string sanitizeUTF8(const std::string &str)
{
    using boost::nowide::utf::convert_string;

    // every non-UTF8 sequence will be replaced with 0xEF 0xBF 0xBD which
    // corresponds to REPLACEMENT CHARACTER U+FFFD
    return convert_string<char>(str.data(), str.data() + str.size());
}

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
        evtNode.put<string>("message", sanitizeUTF8(evt.msg));
        evtNode.put<int>("verbosity_level", evt.verbosityLevel);

        // append the event to the list
        appendNode(&evtList, evtNode);
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
    if (!def.tool.empty())
        defNode.put<string>("tool", def.tool);

    defNode.put<int>("key_event_idx", def.keyEventIdx);
    defNode.put_child("events", evtList);

    // create the node representing the list of defects
    if (!pDefects_)
        pDefects_ = &root_.put_child("defects", PTree());

    // append the node to the list
    appendNode(pDefects_, defNode);
}

void SimpleTreeEncoder::writeTo(std::ostream &str)
{
    if (!pDefects_)
        // create an empty "defects" node to keep format detection working
        pDefects_ = &root_.put_child("defects", PTree());

    write_json(str, root_);
}

// SARIF 2.1.0 is documented at:
// https://docs.github.com/en/code-security/code-scanning/integrating-with-code-scanning/sarif-support-for-code-scanning
// specification: https://docs.oasis-open.org/sarif/sarif/v2.1.0/os/sarif-v2.1.0-os.html
// validation: https://sarifweb.azurewebsites.net/Validation
class SarifTreeEncoder: public AbstractTreeEncoder {
    public:
        SarifTreeEncoder() = default;

        /// import supported scan properties
        void importScanProps(const TScanProps &) override;

        /// append single defect
        void appendDef(const Defect &) override;

        /// write everything to the given output stream
        void writeTo(std::ostream &) override;

    private:
        void initToolVersion();
        void serializeRules();

        using TCweMap = std::map<std::string, int>;
        TCweMap                     cweMap_;

        using TShellCheckMap = std::map<std::string, std::string>;
        TShellCheckMap              shellCheckMap_;

        TScanProps                  scanProps_;
        PTree                       driver_;
        PTree                       results_;
};

void SarifTreeEncoder::initToolVersion()
{
    std::string tool;
    auto it = scanProps_.find("tool");
    if (scanProps_.end() != it)
        // read "tool" scan property
        tool = it->second;

    std::string ver;
    it = scanProps_.find("tool-version");
    if (scanProps_.end() != it) {
        // read "tool-version" scan property
        ver = it->second;

        if (tool.empty()) {
            // try to split the "{tool}-{version}" string by the last '-'
            const size_t lastDashAt = ver.rfind('-');
            if (std::string::npos != lastDashAt) {
                // read tool from the "{tool}-{version}" string
                tool = ver.substr(0, lastDashAt);

                // remove "{tool}-" from "{tool}-{version}"
                ver.erase(0U, lastDashAt);
            }
        }
        else {
            // try to find "{tool}-" prefix in the "tool-version" scan property
            const std::string prefix = tool + "-";
            if (0U == ver.find(prefix))
                ver.erase(0U, prefix.size());
        }
    }

    std::string uri;
    if (tool.empty()) { 
        // unable to read tool name --> fallback to csdiff as the tool
        tool = "csdiff";
        ver = CS_VERSION;
        uri = "https://github.com/csutils/csdiff";
    }
    else if (scanProps_.end() != (it = scanProps_.find("tool-url")))
        // read "tool-url" scan property
        uri = it->second;

    driver_.put<std::string>("name", tool);

    if (!ver.empty())
        driver_.put<std::string>("version", ver);

    if (!uri.empty())
        driver_.put<std::string>("informationUri", uri);
}

static void sarifEncodeShellCheckRule(PTree *rule, const std::string &ruleID)
{
    // name
    rule->put<std::string>("name", ruleID);

    // properties.tags[]
    PTree tagList;
    appendNode(&tagList, PTree({"ShellCheck"}));

    PTree props;
    props.put_child("tags", tagList);
    rule->put_child("properties", props);

    // help.text && help.markdown
    PTree help;
    const auto helpURI =
        "https://github.com/koalaman/shellcheck/wiki/" + ruleID;
    help.put<std::string>("text", "Defect reference: " + helpURI);

    const auto helpMarkdown =
        "Defect reference: [" + ruleID +"](" + helpURI + ")";
    help.put<std::string>("markdown", helpMarkdown);

    rule->put_child("help", help);
}

static void sarifEncodeCweRule(PTree *rule, const int cwe, bool append = false)
{
    PTree cweList;
    const auto cweStr = std::to_string(cwe);
    appendNode(&cweList, PTree("CWE-" + cweStr));

    // properties.cwe[]
    if (append) {
        PTree &props = rule->get_child("properties");
        props.put_child("cwe", cweList);
    } else {
        PTree props;
        props.put_child("cwe", cweList);
        rule->put_child("properties", props);
    }

    // help.text
    const auto helpText =
        "https://cwe.mitre.org/data/definitions/" + cweStr + ".html";

    if (append) {
        PTree &help = rule->get_child("help");
        const auto &originalHelpText = help.get_child("text").get_value("");
        help.put<std::string>("text", originalHelpText + '\n' + helpText);
    } else {
        PTree help;
        help.put<std::string>("text", helpText);
        rule->put_child("help", help);
    }
}

void SarifTreeEncoder::serializeRules()
{
    PTree ruleList;

    for (const auto &item : shellCheckMap_) {
        PTree rule;
        const auto &id = item.first;
        rule.put<std::string>("id", id);

        sarifEncodeShellCheckRule(&rule, item.second);
        if (1U == cweMap_.count(id))
            sarifEncodeCweRule(&rule, cweMap_[id], /*append =*/ true);

        appendNode(&ruleList, rule);
    }

    for (const auto &item : cweMap_) {
        const auto &id = item.first;
        if (1U == shellCheckMap_.count(id))
            continue;

        PTree rule;
        rule.put<std::string>("id", id);
        sarifEncodeCweRule(&rule, item.second);

        appendNode(&ruleList, rule);
    }

    driver_.put_child("rules", ruleList);
}

void SarifTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    scanProps_ = scanProps;
}

static void sarifEncodeMsg(PTree *pDst, const std::string& text)
{
    PTree msg;
    msg.put<std::string>("text", sanitizeUTF8(text));
    pDst->put_child("message", msg);
}

static void sarifEncodeLevel(PTree *result, const std::string &event)
{
    std::string level = event;

    // cut the [...] suffix from event if present
    size_t pos = event.find('[');
    if (std::string::npos != pos)
        level = event.substr(0U, pos);

    // go through events that denote warning level
    for (const char *str : {"error", "warning", "note"}) {
        if (str == level) {
            // encode in the output if matched
            result->put<std::string>("level", level);
            return;
        }
    }
}

static void sarifEncodeLoc(PTree *pLoc, const Defect &def, unsigned idx)
{
    // location ID within the result
    pLoc->put<unsigned>("id", idx);

    const DefEvent &evt = def.events[idx];

    // file name
    PTree locArt;
    locArt.put<std::string>("uri", evt.fileName);
    PTree locPhy;
    locPhy.put_child("artifactLocation", locArt);

    // line/col
    if (evt.line) {
        PTree reg;
        reg.put<int>("startLine", evt.line);
        if (evt.column)
            reg.put<int>("startColumn", evt.column);

        locPhy.put_child("region", reg);
    }

    // location
    pLoc->put_child("physicalLocation", locPhy);
}

static void sarifEncodeComment(PTree *pDst, const Defect &def, unsigned idx)
{
    PTree comment;

    // needed for Github to see the SARIF data as valid
    sarifEncodeLoc(&comment, def, idx);

    sarifEncodeMsg(&comment, def.events[idx].msg);
    appendNode(pDst, comment);
}

static void sarifEncodeEvt(PTree *pDst, const Defect &def, unsigned idx)
{
    const DefEvent &evt = def.events[idx];

    // location + message
    PTree loc;
    sarifEncodeLoc(&loc, def, idx);
    sarifEncodeMsg(&loc, evt.msg);

    // threadFlowLocation
    PTree tfLoc;
    tfLoc.put_child("location", loc);

    // verbosityLevel
    tfLoc.put<int>("nestingLevel", evt.verbosityLevel);

    // event
    PTree kind;
    kind.put<std::string>("", evt.event);
    PTree kindList;
    appendNode(&kindList, kind);
    tfLoc.put_child("kinds", kindList);

    // append the threadFlowLocation object to the destination array
    appendNode(pDst, tfLoc);
}

void SarifTreeEncoder::appendDef(const Defect &def)
{
    const DefEvent &keyEvt = def.events[def.keyEventIdx];
    PTree result;

    // checker (FIXME: suboptimal mapping to SARIF)
    const std::string ruleId = def.checker + ": " + keyEvt.event;
    result.put<std::string>("ruleId", ruleId);

    if (def.checker == "SHELLCHECK_WARNING") {
        boost::smatch sm;
        static const RE reShellCheckMsg("(\\[)?(SC[0-9]+)(\\])?$");
        boost::regex_search(keyEvt.event, sm, reShellCheckMsg);

        // update ShellCheck rule map
        shellCheckMap_[ruleId] = sm[2];
    }

    if (def.cwe)
        // update CWE map
        cweMap_[ruleId] = def.cwe;

    // key event severity level
    sarifEncodeLevel(&result, keyEvt.event);

    // key event location
    PTree loc;
    sarifEncodeLoc(&loc, def, def.keyEventIdx);
    PTree keyLocs;
    appendNode(&keyLocs, loc);
    result.put_child("locations", keyLocs);

    // key msg
    sarifEncodeMsg(&result, keyEvt.msg);

    // other events
    PTree flowLocs, relatedLocs;
    for (unsigned i = 0; i < def.events.size(); ++i) {
        if (def.events[i].event == "#")
            sarifEncodeComment(&relatedLocs, def, i);
        else
            sarifEncodeEvt(&flowLocs, def, i);
    }

    // locations
    PTree tf;
    tf.put_child("locations", flowLocs);

    // threadFlows
    PTree tfList;
    appendNode(&tfList, tf);
    PTree cf;
    cf.put_child("threadFlows", tfList);

    // codeFlows
    PTree cfList;
    appendNode(&cfList, cf);
    result.put_child("codeFlows", cfList);

    if (!relatedLocs.empty())
        // our stash for comments
        result.put_child("relatedLocations", relatedLocs);

    // append the `result` object to the `results` array
    appendNode(&results_, result);
}

void SarifTreeEncoder::writeTo(std::ostream &str)
{
    PTree root;

    // mandatory: schema/version
    root.put<std::string>("$schema",
            "https://json.schemastore.org/sarif-2.1.0.json");
    root.put<std::string>("version", "2.1.0");

    if (!scanProps_.empty()) {
        // scan props
        PTree props;
        for (TScanProps::const_reference prop : scanProps_)
            props.put<std::string>(prop.first, prop.second);

        PTree extProps;
        extProps.put_child("externalizedProperties", props);
        PTree propsList;
        appendNode(&propsList, extProps);
        root.put_child("inlineExternalProperties", propsList);
    }

    this->initToolVersion();

    if (!cweMap_.empty() || !shellCheckMap_.empty())
        // needs to run before we pick driver_
        this->serializeRules();

    PTree tool;
    tool.put_child("driver", driver_);

    PTree run0;
    run0.put_child("tool", tool);

    // results
    run0.put_child("results", results_);

    // mandatory: runs
    PTree runs;
    appendNode(&runs, run0);
    root.put_child("runs", runs);

    // encode as JSON
    write_json(str, root);
}

struct JsonWriter::Private {
    std::ostream                           &str;
    std::queue<Defect>                      defQueue;
    TScanProps                              scanProps;
    std::unique_ptr<AbstractTreeEncoder>    encoder;

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
            d->encoder.reset(new SimpleTreeEncoder);
            break;

        case FF_SARIF:
            d->encoder.reset(new SarifTreeEncoder);
            break;

        default:
            throw std::runtime_error("unknown output format");
    }
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
    const RE reInt(": \"([0-9]+)\"(,?)$");
    boost::iostreams::basic_regex_filter<char> reFilter(reInt, ": \\1\\2");
    str.push(reFilter);

    // create a regex-based filter to replace \/ (produced by newer boost) by /
    const RE reSlash("([^\\\\]*(?:\\\\\\\\)*)(?:\\\\(/))?");
    boost::iostreams::basic_regex_filter<char> reFilterSlash(reSlash, "\\1\\2");
    str.push(reFilterSlash);

    // create a regex-based filter to replace \u0009 by \t
    const RE reTab("\\\\u0009");
    boost::iostreams::basic_regex_filter<char> reFilterTab(reTab, "\\\\t");
    str.push(reFilterTab);

    // regex-based filter to replace "results": "" by "results": [] in SARIF
    const RE reEmptyResults("(\"results\": )\"\"$");
    boost::iostreams::basic_regex_filter<char>
        reFilterEmp(reEmptyResults, "\\1[]");
    str.push(reFilterEmp);

    str.push(d->str);

    // transfer scan properties if available
    d->encoder->importScanProps(d->scanProps);

    // go through the queue and move defects one by one to the property tree
    for (; !d->defQueue.empty(); d->defQueue.pop())
        d->encoder->appendDef(d->defQueue.front());

    // finally encode the tree as JSON
    d->encoder->writeTo(str);
}
