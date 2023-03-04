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
#include "version.hh"
#include "writer-json-common.hh"

#include <algorithm>
#include <queue>

#include <boost/json/src.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::json;

static void prettyPrint(std::ostream&, const value&, std::string* = nullptr);

static inline void prettyPrintArray(
        std::ostream           &os,
        const array            &arr,
        std::string            *indent = nullptr)
{
        os << '[';
        if (arr.empty()) {
            os << ']';
            return;
        }

        indent->append(4, ' ');

        std::string sep{'\n'};
        for (const auto &elem : arr) {
            os << sep << *indent;
            prettyPrint(os, elem, indent);
            sep = ",\n";
        }
        os << '\n';

        indent->resize(indent->size() - 4);
        os << *indent << ']';

}

static inline void prettyPrintObject(
        std::ostream           &os,
        const object           &obj,
        std::string            *indent = nullptr)
{
        os << '{';
        if (obj.empty()) {
            os << '}';
            return;
        }

        indent->append(4, ' ');

        std::string sep{'\n'};
        for (const auto &elem : obj) {
            os << sep << *indent << serialize(elem.key()) << ": ";
            prettyPrint(os, elem.value(), indent);
            sep = ",\n";
        }
        os << '\n';

        indent->resize(indent->size() - 4);
        os << *indent << '}';
}

static void prettyPrint(
        std::ostream           &os,
        const value            &jv,
        std::string            *indent)
{
    std::string indent_;
    if (!indent)
        indent = &indent_;

    switch (jv.kind()) {
    case kind::array:
        prettyPrintArray(os, jv.get_array(), indent);
        break;

    case kind::object:
        prettyPrintObject(os, jv.get_object(), indent);
        break;

    case kind::string:
        os << serialize(jv.get_string());
        break;

    case kind::uint64:
        os << jv.get_uint64();
        break;

    case kind::int64:
        os << jv.get_int64();
        break;

    case kind::double_:
        os << jv.get_double();
        break;

    case kind::bool_:
        os << jv.get_bool();
        break;

    case kind::null:
        os << "null";
        break;
    }

    if (indent->empty())
        os << "\n";
}

// TODO: This should not necessary!  TScanProps should be able to contain
// any type so that no conversions here are needed.
static object serializeScanProps(const TScanProps &scanProps) {
    static auto isDigit = [](unsigned char c){ return std::isdigit(c); };

    object scan;
    for (const auto &prop : scanProps) {
        const auto &val = prop.second;
        if (std::all_of(val.begin(), val.end(), isDigit))
            scan[prop.first] = boost::lexical_cast<int>(val);
        else
            scan[prop.first] = val;
    }

    return scan;
}

class SimpleTreeEncoder: public AbstractTreeEncoder {
    public:
        /// import supported scan properties
        void importScanProps(const TScanProps &) override;

        /// append single defect
        void appendDef(const Defect &) override;

        /// write everything to the given output stream
        void writeTo(std::ostream &) override;

    private:
        object                      root_;
        array                      *pDefects_ = nullptr;
};

void SimpleTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    if (scanProps.empty())
        return;

    root_["scan"] = serializeScanProps(scanProps);
}

void SimpleTreeEncoder::appendDef(const Defect &def)
{
    // go through events
    array evtList;
    for (const DefEvent &evt : def.events) {
        object evtNode;

        // describe the location
        evtNode["file_name"] = evt.fileName;
        evtNode["line"] = evt.line;
        if (0 < evt.column)
            evtNode["column"] = evt.column;

        // describe the event
        evtNode["event"] = evt.event;
        evtNode["message"] = sanitizeUTF8(evt.msg);
        evtNode["verbosity_level"] = evt.verbosityLevel;

        // append the event to the list
        evtList.push_back(std::move(evtNode));
    }

    // create a node for a single defect
    object defNode;
    defNode["checker"] = def.checker;
    if (!def.annotation.empty())
        defNode["annotation"] = def.annotation;

    // write "defect_id", "cwe", etc. if available
    if (0 < def.defectId)
        defNode["defect_id"] = def.defectId;
    if (0 < def.cwe)
        defNode["cwe"] = def.cwe;
    if (0 < def.imp)
        defNode["imp"] = def.imp;
    if (!def.function.empty())
        defNode["function"] = def.function;
    if (!def.language.empty())
        defNode["language"] = def.language;
    if (!def.tool.empty())
        defNode["tool"] = def.tool;

    defNode["key_event_idx"] = def.keyEventIdx;
    defNode["events"] = std::move(evtList);

    // create the node representing the list of defects
    if (!pDefects_)
        pDefects_ = &root_["defects"].emplace_array();

    // append the node to the list
    pDefects_->push_back(std::move(defNode));
}

