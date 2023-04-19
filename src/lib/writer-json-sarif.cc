/*
 * Copyright (C) 2011 - 2023 Red Hat, Inc.
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

#include "writer-json-sarif.hh"

#include "regex.hh"
#include "version.hh"
#include "writer-json-common.hh"

using namespace boost::json;

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
    object reg = {
        { "startLine", evt.line }
    };

    if (evt.column)
        reg["startColumn"] = evt.column;

    locPhy["region"] = std::move(reg);

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

void sarifEncodeSnippet(object &reg, const std::string &msg)
{
    // check whether the "snippet" node already exists
    value &valSnip = reg["snippet"];
    if (!valSnip.is_object()) {
        // create the "text" node containing the header line
        valSnip.emplace_object() = {
            { "text", "Problem detected in this context:" }
        };
    }

    // reuse the existing "snippet/text" nodes
    string &strSnip = valSnip.get_object()["text"].get_string();

    // use new-line as delimiter
    strSnip += "\n";

    // concatenate the snippet from this event
    strSnip += msg;
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

    if (def.cwe) {
        // update CWE map
        cweMap_[ruleId] = def.cwe;

        // encode per-warning CWE property
        object cweProp = {{ "cwe", "CWE-" + std::to_string(def.cwe) }};
        result["properties"] = std::move(cweProp);
    }

    // key event severity level
    sarifEncodeLevel(&result, keyEvt.event);

    // key event location
    object loc;
    sarifEncodeLoc(&loc, def, def.keyEventIdx);
    result["locations"] = array{std::move(loc)};

    // resolve key event region
    value &valLoc = result["locations"].get_array().front();
    value &valPhy = valLoc.get_object()["physicalLocation"];
    object &reg = valPhy.get_object()["region"].get_object();

    // key msg
    sarifEncodeMsg(&result, keyEvt.msg);

    // other events
    array flowLocs, relatedLocs;
    for (unsigned i = 0; i < def.events.size(); ++i) {
        const DefEvent &evt = def.events[i];
        if (evt.event != "#") {
            // regular event
            sarifEncodeEvt(&flowLocs, def, i);
            continue;
        }

        if (ctxEvtDetetor_.isAnyCtxLine(evt))
            // code snippet
            sarifEncodeSnippet(reg, evt.msg);

        // any comment
        sarifEncodeComment(&relatedLocs, def, i);
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
            {{ "externalizedProperties", jsonSerializeScanProps(scanProps_) }}
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
    jsonPrettyPrint(str, root);
}
