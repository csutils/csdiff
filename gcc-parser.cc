/*
 * Copyright (C) 2013 Red Hat, Inc.
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

#include "gcc-parser.hh"

#include "parser-common.hh"

#include <algorithm>

#include <boost/foreach.hpp>
#include <boost/regex.hpp>

enum EToken {
    T_NULL = 0,
    T_UNKNOWN,

    T_INC,
    T_SCOPE,
    T_MSG,
    T_SIDEBAR,
    T_MARKER
};

class ITokenizer {
    public:
        virtual ~ITokenizer() { }
        virtual EToken readNext(DefEvent *pEvt) = 0;
        virtual int lineNo() const = 0;
};

class AbstractTokenFilter: public ITokenizer {
    public:
        virtual int lineNo() const {
            return slave_->lineNo();
        }

    protected:
        /// @param slave the object will NOT be deleted on destruction
        AbstractTokenFilter(ITokenizer *slave):
            slave_(slave)
        {
        }

        ITokenizer *slave_;
};

#define RE_LOCATION "([^ #:\"][^:\"]+)(?::([0-9]+))?(?::([0-9]+))?"
#define RE_TOOL_SUFFIX "(?: <--\\[[^\\]]+\\])?$"
#define RE_FNC_SMATCH "(\\(null\\)|[_A-Za-z][_A-Za-z0-9]*)\\(\\)"

class Tokenizer: public ITokenizer {
    public:
        Tokenizer(std::istream &input):
            input_(input),
            lineNo_(0),
            reSideBar_("^ *((([0-9]+)? \\| )|(\\+\\+\\+ \\|\\+)).*$"),
            reMarker_("^ *[ ~^|]+$"),
            reInc_("^(?:In file included| +) from " RE_LOCATION "[:,]"
                    RE_TOOL_SUFFIX),
            reScope_("^" RE_LOCATION ": ([A-Z].+):" RE_TOOL_SUFFIX),
            reMsg_("^" RE_LOCATION /* evt/msg */ ": (" RE_EVENT "): (.*)$"),
            reSmatch_("^([^:]+):([0-9]+)() "    /* file:line */
                    RE_FNC_SMATCH               /* fnc       */
                    " ([a-z]+): (.*)$")         /* evt: msg  */
        {
        }

        virtual int lineNo() const {
            return lineNo_;
        }

        virtual EToken readNext(DefEvent *pEvt);

    private:
        std::istream           &input_;
        int                     lineNo_;
        const boost::regex      reSideBar_;
        const boost::regex      reMarker_;
        const boost::regex      reInc_;
        const boost::regex      reScope_;
        const boost::regex      reMsg_;
        const boost::regex      reSmatch_;
};

EToken Tokenizer::readNext(DefEvent *pEvt) {
    std::string line;
    if (!std::getline(input_, line))
        return T_NULL;

    // drop CR at end of the line, coming from GCC in source code snippets
    // NOTE: std::string::back/pop_back() would look better but requires C++11
    if (!line.empty() && '\r' == *line.rbegin())
        line.resize(line.size() - 1U);

    lineNo_++;

    *pEvt = DefEvent();
    pEvt->msg = line;

    // check for line markers produced by gcc-9.2.1 (a.k.a. sidebar)
    if (boost::regex_match(pEvt->msg, reSideBar_))
        //  xxx.c:2:1: note: include '<stdlib.h>' or provide a declaration...
        //    1 | #include <stdio.h>
        //  +++ |+#include <stdlib.h>
        //    2 |
        return T_SIDEBAR;

    if (boost::regex_match(line, reMarker_))
        return T_MARKER;

    EToken tok;
    boost::smatch sm;

    if (boost::regex_match(line, sm, reMsg_)) {
        tok = T_MSG;
        pEvt->event = sm[/* evt  */ 4];
        pEvt->msg   = sm[/* msg  */ 5];
    }
    else if (boost::regex_match(line, sm, reScope_)) {
        tok = T_SCOPE;
        pEvt->event = "scope_hint";
        pEvt->msg   = sm[/* msg  */ 4];
    }
    else if (boost::regex_match(line, sm, reInc_)) {
        tok = T_INC;
        pEvt->event = "included_from";
        pEvt->msg   = "Included from here.";
    }
    else if (boost::regex_match(line, sm, reSmatch_)) {
        tok = T_MSG;
        pEvt->event = sm[/* evt */ 5];
        pEvt->msg   = sm[/* fnc */ 4] + "(): ";
        pEvt->msg  += sm[/* msg */ 6];
    }
    else
        return T_UNKNOWN;

    // read file name, event, and msg
    pEvt->fileName    = sm[/* file */ 1];

    // parse line number
    pEvt->line = parse_int(sm[/* line */ 2]);

    // parse column number
    pEvt->column = parse_int(sm[/* col */ 3]);

    return tok;
}

