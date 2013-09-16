/*
 * Copyright (C) 2011-2013 Red Hat, Inc.
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

#include "csparser.hh"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

enum EToken {
    T_NULL = 0,
    T_UNKNOWN,
    T_CHECKER,
    T_EVENT
};

std::ostream& operator<<(std::ostream &str, EToken code) {
    switch (code) {
        case T_NULL:    str << "T_NULL";    break;
        case T_UNKNOWN: str << "T_UNKNOWN"; break;
        case T_CHECKER: str << "T_CHECKER"; break;
        case T_EVENT:   str << "T_EVENT";   break;
    }

    return str;
}

class ErrFileLexer {
    public:
        ErrFileLexer(std::istream &input):
            input_(input),
            hasError_(false),
            lineNo_(0),
            reEmpty_("^ *|#.*$"),
            reChecker_("^Error: *([A-Za-z][A-Za-z_.]+)( *\\([^)]+\\))? *:$"),
            reEvent_(
                    /* location */ "^([^:]+)(?::([0-9]+))?(?::([0-9]+))?"
                    /* evt/mesg */ ": ([a-z][\\[\\]A-Za-z_-]+): (.*)$")
        {
        }

        bool hasError() const {
            return hasError_;
        }

        int lineNo() const {
            return lineNo_;
        }

        const Defect& def() const {
            return def_;
        }

        const DefEvent& evt() const {
            return evt_;
        }

        EToken readNext();

    private:
        std::istream               &input_;
        bool                        hasError_;
        int                         lineNo_;
        Defect                      def_;
        DefEvent                    evt_;
        const boost::regex          reEmpty_;
        const boost::regex          reChecker_;
        const boost::regex          reEvent_;
};

EToken ErrFileLexer::readNext() {
    for (;;) {
        std::string line;
        if (!std::getline(input_, line))
            return T_NULL;

        lineNo_++;

        if (boost::regex_match(line, reEmpty_))
            continue;

        boost::smatch sm;

        if (boost::regex_match(line, sm, reChecker_)) {
            def_ = Defect();
            def_.checker    = sm[/* checker */ 1];
            def_.annotation = sm[/* annotat */ 2];
            return T_CHECKER;
        }

        if (!boost::regex_match(line, sm, reEvent_)) {
            evt_.msg = line;
            return T_UNKNOWN;
        }

        // read file name, event, and msg
        evt_.fileName   = sm[/* file  */ 1];
        evt_.event      = sm[/* event */ 4];
        evt_.msg        = sm[/* msg   */ 5];

        // parse line number
        try {
            evt_.line = boost::lexical_cast<int>(sm[/* line */ 2]);
        }
        catch (boost::bad_lexical_cast &) {
            evt_.line = 0;
        }

        // parse column number
        try {
            evt_.column = boost::lexical_cast<int>(sm[/* col */ 3]);
        }
        catch (boost::bad_lexical_cast &) {
            evt_.column = 0;
        }

        return T_EVENT;
    }
}

struct KeyEventDigger::Private {
    typedef std::set<std::string>                   TSet;
    typedef std::map<std::string, TSet>             TMap;
    TMap hMap;
    TSet blackList;
};

KeyEventDigger::KeyEventDigger():
    d(new Private)
{
    // register checker-specific key events
    d->hMap["FORWARD_NULL"]         .insert("deref_parm");
    d->hMap["FORWARD_NULL"]         .insert("dereference");
    d->hMap["FORWARD_NULL"]         .insert("var_deref_op");
    d->hMap["FORWARD_NULL"]         .insert("var_deref_model");
    d->hMap["ORDER_REVERSAL"]       .insert("lock_acquire");
    d->hMap["OVERRUN_STATIC"]       .insert("index_parm");
    d->hMap["OVERRUN_STATIC"]       .insert("overrun-buffer-arg");
    d->hMap["OVERRUN_STATIC"]       .insert("overrun-local");
    d->hMap["UNINIT"]               .insert("uninit_use");
    d->hMap["UNINIT"]               .insert("uninit_use_in_call");
    d->hMap["UNINIT_CTOR"]          .insert("uninit_member");
    d->hMap["USE_AFTER_FREE"]       .insert("deref_after_free");
    d->hMap["USE_AFTER_FREE"]       .insert("deref_arg");
    d->hMap["USE_AFTER_FREE"]       .insert("double_free");
    d->hMap["USE_AFTER_FREE"]       .insert("pass_freed_arg");
    d->hMap["USE_AFTER_FREE"]       .insert("use_after_free");

    // we use COMPILER_WARNING as checker for compiler errors/warnings
    d->hMap["COMPILER_WARNING"]     .insert("error");
    d->hMap["COMPILER_WARNING"]     .insert("warning");

    // do not match the lowered checker name of the following checkers
    d->hMap["LOCK"];

    // events that should never be used as key events
    d->blackList.insert("break");
    d->blackList.insert("cond_false");
    d->blackList.insert("cond_true");
    d->blackList.insert("continue");
    d->blackList.insert("else_branch");
    d->blackList.insert("end_of_path");
    d->blackList.insert("goto");
    d->blackList.insert("if_end");
    d->blackList.insert("if_fallthrough");
    d->blackList.insert("label");
    d->blackList.insert("loop");
    d->blackList.insert("loop_begin");
    d->blackList.insert("loop_end");
    d->blackList.insert("switch");
    d->blackList.insert("switch_case");
    d->blackList.insert("switch_default");
    d->blackList.insert("switch_end");
    d->blackList.insert("return");
}

