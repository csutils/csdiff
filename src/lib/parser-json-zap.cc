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
    Defect                          sitePrototype;
    Defect                          alertPrototype;
    const pt::ptree                *alertList = nullptr;
    const pt::ptree                *instList = nullptr;
    pt::ptree::const_iterator       alertIter;
    pt::ptree::const_iterator       instIter;

    Private()
    {
        this->sitePrototype.checker = "OWASP_ZAP_WARNING";
        this->sitePrototype.tool    = "owasp-zap";
    }

    void readSiteProto(const pt::ptree &siteNode);
    void readAlertProto(const pt::ptree &alertNode);
    void readAlertInst(Defect *pDef, const pt::ptree &instNode);
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

void ZapTreeDecoder::Private::readSiteProto(const pt::ptree &siteNode)
{
    this->sitePrototype.events.clear();
    const auto siteName = valueOf<std::string>(siteNode, "@name");
    if (siteName.empty() || this->timeStamp.empty())
        return;

    // create a prototype "note" event
    DefEvent siteEvt("note");
    siteEvt.fileName = std::move(siteName);
    siteEvt.msg = "dynamically analyzed on " + this->timeStamp;
    siteEvt.verbosityLevel = /* info event */ 1;
    this->sitePrototype.events.push_back(std::move(siteEvt));
}

void ZapTreeDecoder::Private::readAlertProto(const pt::ptree &alertNode)
{
    // read per-alert properties
    this->alertPrototype = this->sitePrototype;
    this->alertPrototype.cwe = valueOf<int>(alertNode, "cweid");
    this->alertPrototype.imp = (1 < valueOf<int>(alertNode, "riskcode"));

    // initialize key event
    DefEvent evt("alert");

    // get "uri" from the prototype event
    TEvtList &events = this->alertPrototype.events;
    if (!events.empty())
        evt.fileName = events.front().fileName;

    // read "alertRef" if available
    const auto alertRef = valueOf<std::string>(alertNode, "alertRef");
    if (!alertRef.empty())
        evt.event += "[" + alertRef + "]";

    // read "alert" if available
    evt.msg = valueOf<std::string>(alertNode, "alert");

    // append the key event
    this->alertPrototype.keyEventIdx = events.size();
    events.push_back(evt);

    // read other per-alert events if available
    evt.verbosityLevel = /* info event */ 1;
    const auto defProps = { "desc", "solution", "otherinfo", "reference" };
    readNonEmptyProps(&events, alertNode, evt, defProps);
}

void ZapTreeDecoder::Private::readAlertInst(
        Defect                      *pDef,
        const pt::ptree             &instNode)
{
    // start with the prototype initialized by readAlertProto()
    *pDef = this->alertPrototype;
    TEvtList &events = pDef->events;

    // reinitialize events with "uri" specific for this instance (if available)
    const std::string uri = valueOf<std::string>(instNode, "uri");
    if (!uri.empty())
        for (DefEvent &evt : events)
            evt.fileName = uri;

    // use the key event as a prototype for instance-specific events
    DefEvent evtProto = events[pDef->keyEventIdx];
    evtProto.verbosityLevel = /* info event */ 1;

    // read per-instance properties
    const auto instProps = { "method", "param", "attack", "evidence" };
    readNonEmptyProps(&events, instNode, evtProto, instProps);
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
        (*pDst)["analyzer-version-owasp-zap"] = std::move(version);

    d->timeStamp = valueOf<std::string>(*root, "@generated");
}

const pt::ptree* ZapTreeDecoder::nextAlert()
{
    // iterate over sites unless we are processing a site already
    while (!d->alertList || d->alertList->end() == d->alertIter) {
        const pt::ptree *siteNode = this->nextNode();
        if (!siteNode)
            // failed initialization or EOF
            return nullptr;

        if (!findChildOf(&d->alertList, *siteNode, "alerts")) {
            // "alerts" node missing for this site
            d->alertList = nullptr;
            continue;
        }

        // initialize iteration over alerts
        d->alertIter = d->alertList->begin();
        d->instList = nullptr;

        if (!d->alertList->empty())
            // site with alerts found --> update site prototype
            d->readSiteProto(*siteNode);
    }

    // get the current alert and move to the next one
    const auto itAlertNow = d->alertIter++;
    return &itAlertNow->second;
}

bool ZapTreeDecoder::readNode(Defect *pDef)
{
    if (!d->instList || d->instList->end() == d->instIter) {
        // iterate over alerts
        const pt::ptree *alertNode = this->nextAlert();
        if (!alertNode)
            // failed initialization or EOF
            return false;

        // process the current alert
        d->readAlertProto(*alertNode);

        // read the list of instances
        if (!findChildOf(&d->instList, *alertNode, "instances")
                || d->instList->empty())
        {
            // no instances for this alert --> emit the prototype
            d->instList = nullptr;
            *pDef = d->alertPrototype;
            return true;
        }

        // initialize iteration over instances
        d->instIter = d->instList->begin();
    }

    // get the current instance and move to the next one
    const auto itInstNow = d->instIter++;

    // process the current instance
    d->readAlertInst(pDef, itInstNow->second);
    return true;
}