#define RE_CLANG_EVT "(?:error|warning)"
#define RE_CLANG_CNT_EVTS "(?:(?:1 " RE_CLANG_EVT \
    ")|(?:[0-9]+ " RE_CLANG_EVT "s))"

class NoiseFilter: public AbstractTokenFilter {
    public:
        NoiseFilter(ITokenizer *slave):
            AbstractTokenFilter(slave),
            reClangWarnCnt_("^" RE_CLANG_CNT_EVTS " generated\\.$")
        {
        }

        virtual EToken readNext(DefEvent *);

    private:
        const boost::regex      reClangWarnCnt_;
};

EToken NoiseFilter::readNext(DefEvent *pEvt)
{
    for (;;) {
        const EToken tok = slave_->readNext(pEvt);
        if (T_UNKNOWN != tok)
            return tok;

        if (!boost::regex_match(pEvt->msg, reClangWarnCnt_))
            return tok;
    }
}

class MarkerConverter: public AbstractTokenFilter {
    public:
        MarkerConverter(ITokenizer *slave):
            AbstractTokenFilter(slave),
            lastTok_(T_NULL),
            lineNo_(0)
        {
        }

        virtual int lineNo() const {
            return lineNo_;
        }

        virtual EToken readNext(DefEvent *pEvt);

    private:
        EToken                  lastTok_;
        DefEvent                lastEvt_;
        int                     lineNo_;
};

EToken MarkerConverter::readNext(DefEvent *pEvt) {
    EToken tok = lastTok_;
    if (T_NULL != tok) {
        *pEvt = lastEvt_;
        lineNo_ = slave_->lineNo();
        lastTok_ = T_NULL;
        return tok;
    }

    tok = slave_->readNext(pEvt);
    lineNo_ = slave_->lineNo();
    switch (tok) {
        case T_SIDEBAR:
            pEvt->event = "#";
            tok = T_MSG;
            break;

        case T_UNKNOWN:
            break;

        default:
            return tok;
    }

    lastTok_ = slave_->readNext(&lastEvt_);
    switch (lastTok_) {
        case T_SIDEBAR:
        case T_MARKER:
            break;

        default:
            return tok;
    }

    // translate both events to comments
    lastEvt_.event = pEvt->event = "#";

    // translate both tokens to T_MSG
    lastTok_ = T_MSG;
    return T_MSG;
}

class MultilineConcatenator: public AbstractTokenFilter {
    public:
        MultilineConcatenator(ITokenizer *slave):
            AbstractTokenFilter(slave),
            lastTok_(T_NULL),
#define REASON_SUFFIX "( \\[[^\\]]+\\])?" RE_TOOL_SUFFIX
            reBase_("^([^ ].*[^\\]])" REASON_SUFFIX),
            reExtra_("^ *((?: [^ ].*[^\\]])|(?:\\(.+\\)))" REASON_SUFFIX)
        {
        }

        virtual EToken readNext(DefEvent *pEvt);

    private:
        EToken                  lastTok_;
        DefEvent                lastEvt_;
        const boost::regex      reBase_;
        const boost::regex      reExtra_;

        bool tryMerge(DefEvent *pEvt);
};