KeyEventDigger::~KeyEventDigger() {
    delete d;
}

bool KeyEventDigger::guessKeyEvent(Defect *def) {
    const std::vector<DefEvent> &evtList = def->events;
    if (evtList.empty())
        return false;

    const unsigned evtCount = evtList.size();
    Private::TSet defKeyEvent;
    const Private::TSet *pKeyEvents = &defKeyEvent;

    Private::TMap::const_iterator it = d->hMap.find(def->checker);
    if (d->hMap.end() == it) {
        // no override for the checker -> match the lowered checker name
        std::string str(def->checker);
        boost::algorithm::to_lower(str);
        defKeyEvent.insert(str);
    }
    else
        // use the corresponding set of events from d->hMap
        pKeyEvents = &it->second;

    for (int idx = evtCount - 1U; idx >= 0; --idx) {
        const DefEvent &evt = evtList[idx];
        if (!pKeyEvents->count(evt.event))
            continue;

        // matched
        def->keyEventIdx = idx;
        return true;
    }

    // use the last event as key event by default (unless black-listed)
    for (int idx = evtCount - 1U; idx >= 0; --idx) {
        def->keyEventIdx = idx;
        const DefEvent &evt = evtList[idx];
        if (!d->blackList.count(evt.event))
            break;
    }

    return true;
}

void KeyEventDigger::initVerbosity(Defect *def) {
    TEvtList &evtList = def->events;
    const unsigned evtCount = evtList.size();
    for (unsigned idx = 0U; idx < evtCount; ++idx) {
        DefEvent &evt = evtList[idx];
        evt.verbosityLevel = (idx == def->keyEventIdx)
            ? /* key event */ 0
            : 1 + /* trace event */ !!d->blackList.count(evt.event);
    }

}

struct CovParser::Private {
    ErrFileLexer            lexer;
    std::string             fileName;
    const bool              silent;
    bool                    hasError;
    EToken                  code;
    KeyEventDigger          keDigger;

    Private(std::istream &input_, std::string fileName_, bool silent_):
        lexer(input_),
        fileName(fileName_),
        silent(silent_),
        hasError(false),
        code(T_NULL)
    {
    }

    void parseError(const std::string &msg);
    void wrongToken();
    bool seekForToken(const EToken);
    bool parseMsg(DefEvent *);
    bool parseNext(Defect *);
};

CovParser::CovParser(
        std::istream                &input,
        const std::string           &fileName,
        const bool                   silent):
    d(new Private(input, fileName, silent))
{
}

CovParser::~CovParser() {
    delete d;
}

bool CovParser::hasError() const {
    return d->lexer.hasError()
        || d->hasError;
}

void CovParser::Private::parseError(const std::string &msg) {
    this->hasError = true;
    if (this->silent)
        return;

    std::cerr << this->fileName
        << ":" << this->lexer.lineNo()
        << ": parse error: " << msg << "\n";
}

void CovParser::Private::wrongToken() {
    std::ostringstream str;
    str << "wrong token: " << this->code;
    this->parseError(str.str());
}

bool CovParser::Private::seekForToken(const EToken token) {
    if (token == code)
        return true;

    do {
        code = this->lexer.readNext();
        if (T_NULL == code)
            return false;

        if (token == code)
            return true;

        this->wrongToken();
    }
    while (T_CHECKER != code);

    return false;
}

bool CovParser::Private::parseMsg(DefEvent *evt) {
    // parse event
    if (seekForToken(T_EVENT))
        *evt = this->lexer.evt();
    else
        goto fail;

    // parse extra msg
    for (;;) {
        code = lexer.readNext();
        switch (code) {
            case T_NULL:
            case T_CHECKER:
            case T_EVENT:
                // all OK
                return true;

            case T_UNKNOWN:
                evt->msg += "\n";
                evt->msg += this->lexer.evt().msg;
                continue;

            default:
                goto fail;
        }
    }

fail:
    this->wrongToken();
    return false;
}

bool CovParser::Private::parseNext(Defect *def) {
    // parse defect header
    if (!seekForToken(T_CHECKER))
        return false;

    *def = this->lexer.def();

    // parse defect body
    code = lexer.readNext();
    while (T_NULL != code && T_CHECKER != code) {
        DefEvent evt;
        if (!parseMsg(&evt))
            continue;

        // append single event
        def->events.push_back(evt);
    }

    if (this->keDigger.guessKeyEvent(def)) {
        this->keDigger.initVerbosity(def);

        // all OK
        return true;
    }

    this->wrongToken();
    return false;
}

bool CovParser::getNext(Defect *def) {
    // error recovery loop
    do {
        if (d->parseNext(def))
            return true;
    }
    while (T_NULL != d->code);

    return false;
}
