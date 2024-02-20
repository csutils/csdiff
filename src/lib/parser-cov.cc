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

#include "parser-cov.hh"

#include "parser-common.hh"
#include "regex.hh"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <sstream>

#include <boost/algorithm/string.hpp>

namespace CovParserImpl {

class LineReader {
    public:
        LineReader(std::istream &input):
            input_(input)
        {
        }

        int lineNo() const {
            return lineNo_;
        }

        bool getLine(std::string *pDst);

    private:
        std::istream               &input_;
        int                         lineNo_ = 0;

        const RE reTrailLoc_ = RE("^(path:|/).*(:[0-9]+|<.*>):$");
        const RE rePathPref_ = RE("^path:");

        bool getLinePriv(std::string *pDst);
};

bool LineReader::getLinePriv(std::string *pDst)
{
    if (!std::getline(input_, *pDst))
        return false;

    lineNo_++;
    return true;
}

bool LineReader::getLine(std::string *pDst)
{
    std::string line;
    if (!this->getLinePriv(&line))
        return false;

    std::string nextLine;
    while (boost::regex_search(line, reTrailLoc_)
            && this->getLinePriv(&nextLine))
    {
        // merge the current line with the next line
        nextLine.insert(/* pos */ 0U, " ");
        line += nextLine;
    }

    // remove the "path:" prefix if matched
    *pDst = boost::regex_replace(line, rePathPref_, "");

    return true;
}

enum EToken {
    T_NULL = 0,
    T_EMPTY,
    T_COMMENT,
    T_UNKNOWN,
    T_CHECKER,
    T_EVENT
};

std::ostream& operator<<(std::ostream &str, EToken code)
{
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
            lineReader_(input),
            hasError_(false)
        {
        }

        bool hasError() const {
            return hasError_;
        }

        int lineNo() const {
            return lineReader_.lineNo();
        }

        const Defect& def() const {
            return def_;
        }

        const DefEvent& evt() const {
            return evt_;
        }

        EToken readNext();

    private:
        LineReader                  lineReader_;
        bool                        hasError_;
        Defect                      def_;
        DefEvent                    evt_;

        const RE reEmpty_ =
            RE("^ *$");

        const RE reComment_ =
            RE("^(#)(.*)$");

        const RE reChecker_ =
            RE("^Error: *(" RE_CHECKER_NAME ")( *\\([^)]+\\))? *:(?: \\[#def[0-9]+\\])?$");

        const RE reEvent_ =
            RE(/* location */ "^(" RE_PATH ")(?::([0-9]+|<[Uu]nknown>))?(?::([0-9]+))?"
               /* evt/mesg */ ": (" RE_EVENT "): (.*)$");
};

EToken ErrFileLexer::readNext()
{
    std::string line;
    if (!lineReader_.getLine(&line))
        return T_NULL;

    if (boost::regex_match(line, reEmpty_))
        return T_EMPTY;

    boost::smatch sm;

    if (boost::regex_match(line, sm, reChecker_)) {
        def_ = Defect(sm[/* checker */ 1]);
        def_.annotation = sm[/* annotation */ 2];
        return T_CHECKER;
    }

    if (boost::regex_match(line, sm, reComment_)) {
        evt_ = DefEvent();
        evt_.event  = sm[/* #     */ 1];
        evt_.msg    = sm[/* msg   */ 2];
        return T_COMMENT;
    }

    if (!boost::regex_match(line, sm, reEvent_)) {
        evt_.msg = std::move(line);
        return T_UNKNOWN;
    }

    // read file name, event, and msg
    evt_.fileName   = sm[/* file  */ 1];
    evt_.event      = sm[/* event */ 4];
    evt_.msg        = sm[/* msg   */ 5];

    // parse line number
    evt_.line = parse_int(sm[/* line */ 2]);

    // parse column number
    evt_.column = parse_int(sm[/* col */ 3]);

    return T_EVENT;
}

} // namespace CovParserImpl

using namespace CovParserImpl;