bool MultilineConcatenator::tryMerge(DefEvent *pEvt) {
    if (T_MSG != lastTok_)
        // only messages can be merged together
        return false;

    if (pEvt->event == "#")
        // do not concatenate multi-line comments
        return false;

    if (pEvt->event != lastEvt_.event)
        // different kind of event
        return false;

    if (pEvt->fileName != lastEvt_.fileName
            || pEvt->line != lastEvt_.line
            || pEvt->column != lastEvt_.column)
        // different location info
        return false;

    boost::smatch smBase;
    if (!boost::regex_match(pEvt->msg, smBase, reBase_))
        return false;

    boost::smatch smExtra;
    if (!boost::regex_match(lastEvt_.msg, smExtra, reExtra_))
        return false;

    // we need to drop the [-Wreason] suffix from the first message if same
    if (smBase[/* -W suffix */ 2] != smExtra[/* -W suffix */ 2])
        return false;

    assert(!smExtra[/* msg */ 1].str().empty());
    const char *gap = (' ' == *smExtra[/* msg */ 1].str().begin()) ? "" : " ";

    // concatenate both messages together
    pEvt->msg = smBase[/* msg */ 1] + gap
        + smExtra[/* msg */1] + smExtra[/* suf */2];

    // clear the already merged token
    lastTok_ = T_NULL;
    return true;
}

EToken MultilineConcatenator::readNext(DefEvent *pEvt) {
    EToken tok;
    switch (lastTok_) {
        case T_NULL:
            // no last token --> we have to read a new one
            tok = slave_->readNext(pEvt);
            break;

        case T_MSG:
            // reuse the last T_MSG token
            tok = lastTok_;
            *pEvt = lastEvt_;
            break;

        default:
            // flush the last token and bail out
            tok = lastTok_;
            *pEvt = lastEvt_;
            lastTok_ = T_NULL;
            return tok;
    }

    if (T_MSG == tok) {
        do
            // read one token ahead
            lastTok_ = slave_->readNext(&lastEvt_);

        while
            // try to merge it with the previous one
            (this->tryMerge(pEvt));
    }

    return tok;
}

class BasicGccParser {
    public:
        BasicGccParser(
                std::istream       &input,
                const std::string  &fileName,
                const bool          silent):
            rawTokenizer_(input),
            noiseFilter_(&rawTokenizer_),
            markerConverter_(&noiseFilter_),
            tokenizer_(&markerConverter_),
            fileName_(fileName),
            silent_(silent),
            reCppcheck_("^([A-Za-z_]+)(?:\\(CWE-([0-9]+)\\))?: (.*)$"),
            reClang_("^clang.*$"),
            reProspector_(RE_EVENT_PROSPECTOR),
            reShellCheckMsg_("^.* \\[SC[0-9]+\\]$"),
            reSmatchMsg_("^" RE_FNC_SMATCH ": .*$"),
            reTool_("^(.*) <--\\[([^\\]]+)\\]$"),
            hasKeyEvent_(false),
            hasError_(false)
        {
        }

        bool getNext(Defect *);
        bool hasError() const;

    private:
        Tokenizer               rawTokenizer_;
        NoiseFilter             noiseFilter_;
        MarkerConverter         markerConverter_;
        MultilineConcatenator   tokenizer_;
        const std::string       fileName_;
        const bool              silent_;
        const boost::regex      reCppcheck_;
        const boost::regex      reClang_;
        const boost::regex      reProspector_;
        const boost::regex      reShellCheckMsg_;
        const boost::regex      reSmatchMsg_;
        const boost::regex      reTool_;
        bool                    hasKeyEvent_;
        bool                    hasError_;
        Defect                  defCurrent_;

        void handleError();
        bool digCppcheckEvt(Defect *pDef);
        bool exportAndReset(Defect *pDef);
};

void BasicGccParser::handleError() {
    if (!hasKeyEvent_)
        // drop the events captured up to now
        defCurrent_ = Defect();

    hasError_ = true;
    if (silent_)
        return;

    std::cerr << fileName_ << ":" << tokenizer_.lineNo()
        << ": error: invalid syntax\n";
}