void SimpleTreeEncoder::writeTo(std::ostream &str)
{
    if (!pDefects_)
        // create an empty "defects" node to keep format detection working
        pDefects_ = &root_["defects"].emplace_array();

    prettyPrint(str, root_);
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
        object                      driver_;
        array                       results_;
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

    driver_["name"] = std::move(tool);

    if (!ver.empty())
        driver_["version"] = std::move(ver);

    if (!uri.empty())
        driver_["informationUri"] = std::move(uri);
}

static void sarifEncodeShellCheckRule(object *rule, const std::string &ruleID)
{
    // name
    rule->emplace("name", ruleID);

    // properties.tags[]
    object props = {
        { "tags", { "ShellCheck" } }
    };
    rule->emplace("properties", std::move(props));

    // help.text && help.markdown
    auto helpURI = "https://github.com/koalaman/shellcheck/wiki/" + ruleID;
    auto helpMarkdown = "Defect reference: [" + ruleID +"](" + helpURI + ")";

    object help = {
        { "text", "Defect reference: " + helpURI },
        { "markdown", std::move(helpMarkdown) }
    };

    rule->emplace("help", std::move(help));
}

static void sarifEncodeCweRule(object *rule, const int cwe, bool append = false)
{
    auto cweStr = std::to_string(cwe);
    array cweList = { "CWE-" + cweStr };

    // properties.cwe[]
    if (append) {
        object &props = rule->at("properties").as_object();
        props["cwe"] = std::move(cweList);
    } else {
        object props = {
            { "cwe", std::move(cweList) }
        };
        rule->emplace("properties", std::move(props));
    }

    // help.text
    auto helpText =
        "https://cwe.mitre.org/data/definitions/" + cweStr + ".html";

    if (append) {
        object &help = rule->at("help").as_object();
        help["text"].as_string() += '\n' + std::move(helpText);
    } else {
        object help = {
            { "text", std::move(helpText) }
        };
        rule->emplace("help", help);
    }
}

void SarifTreeEncoder::serializeRules()
{
    array ruleList;
    for (const auto &item : shellCheckMap_) {
        const auto &id = item.first;
        object rule = {
            { "id", id }
        };

        sarifEncodeShellCheckRule(&rule, item.second);
        if (1U == cweMap_.count(id))
            sarifEncodeCweRule(&rule, cweMap_[id], /*append =*/ true);

        ruleList.push_back(std::move(rule));
    }

    for (const auto &item : cweMap_) {
        const auto &id = item.first;
        if (1U == shellCheckMap_.count(id))
            continue;

        object rule = {
            { "id", id }
        };

        sarifEncodeCweRule(&rule, item.second);
        ruleList.push_back(std::move(rule));
    }

    driver_["rules"] = std::move(ruleList);
}

void SarifTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    scanProps_ = scanProps;
}

static void sarifEncodeMsg(object *pDst, const std::string& text)
{
    object message = {
        { "text", sanitizeUTF8(text) }
    };

    pDst->emplace("message", std::move(message) );
}

static void sarifEncodeLevel(object *result, const std::string &event)
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
            result->emplace("level", std::move(level));
            return;
        }
    }
}