struct KeyEventDigger::Private {
    typedef std::set<std::string>                   TSet;
    typedef std::map<std::string, TSet>             TMap;
    TMap hMap;
    TSet denyList, traceEvts;
    const RE reEvtSuffix = RE("^(.*)\\[[^ \\]]+\\]$");
    const std::string stripEvtName(const std::string &) const;
};

/// strip the [-W...] suffix from event name
const std::string KeyEventDigger::Private::stripEvtName(const std::string &evt)
    const
{
    boost::smatch sm;
    if (boost::regex_match(evt, sm, this->reEvtSuffix))
        return sm[/* bare evt */ 1];

    // no match
    return evt;
}

KeyEventDigger::KeyEventDigger():
    d(new Private)
{
    // register checker-specific key events
    d->hMap["BAD_CHECK_OF_WAIT_COND"]    .insert("wait_cond_improperly_checked");
    d->hMap["BAD_LOCK_OBJECT"]           .insert("boxed_lock");
    d->hMap["BAD_LOCK_OBJECT"]           .insert("lock_on_assigned_field");
    d->hMap["BAD_LOCK_OBJECT"]           .insert("single_thread_lock");
    d->hMap["CALL_SUPER"]                .insert("missing_super_call");
    d->hMap["CHECKED_RETURN"]            .insert("check_return");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("extra_high_bits");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("logical_vs_bitwise");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("missing_parentheses");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("operator_confusion");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("pointless_expression");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("result_independent_of_operands");
    d->hMap["CONSTANT_EXPRESSION_RESULT"].insert("same_on_both_sides");
    d->hMap["EXPLICIT_THIS_EXPECTED"]    .insert("implicit_this_used");
    d->hMap["FORWARD_NULL"]              .insert("deref_parm");
    d->hMap["FORWARD_NULL"]              .insert("dereference");
    d->hMap["FORWARD_NULL"]              .insert("var_deref_op");
    d->hMap["FORWARD_NULL"]              .insert("var_deref_model");
    d->hMap["LOCK"]                      .insert("double_lock");
    d->hMap["LOCK"]                      .insert("double_unlock");
    d->hMap["MISSING_BREAK"]             .insert("unterminated_case");
    d->hMap["NESTING_INDENT_MISMATCH"]   .insert("dangling_else");
    d->hMap["NESTING_INDENT_MISMATCH"]   .insert("multi_stmt_macro");
    d->hMap["NESTING_INDENT_MISMATCH"]   .insert("on_same_line");
    d->hMap["NESTING_INDENT_MISMATCH"]   .insert("uncle");
    d->hMap["ORDER_REVERSAL"]            .insert("lock_acquire");
    d->hMap["OVERRUN_STATIC"]            .insert("index_parm");
    d->hMap["OVERRUN_STATIC"]            .insert("overrun-buffer-arg");
    d->hMap["OVERRUN_STATIC"]            .insert("overrun-local");
    d->hMap["STREAM_FORMAT_STATE"]       .insert("format_changed");
    d->hMap["UNINIT"]                    .insert("uninit_use");
    d->hMap["UNINIT"]                    .insert("uninit_use_in_call");
    d->hMap["UNINIT_CTOR"]               .insert("uninit_member");
    d->hMap["USE_AFTER_FREE"]            .insert("deref_after_free");
    d->hMap["USE_AFTER_FREE"]            .insert("deref_arg");
    d->hMap["USE_AFTER_FREE"]            .insert("double_free");
    d->hMap["USE_AFTER_FREE"]            .insert("pass_freed_arg");
    d->hMap["USE_AFTER_FREE"]            .insert("use_after_free");

    // we use COMPILER_WARNING as checker for compiler errors/warnings
    d->hMap["COMPILER_WARNING"]     .insert("error");
    d->hMap["COMPILER_WARNING"]     .insert("warning");
    d->hMap["COMPILER_WARNING"]     .insert("fatal error");
    // likewise for clang
    d->hMap["CLANG_WARNING"]        .insert("error");
    d->hMap["CLANG_WARNING"]        .insert("warning");
    d->hMap["CLANG_WARNING"]        .insert("fatal error");
    // ... and `gcc -fanalyzer`
    d->hMap["GCC_ANALYZER_WARNING"] .insert("error");
    d->hMap["GCC_ANALYZER_WARNING"] .insert("warning");
    d->hMap["GCC_ANALYZER_WARNING"] .insert("fatal error");

    // OWASP ZAP uses "alert" as the key event
    d->hMap["OWASP_ZAP_WARNING"]    .insert("alert");

    // events that should never be used as key events (excluding trace events)
    d->denyList.insert("another_instance");
    d->denyList.insert("comparison_remediation");
    d->denyList.insert("example_access");
    d->denyList.insert("example_assign");
    d->denyList.insert("example_checked");
    d->denyList.insert("example_comparison");
    d->denyList.insert("example_lock");
    d->denyList.insert("function_annotation");
    d->denyList.insert("included_from");
    d->denyList.insert("note");
    d->denyList.insert("remediation");
    d->denyList.insert("rounding_remediation");
    d->denyList.insert("scope_hint");

    // trace events
    d->traceEvts.insert("break");
    d->traceEvts.insert("caretline");
    d->traceEvts.insert("cond_false");
    d->traceEvts.insert("cond_true");
    d->traceEvts.insert("continue");
    d->traceEvts.insert("destructor");
    d->traceEvts.insert("else_branch");
    d->traceEvts.insert("end_of_path");
    d->traceEvts.insert("finally");
    d->traceEvts.insert("finally_jump");
    d->traceEvts.insert("for_loop");
    d->traceEvts.insert("goto");
    d->traceEvts.insert("if_end");
    d->traceEvts.insert("if_fallthrough");
    d->traceEvts.insert("label");
    d->traceEvts.insert("loop");
    d->traceEvts.insert("loop_begin");
    d->traceEvts.insert("loop_end");
    d->traceEvts.insert("path");
    d->traceEvts.insert("return");
    d->traceEvts.insert("switch");
    d->traceEvts.insert("switch_case");
    d->traceEvts.insert("switch_default");
    d->traceEvts.insert("switch_end");
    d->traceEvts.insert("try_end");
    d->traceEvts.insert("try_fallthrough");
}

