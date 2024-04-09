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

struct RuleProps {
    int                 cweId;
    std::string         scRuleId;
    std::string         tool;
};

struct SarifTreeEncoder::Private {
    using TRuleMap = std::map<std::string, RuleProps>;
    TRuleMap                    ruleMap;

    TScanProps                  scanProps;
    boost::json::object         driver;
    boost::json::array          results;
    CtxEventDetector            ctxEvtDetetor;

    void initToolVersion();
    void serializeRules();
};

SarifTreeEncoder::SarifTreeEncoder():
    d(new Private)
{
}

SarifTreeEncoder::~SarifTreeEncoder() = default;

void SarifTreeEncoder::Private::initToolVersion()
{
    std::string tool;
    auto it = this->scanProps.find("tool");
    if (this->scanProps.end() != it)
        // read "tool" scan property
        tool = it->second;

    std::string ver;
    it = this->scanProps.find("tool-version");
    if (this->scanProps.end() != it) {
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
    else if (this->scanProps.end() != (it = this->scanProps.find("tool-url")))
        // read "tool-url" scan property
        uri = it->second;

    this->driver["name"] = std::move(tool);

    if (!ver.empty())
        this->driver["version"] = std::move(ver);

    if (!uri.empty())
        this->driver["informationUri"] = std::move(uri);
}

static void sarifEncodeShellCheckRule(object *rule, const std::string &ruleID)
{
    // name
    rule->emplace("name", ruleID);

    // properties.tags[]
    array tags = { "ShellCheck" };
    object &props = rule->at("properties").as_object();
    props["tags"] = std::move(tags);

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
    object &props = rule->at("properties").as_object();
    props["cwe"] = std::move(cweList);

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

void SarifTreeEncoder::Private::serializeRules()
{
    array ruleList;
    for (const auto &item : this->ruleMap) {
        const auto &id = item.first;
        const RuleProps &rp = item.second;

        object rule = {
            { "id", id },
            { "properties", object() }
        };

        const bool haveScRule = !rp.scRuleId.empty();
        if (haveScRule)
            sarifEncodeShellCheckRule(&rule, rp.scRuleId);
        else if (!rp.tool.empty()) {
            // encode tool tag
            array tags = { rp.tool };
            object &props = rule["properties"].as_object();
            props["tags"] = std::move(tags);
        }

        if (rp.cweId)
            sarifEncodeCweRule(&rule, rp.cweId, /*append =*/ haveScRule);

        ruleList.push_back(std::move(rule));
    }

    this->driver["rules"] = std::move(ruleList);
}

void SarifTreeEncoder::importScanProps(const TScanProps &scanProps)
{
    d->scanProps = scanProps;
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

    if (evt.line) {
        // line/col
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

void sarifEncodeSnippet(object &result, const std::string &msg)
{
    // resolve key event region
    value &valLoc = result["locations"].get_array().front();
    value &valPhy = valLoc.get_object()["physicalLocation"];
    object &reg = valPhy.get_object()["region"].get_object();

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

        // update ShellCheck rule ID
        d->ruleMap[ruleId].scRuleId = sm[2];
    }

    if (def.cwe) {
        // update CWE ID
        d->ruleMap[ruleId].cweId = def.cwe;

        // encode per-warning CWE property
        object cweProp = {{ "cwe", "CWE-" + std::to_string(def.cwe) }};
        result["properties"] = std::move(cweProp);
    }

    if (!def.tool.empty())
        // update tool for this rule
        d->ruleMap[ruleId].tool = def.tool;

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
        const DefEvent &evt = def.events[i];
        if (evt.event != "#") {
            // regular event
            sarifEncodeEvt(&flowLocs, def, i);
            continue;
        }

        if (d->ctxEvtDetetor.isAnyCtxLine(evt))
            // code snippet
            sarifEncodeSnippet(result, evt.msg);

        // any comment
        sarifEncodeComment(&relatedLocs, def, i);
    }

    // codeFlows
    result["codeFlows"] = array{
        // threadFlows
        {{ "threadFlows", array{
            // locations
            {{ "locations", std::move(flowLocs) }}
        }}}
    };

    if (!relatedLocs.empty())
        // our stash for comments
        result["relatedLocations"] = std::move(relatedLocs);

    // append the `result` object to the `results` array
    d->results.push_back(std::move(result));
}

void SarifTreeEncoder::writeTo(std::ostream &str)
{
    object root = {
        // mandatory: schema/version
        { "$schema", "https://json.schemastore.org/sarif-2.1.0.json" },
        { "version", "2.1.0" }
    };

    if (!d->scanProps.empty()) {
        // scan props
        root["inlineExternalProperties"] = array{
            {{ "externalizedProperties", jsonSerializeScanProps(d->scanProps) }}
        };
    }

    d->initToolVersion();

    if (!d->ruleMap.empty())
        // needs to run before we pick d->driver
        d->serializeRules();

    object run0 = {
        { "tool", {
            { "driver", std::move(d->driver) }
        }}
    };

    // results
    run0["results"] = std::move(d->results);

    // mandatory: runs
    root["runs"] = array{std::move(run0)};

    // encode as JSON
    jsonPrettyPrint(str, std::move(root));
}