bool BasicGccParser::digCppcheckEvt(Defect *pDef) {
    DefEvent &keyEvt = pDef->events[pDef->keyEventIdx];
    if (keyEvt.event == "#")
        // this is just a comment, do not look for real events
        return false;

    boost::smatch sm;
    if (!boost::regex_match(keyEvt.msg, sm, reCppcheck_))
        return false;

    // format produced by cscppc, embed cppcheck checker's ID into the event
    pDef->checker = "CPPCHECK_WARNING";
    keyEvt.event += "[";
    keyEvt.event += sm[/* id  */ 1];
    keyEvt.event += "]";

    // store CWE if available
    pDef->cwe = parse_int(sm[/* cwe */ 2]);

    // this assignment invalidates sm!
    keyEvt.msg = sm[/* msg */ 3];

    return true;
}

bool BasicGccParser::exportAndReset(Defect *pDef) {
    Defect &def = defCurrent_;
    if (!hasKeyEvent_)
        // nothing to export yet
        return false;

    // assume COMPILER_WARNING by default
    def.checker = "COMPILER_WARNING";

    DefEvent &keyEvt = def.events[def.keyEventIdx];

    boost::smatch sm;
    if (boost::regex_match(keyEvt.msg, sm, reTool_)) {
        const std::string tool = sm[/* tool */ 2].str();
        if (boost::regex_match(tool, reClang_))
            // <--[clang] or <--[clang++]
            def.checker = "CLANG_WARNING";

        else if (tool == "shellcheck")
            // <--[shellcheck]
            def.checker = "SHELLCHECK_WARNING";

        else if (tool == "smatch")
            // <--[smatch]
            def.checker = "SMATCH_WARNING";

        else if (tool == "cppcheck" && !this->digCppcheckEvt(&def))
            // <--[cppcheck] ... assume cppcheck running with --template=gcc
            def.checker = "CPPCHECK_WARNING";
    }
    else if (boost::regex_match(keyEvt.event, reProspector_))
        def.checker = "PROSPECTOR_WARNING";
    else if (boost::regex_match(keyEvt.msg, reShellCheckMsg_))
        def.checker = "SHELLCHECK_WARNING";
    else if (boost::regex_match(keyEvt.msg, reSmatchMsg_))
        def.checker = "SMATCH_WARNING";
    else
        // no <--[TOOL] suffix given
        this->digCppcheckEvt(&def);

    // drop the " <--[tool]" suffixes
    BOOST_FOREACH(DefEvent &evt, def.events)
        if (boost::regex_match(evt.msg, sm, reTool_))
            evt.msg = sm[/* msg */ 1];

    // export the current state and clear the data for next iteration
    *pDef = def;
    def = Defect();
    hasKeyEvent_ = false;
    return true;
}

bool BasicGccParser::getNext(Defect *pDef) {
    bool done = false;
    while (!done) {
        DefEvent evt;

        const EToken tok = tokenizer_.readNext(&evt);
        switch (tok) {
            case T_NULL:
                if (!hasKeyEvent_ && !defCurrent_.events.empty())
                    // some events read prior to EOF, but we have no key event
                    this->handleError();

                return this->exportAndReset(pDef);

            case T_INC:
            case T_SCOPE:
                done = this->exportAndReset(pDef);
                defCurrent_.events.push_back(evt);
                break;

            case T_MSG:
                done = this->exportAndReset(pDef);
                defCurrent_.keyEventIdx = defCurrent_.events.size();
                defCurrent_.events.push_back(evt);
                hasKeyEvent_ = true;
                break;

            case T_SIDEBAR:
            case T_MARKER:
            case T_UNKNOWN:
                this->handleError();
                continue;
        }
    }

    return true;
}

bool BasicGccParser::hasError() const {
    return hasError_;
}

class PostProcessor {
    public:
        PostProcessor():
            reGccAnalCoreEvt_("^(.*) \\[-Wanalyzer-[A-Za-z0-9-]+\\]$"),
            reGccAnalCwe_("^.* \\[CWE-([0-9]+)\\]$")
        {
        }

        /// apply final transformations on a successfully parsed defect
        void apply(Defect *pDef);

    private:
        const boost::regex reGccAnalCoreEvt_;
        const boost::regex reGccAnalCwe_;

        void transGccAnal(Defect *pDef);
};