KeyEventDigger::~KeyEventDigger()
{
    delete d;
}

bool KeyEventDigger::guessKeyEvent(Defect *def)
{
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
        const std::string evtName = d->stripEvtName(evt.event);
        if (!pKeyEvents->count(evtName))
            continue;

        // matched
        def->keyEventIdx = idx;
        return true;
    }

    // use the last event as key event by default (unless deny-listed)
    for (int pass = 0; pass < 2; ++pass) {
        for (int idx = evtCount - 1U; idx >= 0; --idx) {
            const DefEvent &evt = evtList[idx];
            if (evt.event == "#")
                // never use comment as the key event
                continue;


            // never use trace or deny-listed event as the key event
            // (but pick the last one of there are no other events)
            if (!pass) {
                const std::string &evtName = evt.event;
                if (d->traceEvts.count(evtName) || d->denyList.count(evtName))
                    continue;
            }

            // matched
            def->keyEventIdx = idx;
            return true;
        }
    }

    // no valid key event
    return false;
}

void KeyEventDigger::initVerbosity(Defect *def)
{
    TEvtList &evtList = def->events;
    const unsigned evtCount = evtList.size();
    for (unsigned idx = 0U; idx < evtCount; ++idx) {
        DefEvent &evt = evtList[idx];
        evt.verbosityLevel = (idx == def->keyEventIdx)
            ? /* key event */ 0
            : 1 + /* trace event */ !!d->traceEvts.count(evt.event);
    }
}

class AnnotHandler {
    public:
        void handleDef(Defect *);

    private:
        const RE reCweAnnot_ = RE("^ *\\(CWE-([0-9]+)\\)$");
};

void AnnotHandler::handleDef(Defect *pDef)
{
    boost::smatch sm;
    if (boost::regex_match(pDef->annotation, sm, reCweAnnot_)) {
        pDef->cwe = parse_int(sm[/* cwe */ 1]);
        pDef->annotation.clear();
    }
}