static void sarifEncodeLoc(object *pLoc, const Defect &def, unsigned idx)
{
    // location ID within the result
    pLoc->emplace("id", idx);

    const DefEvent &evt = def.events[idx];

    // file name
    object locPhy = {
        { "artifactLocation", {
            { "uri", evt.fileName }
        }}
    };

    // line/col
    if (evt.line) {
        object reg = {
            { "startLine", evt.line }
        };

        if (evt.column)
            reg["startColumn"] = evt.column;

        locPhy["region"] = std::move(reg);
    }

    // location
    pLoc->emplace("physicalLocation", std::move(locPhy));
}

static void sarifEncodeComment(array *pDst, const Defect &def, unsigned idx)
{
    object comment;

    // needed for Github to see the SARIF data as valid
    sarifEncodeLoc(&comment, def, idx);

    sarifEncodeMsg(&comment, def.events[idx].msg);
    pDst->push_back(std::move(comment));
}

static void sarifEncodeEvt(array *pDst, const Defect &def, unsigned idx)
{
    const DefEvent &evt = def.events[idx];

    // location + message
    object loc;
    sarifEncodeLoc(&loc, def, idx);
    sarifEncodeMsg(&loc, evt.msg);

    // threadFlowLocation
    object tfLoc = {
        { "location", std::move(loc) },
        // verbosityLevel
        { "nestingLevel", evt.verbosityLevel },
        // event
        { "kinds", { evt.event } }
    };

    // append the threadFlowLocation object to the destination array
    pDst->push_back(std::move(tfLoc));
}

void SarifTreeEncoder::appendDef(const Defect &def)
{
    const DefEvent &keyEvt = def.events[def.keyEventIdx];
    object result;

    // checker (FIXME: suboptimal mapping to SARIF)
    const std::string ruleId = def.checker + ": " + keyEvt.event;
    result["ruleId"] = ruleId;

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
    object loc;
    sarifEncodeLoc(&loc, def, def.keyEventIdx);
    result["locations"] = array{std::move(loc)};

    // key msg
    sarifEncodeMsg(&result, keyEvt.msg);

    // other events
    array flowLocs, relatedLocs;
    for (unsigned i = 0; i < def.events.size(); ++i) {
        if (def.events[i].event == "#")
            sarifEncodeComment(&relatedLocs, def, i);
        else
            sarifEncodeEvt(&flowLocs, def, i);
    }

    // codeFlows
    result["codeFlows"] = {
        // threadFlows
        {{ "threadFlows", {
            // locations
            {{ "locations", std::move(flowLocs) }}
        }}}
    };

    if (!relatedLocs.empty())
        // our stash for comments
        result["relatedLocations"] = std::move(relatedLocs);

    // append the `result` object to the `results` array
    results_.push_back(std::move(result));
}

void SarifTreeEncoder::writeTo(std::ostream &str)
{
    object root = {
        // mandatory: schema/version
        { "$schema", "https://json.schemastore.org/sarif-2.1.0.json" },
        { "version", "2.1.0" }
    };

    if (!scanProps_.empty()) {
        // scan props
        root["inlineExternalProperties"] = {
            {{ "externalizedProperties", serializeScanProps(scanProps_) }}
        };
    }

    this->initToolVersion();

    if (!cweMap_.empty() || !shellCheckMap_.empty())
        // needs to run before we pick driver_
        this->serializeRules();

    object run0 = {
        { "tool", {
            { "driver", std::move(driver_) }
        }}
    };

    // results
    run0["results"] = std::move(results_);

    // mandatory: runs
    root["runs"] = array{std::move(run0)};

    // encode as JSON
    prettyPrint(str, root);
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
    // transfer scan properties if available
    d->encoder->importScanProps(d->scanProps);

    // go through the queue and move defects one by one to the property tree
    for (; !d->defQueue.empty(); d->defQueue.pop())
        d->encoder->appendDef(d->defQueue.front());

    // finally encode the tree as JSON
    d->encoder->writeTo(d->str);
}