void PostProcessor::transGccAnal(Defect *pDef) {
    if ("COMPILER_WARNING" != pDef->checker)
        return;

    // check for [-Wanalyzer-...] suffix in message of the key event
    DefEvent &keyEvt = pDef->events[pDef->keyEventIdx];
    boost::smatch sm;
    if (!boost::regex_match(keyEvt.msg, sm, reGccAnalCoreEvt_))
        return;

    // COMPILER_WARNING -> GCC_ANALYZER_WARNING
    pDef->checker = "GCC_ANALYZER_WARNING";

    // pick CWE number if available
    const std::string rawMsg = sm[/* msg */ 1];
    if (boost::regex_match(rawMsg, sm, reGccAnalCwe_))
        pDef->cwe = parse_int(sm[/* cwe */ 1]);
}

void PostProcessor::apply(Defect *pDef) {
    this->transGccAnal(pDef);
}

struct GccParser::Private {
    BasicGccParser              core;
    PostProcessor               postProc;
    Defect                      lastDef;
    const boost::regex          reLocation;

    Private(
            std::istream       &input_,
            const std::string  &fileName_,
            const bool          silent_):
        core(input_, fileName_, silent_),
        reLocation("^this is the location.*$")
    {
    }

    bool checkMerge(DefEvent &keyEvt);
    bool tryMerge(Defect *pDef);
};

GccParser::GccParser(
        std::istream           &input,
        const std::string      &fileName,
        const bool              silent):
    d(new Private(input, fileName, silent))
{
}

GccParser::~GccParser() {
    delete d;
}

bool GccParser::Private::checkMerge(DefEvent &keyEvt) {
    if (keyEvt.event == "#")
        // can merge a comment
        return true;

    if (keyEvt.event == "note"
            // shellcheck emits "note" always as key event with no context info
            && this->lastDef.checker != "SHELLCHECK_WARNING")
        // can merge a "note" event
        return true;

    if (keyEvt.event != "warning")
        // we know to merge only notes and warnings
        return false;

    // check whether the warning comes with a location only
    if (!boost::regex_match(keyEvt.msg, this->reLocation))
        return false;

    // translate "warning" -> "note" so that we have an unambiguous key event
    keyEvt.event = "note";
    return true;
}

bool GccParser::Private::tryMerge(Defect *pDef) {
    TEvtList &lastEvts = this->lastDef.events;
    DefEvent &lastKeyEvt = lastEvts[this->lastDef.keyEventIdx];
    if (!this->checkMerge(lastKeyEvt))
        // not something we can merge
        return false;

    if (pDef->checker != this->lastDef.checker && lastKeyEvt.event != "#")
        // do not merge events of incompatible checkers
        return false;

    TEvtList &evts = pDef->events;
    const DefEvent &keyEvt = evts[pDef->keyEventIdx];
    if (keyEvt.event == "note")
        // avoid using "note" as the key event
        return false;

    // concatenate the events and purge the last defect
    std::copy(lastEvts.begin(), lastEvts.end(), std::back_inserter(evts));
    lastEvts.clear();
    return true;
}

bool GccParser::getNext(Defect *pDef) {
    // pick the last defect and clear the stash
    *pDef = d->lastDef;
    d->lastDef.events.clear();
    if (pDef->events.size() <= pDef->keyEventIdx
        // no valid last defect --> read a new one
            && !d->core.getNext(pDef))
        // no valid current defect either
        return false;

    // defect merging loop
    while (d->core.getNext(&d->lastDef) && d->tryMerge(pDef))
        ;

    // initialize verbosityLevel 
    // FIXME: similar code to KeyEventDigger::initVerbosity()
    TEvtList &evtList = pDef->events;
    const unsigned evtCount = evtList.size();
    const unsigned keyEventIdx = pDef->keyEventIdx;
    for (unsigned idx = 0U; idx < evtCount; ++idx)
        evtList[idx].verbosityLevel = (keyEventIdx != idx);

    // apply final transformations
    d->postProc.apply(pDef);

    return true;
}

bool GccParser::hasError() const {
    return d->core.hasError();
}