struct CovParser::Private {
    ErrFileLexer            lexer;
    std::string             fileName;
    const bool              silent;
    bool                    hasError;
    EToken                  code;
    KeyEventDigger          keDigger;
    AnnotHandler            annotHdl;
    ImpliedAttrDigger       digger;

    Private(InStream &input_):
        lexer(input_.str()),
        fileName(input_.fileName()),
        silent(input_.silent()),
        hasError(false),
        code(T_NULL)
    {
    }

    void parseError(const std::string &msg);
    void wrongToken(EToken expected = T_NULL);
    bool seekForToken(EToken, TEvtList *pEvtList);
    bool parseMsg(TEvtList *pEvtList);
    bool parseNext(Defect *);
};

CovParser::CovParser(InStream &input):
    d(new Private(input))
{
}

CovParser::~CovParser()
{
    delete d;
}

bool CovParser::hasError() const
{
    return d->lexer.hasError()
        || d->hasError;
}

void CovParser::Private::parseError(const std::string &msg)
{
    this->hasError = true;
    if (this->silent)
        return;

    std::cerr << this->fileName
        << ":" << this->lexer.lineNo()
        << ": parse error: " << msg << "\n";
}

void CovParser::Private::wrongToken(const EToken expected)
{
    std::ostringstream str;
    str << "wrong token: " << this->code;
    if (T_NULL != expected)
        str << " (expected " << expected << ")";
    this->parseError(str.str());
}

bool CovParser::Private::seekForToken(const EToken token, TEvtList *pEvtList)
{
    for (;;) {
        if (token == this->code)
            return true;

        bool stopReached = false;

        switch (this->code) {
            case T_NULL:
                // read the first defect from the input stream
                break;

            case T_EMPTY:
                // skip empty lines while seeking for a token
                break;

            case T_COMMENT:
                // capture a comment event
                pEvtList->push_back(this->lexer.evt());
                break;

            case T_CHECKER:
                // stop the seek now (to allow recovery in higher levels)
                stopReached = true;
                // fall through!

            default:
                this->wrongToken(token);
        }

        this->code = this->lexer.readNext();

        if (stopReached || (T_NULL == this->code))
            return false;
    }
}

bool CovParser::Private::parseMsg(TEvtList *pEvtList)
{
    bool anyComment = false;

    // parse event
    if (!this->seekForToken(T_EVENT, pEvtList)) {
        this->wrongToken(T_EVENT);
        return false;
    }

    pEvtList->push_back(this->lexer.evt());

    // parse extra msg
    for (;;) {
        this->code = this->lexer.readNext();
        switch (this->code) {
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

bool CovParser::Private::parseNext(Defect *def)
{
    // parse defect header
    TEvtList evtList;
    if (!this->seekForToken(T_CHECKER, &evtList))
        return false;

    *def = this->lexer.def();
    def->events.swap(evtList);

    // parse defect body
    this->code = this->lexer.readNext();
    for (;;) {
        switch (this->code) {
            case T_EMPTY:
                // unless T_EVENT follows, we are done with this defect
                do {
                    this->code = this->lexer.readNext();
                }
                while (T_EMPTY == this->code);
                if (T_EVENT == this->code)
                    continue;
                // fall through!

            case T_NULL:
            case T_CHECKER:
                goto done;

            case T_COMMENT:
                // capture a comment event
                def->events.push_back(this->lexer.evt());
                this->code = this->lexer.readNext();
                continue;

            default:
                this->parseMsg(&def->events);
        }
    }

done:
    if (!this->keDigger.guessKeyEvent(def)) {
        this->parseError("failed to guess key event");
        return false;
    }

    this->keDigger.initVerbosity(def);
    this->annotHdl.handleDef(def);
    this->digger.inferLangFromChecker(def);
    this->digger.inferToolFromChecker(def);

    // all OK
    return true;
}

bool CovParser::getNext(Defect *def)
{
    // error recovery loop
    do {
        if (d->parseNext(def))
            return true;
    }
    while (T_NULL != d->code);

    return false;
}
