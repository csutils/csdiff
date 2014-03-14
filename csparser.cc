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
    T_EMPTY,
    T_COMMENT,
    T_UNKNOWN,
    T_CHECKER,
    T_EVENT
};

std::ostream& operator<<(std::ostream &str, EToken code) {
    switch (code) {
        case T_NULL:    str << "T_NULL";    break;
        case T_EMPTY:   str << "T_EMPTY";   break;
        case T_COMMENT: str << "T_COMMENT"; break;
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
            reEmpty_("^ *$"),
            reComment_("^(#)(.*)$"),
            reChecker_("^Error: *([A-Za-z][A-Za-z_.]+)( *\\([^)]+\\))? *:$"),
            reEvent_(
                    /* location */ "^([^:]+)(?::([0-9]+))?(?::([0-9]+))?"
                    /* evt/mesg */ ": ((?:fatal )?[a-z][\\[\\]A-Za-z_-]+): (.*)$")
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
        const boost::regex          reComment_;
        const boost::regex          reChecker_;
        const boost::regex          reEvent_;
};

EToken ErrFileLexer::readNext() {
    std::string line;
    if (!std::getline(input_, line))
        return T_NULL;

    lineNo_++;

    if (boost::regex_match(line, reEmpty_))
        return T_EMPTY;

    boost::smatch sm;

    if (boost::regex_match(line, sm, reChecker_)) {
        def_ = Defect();
        def_.checker    = sm[/* checker */ 1];
        def_.annotation = sm[/* annotat */ 2];
        return T_CHECKER;
    }

    if (boost::regex_match(line, sm, reComment_)) {
        evt_ = DefEvent();
        evt_.event  = sm[/* #     */ 1];
        evt_.msg    = sm[/* msg   */ 2];
        return T_COMMENT;
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
    d->hMap["COMPILER_WARNING"]     .insert("fatal error");
    // likewise for clang
    d->hMap["CLANG_WARNING"]        .insert("error");
    d->hMap["CLANG_WARNING"]        .insert("warning");
    d->hMap["CLANG_WARNING"]        .insert("fatal error");

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
        if (evt.event == "#")
            // never use comment as the key event
            continue;

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
    bool seekForToken(const EToken, TEvtList *pEvtList);
    bool parseMsg(TEvtList *pEvtList);
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

bool CovParser::Private::seekForToken(const EToken token, TEvtList *pEvtList) {
    if (token == code)
        return true;

    for (;;) {
        code = this->lexer.readNext();
        if (token == code)
            return true;

        switch (code) {
            case T_NULL:
            case T_EMPTY:
            case T_CHECKER:
                return false;

            case T_COMMENT:
                // capture a comment event
                pEvtList->push_back(this->lexer.evt());
                continue;

            default:
                this->wrongToken();
        }
    }
}

bool CovParser::Private::parseMsg(TEvtList *pEvtList) {
    bool anyComment = false;

    // parse event
    if (!seekForToken(T_EVENT, pEvtList))
        goto fail;

    pEvtList->push_back(this->lexer.evt());

    // parse extra msg
    for (;;) {
        code = lexer.readNext();
        switch (code) {
            case T_NULL:
            case T_EMPTY:
            case T_CHECKER:
            case T_EVENT:
                // all OK
                return true;

            case T_COMMENT:
                // capture a comment event
                pEvtList->push_back(this->lexer.evt());
                anyComment = true;
                continue;

            case T_UNKNOWN:
                if (anyComment)
                    // interleaving of multi-line msgs with comments not allowed
                    goto fail;

                pEvtList->back().msg += "\n";
                pEvtList->back().msg += this->lexer.evt().msg;
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
    TEvtList evtList;
    while (!seekForToken(T_CHECKER, &evtList))
        if (T_EMPTY != code)
            return false;

    *def = this->lexer.def();
    def->events.swap(evtList);

    // parse defect body
    code = lexer.readNext();
    for (;;) {
        switch (code) {
            case T_NULL:
            case T_EMPTY:
            case T_CHECKER:
                goto done;

            case T_COMMENT:
                // capture a comment event
                def->events.push_back(this->lexer.evt());
                code = lexer.readNext();
                continue;

            default:
                parseMsg(&def->events);
        }
    }

done:
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
