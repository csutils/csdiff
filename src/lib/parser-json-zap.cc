/*
 * Copyright (C) 2022 Red Hat, Inc.
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

#include "parser-json-zap.hh"

struct ZapTreeDecoder::Private {
    std::string                     timeStamp;
    Defect                          defPrototype = Defect("OWASP_ZAP_WARNING");
    const pt::ptree                *alertList = nullptr;
    pt::ptree::const_iterator       alertIter;

    Private()
    {
        this->defPrototype.tool = "owasp-zap";
    }

    void readAlert(Defect *pDef, const pt::ptree &alertNode);
};

template <typename TPropList>
void readNonEmptyProps(
        TEvtList                   *pDst,
        const pt::ptree            &node,
        const DefEvent             &evtProto,
        const TPropList            &propList)
{
    // make our own copy of the given prototype event
    DefEvent evt = evtProto;

    for (const auto &evtName : propList) {
        evt.event = evtName;
        evt.msg = valueOf<std::string>(node, evtName);
        if (!evt.msg.empty())
            pDst->push_back(evt);
    }
}

void ZapTreeDecoder::Private::readAlert(Defect *pDef, const pt::ptree &alertNode)
{
    // read per-defect properties
    *pDef = this->defPrototype;
    pDef->cwe = valueOf<int>(alertNode, "cweid");
    pDef->imp = (1 < valueOf<int>(alertNode, "riskcode"));

    // get "uri" for the key event
    std::string uri;
    const pt::ptree *instList = nullptr;
    if (findChildOf(&instList, alertNode, "instances")) {
        for (const auto &item : *instList) {
            uri = valueOf<std::string>(item.second, "uri");
            if (!uri.empty())
                // found!
                break;
        }
    }

    TEvtList &events = pDef->events;
    if (uri.empty() && !events.empty())
        // fallback to "uri" from the prototype event
        uri = events.front().fileName;

    // initialize key event
    DefEvent evt("alert");
    evt.fileName = uri;

    // read "alertRef" if available
    const auto alertRef = valueOf<std::string>(alertNode, "alertRef");
    if (!alertRef.empty())
        evt.event += "[" + alertRef + "]";

    // read "alert" if available
    evt.msg = valueOf<std::string>(alertNode, "alert");

    // append the key event
    pDef->keyEventIdx = events.size();
    events.push_back(evt);

    // read other per-alert events if available
    evt.verbosityLevel = /* info event */ 1;
    const auto defProps = { "desc", "solution", "otherinfo", "reference" };
    readNonEmptyProps(&events, alertNode, evt, defProps);

    if (!instList)
        // no instances to go through
        return;

    // read per-instance properties
    const auto instProps = { "method", "param", "attack", "evidence" };
    for (const auto &item : *instList) {
        const pt::ptree &instNode = item.second;
        evt.fileName = valueOf<std::string>(instNode, "uri");
        if (evt.fileName.empty())
            // no "uri" for this instance
            continue;

        readNonEmptyProps(&events, instNode, evt, instProps);
    }
}

ZapTreeDecoder::ZapTreeDecoder():
    d(new Private)
{
}

ZapTreeDecoder::~ZapTreeDecoder() = default;

void ZapTreeDecoder::readScanProps(
        TScanProps                 *pDst,
        const pt::ptree            *root)
{
    const auto version = valueOf<std::string>(*root, "@version");
    if (!version.empty())
        (*pDst)["analyzer-version-owasp-zap"] = version;

    d->timeStamp = valueOf<std::string>(*root, "@generated");
}

bool ZapTreeDecoder::readNode(Defect *pDef)
{
    // iterate over sites unless we are processing a site already
    while (!d->alertList || d->alertList->end() == d->alertIter) {
        const pt::ptree *siteNode = this->nextNode();
        if (!siteNode)
            // failed initialization or EOF
            return false;

        if (!findChildOf(&d->alertList, *siteNode, "alerts")) {
            // "alerts" node missing for this site
            d->alertList = nullptr;
            continue;
        }

        // initialize iteration over alerts
        d->alertIter = d->alertList->begin();

        if (d->alertList->end() != d->alertIter) {
            // site with alerts found -> update defect prototype based on site
            d->defPrototype.events.clear();
            const auto siteName = valueOf<std::string>(*siteNode, "@name");
            if (!siteName.empty() && !d->timeStamp.empty()) {
                // create a prototype "note" event
                DefEvent siteEvt("note");
                siteEvt.fileName = std::move(siteName);
                siteEvt.msg = "dynamically analyzed on " + d->timeStamp;
                siteEvt.verbosityLevel = /* info event */ 1;
                d->defPrototype.events.push_back(std::move(siteEvt));
            }

            break;
        }
    }

    // get the current alert and move to the next one
    const auto itNow = d->alertIter++;

    // process the current alert
    d->readAlert(pDef, itNow->second);

    return true;
}
