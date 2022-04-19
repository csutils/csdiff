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

#include "abstract-tree.hh"
#include "regex.hh"
#include "shared-string-ptree.hh"
#include "version.hh"

#include <queue>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/regex.hpp>
#include <boost/property_tree/json_parser.hpp>

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
        evtNode.put<string>("message", evt.msg);
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
        SarifTreeEncoder();

        /// import supported scan properties
        void importScanProps(const TScanProps &) override;

        /// append single defect
        void appendDef(const Defect &) override;

        /// write everything to the given output stream
        void writeTo(std::ostream &) override;

    private:
        void serializeCweMap();

        typedef std::map<std::string, int>  TCweMap;
        TCweMap                     cweMap_;
        TScanProps                  scanProps_;
        PTree                       driver_;
        PTree                       results_;
};

SarifTreeEncoder::SarifTreeEncoder()
{
    // mandatory: tool/driver
    driver_.put<std::string>("name", "csdiff");
    driver_.put<std::string>("version", CS_VERSION);
    driver_.put<std::string>("informationUri",
            "https://github.com/csutils/csdiff");
}

void SarifTreeEncoder::serializeCweMap()
{
    PTree ruleList;

    for (const auto &item : cweMap_) {
        PTree rule;
        const auto &id = item.first;
        rule.put<std::string>("id", id);

        PTree cweList;
        const auto cwe = item.second;
        const auto cweStr = std::to_string(cwe);
        appendNode(&cweList, PTree("CWE-" + cweStr));

        // properties.cwe[]
        PTree props;
        props.put_child("cwe", cweList);
        rule.put_child("properties", props);

        // help.text
        PTree help;
        const auto helpText =
            "https://cwe.mitre.org/data/definitions/" + cweStr + ".html";
        help.put<std::string>("text", helpText);
        rule.put_child("help", help);

        appendNode(&ruleList, rule);
    }

    driver_.put_child("rules", ruleList);
}

void SarifTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    scanProps_ = scanProps;
}

static void sarifEncodeMsg(PTree *pDst, const std::string text)
{
    PTree msg;
    msg.put<std::string>("text", text);
    pDst->put_child("message", msg);
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
    if (def.cwe)
        // update CWE map
        cweMap_[ruleId] = def.cwe;

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

    if (!cweMap_.empty())
        // needs to run before we pick driver_
        this->serializeCweMap();

    PTree tool;
    tool.put_child("driver", driver_);

    PTree run0;
    run0.put_child("tool", tool);

    if (!results_.empty())
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

    str.push(d->str);

    // transfer scan properties if available
    d->encoder->importScanProps(d->scanProps);

    // go through the queue and move defects one by one to the property tree
    for (; !d->defQueue.empty(); d->defQueue.pop())
        d->encoder->appendDef(d->defQueue.front());

    // finally encode the tree as JSON
    d->encoder->writeTo(str);
}
