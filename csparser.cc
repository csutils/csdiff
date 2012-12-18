/*
 * Copyright (C) 2011-2012 Red Hat, Inc.
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
#include "csparser-priv.hh"

#include <FlexLexer.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>

#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/null.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/lexical_cast.hpp>

std::ostream& operator<<(std::ostream &str, EToken code) {
    switch (code) {
        case T_NULL:    str << "T_NULL";    break;
        case T_INIT:    str << "T_INIT";    break;
        case T_DEFECT:  str << "T_DEFECT";  break;
        case T_FILE:    str << "T_FILE";    break;
        case T_LINE:    str << "T_LINE";    break;
        case T_MSG:     str << "T_MSG";     break;
        case T_MSG_EX:  str << "T_MSG_EX";  break;
    }

    return str;
}

class FlexLexerWrap: public yyFlexLexer {
    private:
        typedef boost::iostreams::basic_null_sink<char> TSink;
        TSink                           sinkPriv_;
        boost::iostreams::stream<TSink> sink_;

    public:
        FlexLexerWrap(std::istream &input, std::string fileName, bool silent):
            yyFlexLexer(&input, (silent) ? &sink_ : &std::cerr),
            sink_(sinkPriv_),
            fileName_(fileName),
            hasError_(false),
            silent_(false)
        {
        }

        bool hasError() const   { return hasError_; }
        EToken readNext() {
            silent_ = false;
            return static_cast<EToken>(this->yylex());
        }

    protected:
        /// override default output behavior
        virtual void LexerOutput(const char *buf, int size) {
            std::string msg(buf, size);
            this->LexerError(msg.c_str());
        }

        /// override default error behavior
        virtual void LexerError(const char *msg) {
            if (silent_)
                return;

            silent_ = true;
            hasError_ = true;
            std::ostream &str = *(this->yyout);
            str << fileName_ << ":" << this->lineno()
                << ": lexical error: " << msg << "\n";
        }

    private:
        std::string         fileName_;
        bool                hasError_;
        bool                silent_;
};

class KeyEventDigger {
    private:
        typedef std::set<std::string>               TSet;
        typedef std::map<std::string, TSet>         TMap;
        TMap hMap_;
        TSet blackList_;

    public:
        KeyEventDigger();
        bool guessKeyEvent(Defect *);
};

KeyEventDigger::KeyEventDigger() {
    // register checker-specific key events
    hMap_["FORWARD_NULL"]           .insert("deref_parm");
    hMap_["FORWARD_NULL"]           .insert("dereference");
    hMap_["FORWARD_NULL"]           .insert("var_deref_op");
    hMap_["FORWARD_NULL"]           .insert("var_deref_model");
    hMap_["OVERRUN_STATIC"]         .insert("index_parm");
    hMap_["OVERRUN_STATIC"]         .insert("overrun-buffer-arg");
    hMap_["OVERRUN_STATIC"]         .insert("overrun-local");
    hMap_["UNINIT"]                 .insert("uninit_use");
    hMap_["UNINIT"]                 .insert("uninit_use_in_call");
    hMap_["UNINIT_CTOR"]            .insert("uninit_member");
    hMap_["USE_AFTER_FREE"]         .insert("deref_after_free");
    hMap_["USE_AFTER_FREE"]         .insert("deref_arg");
    hMap_["USE_AFTER_FREE"]         .insert("double_free");
    hMap_["USE_AFTER_FREE"]         .insert("pass_freed_arg");
    hMap_["USE_AFTER_FREE"]         .insert("use_after_free");
    hMap_["ORDER_REVERSAL"]         .insert("lock_acquire");

    // events that should never be used as key events
    blackList_.insert("break");
    blackList_.insert("cond_false");
    blackList_.insert("cond_true");
    blackList_.insert("else_branch");
    blackList_.insert("end_of_path");
    blackList_.insert("goto");
    blackList_.insert("if_end");
    blackList_.insert("if_fallthrough");
    blackList_.insert("label");
    blackList_.insert("loop");
    blackList_.insert("loop_begin");
    blackList_.insert("loop_end");
    blackList_.insert("switch_end");
    blackList_.insert("return");
}

bool KeyEventDigger::guessKeyEvent(Defect *def) {
    const std::vector<DefEvent> &evtList = def->events;
    if (evtList.empty())
        return false;

    const unsigned evtCount = evtList.size();
    TSet defKeyEvent;
    const TSet *pKeyEvents = &defKeyEvent;

    TMap::const_iterator it = hMap_.find(def->checker);
    if (hMap_.end() == it) {
        // no override for the checker -> match the lowered checker name
        std::string str(def->checker);
        boost::algorithm::to_lower(str);
        defKeyEvent.insert(str);
    }
    else
        // use the corresponding set of events from KeyEventDigger::hMap_
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
        if (!blackList_.count(evt.event))
            break;
    }

    return true;
}

struct CovParser::Private {
    FlexLexerWrap           lexer;
    std::string             fileName;
    const bool              silent;
    bool                    hasError;
    EToken                  code;
    KeyEventDigger          keDigger;

    Private(std::istream &input_, std::string fileName_, bool silent_):
        lexer(input_, fileName_, silent_),
        fileName(fileName_),
        silent(silent_),
        hasError(false),
        code(T_NULL)
    {
    }

    void wrongToken();
    bool seekForToken(const EToken);
    bool parseClass(Defect *);
    bool parseLine(DefEvent *);
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

void CovParser::Private::wrongToken() {
    this->hasError = true;
    if (this->silent)
        return;

    std::cerr << this->fileName
        << ":" << this->lexer.lineno()
        << ": parse error: wrong token: "
        << this->code << "\n";
}

bool CovParser::Private::seekForToken(const EToken token) {
    if (token == code)
        return true;

    do {
        code = lexer.readNext();
        if (T_NULL == code)
            return false;

        if (token == code)
            return true;

        this->wrongToken();
    }
    while (T_INIT != code);

    return false;
}

bool CovParser::Private::parseClass(Defect *def) {
    char *ann, *end;
    char *text = strdup(lexer.YYText());
    if (!text || !isupper((unsigned char) text[0]))
        goto fail;

    end = strchr(text, ':');
    if (!end || end[1])
        goto fail;

    // OK
    *end = '\0';

    // look for annotation
    ann = strpbrk(text, " (");
    if (ann) {
        def->annotation = ann;
        *ann = '\0';
    }
    else
        def->annotation.clear();

    def->checker = text;
    def->events.clear();
    free(text);
    return true;

fail:
    free(text);
    return false;
}

bool CovParser::Private::parseLine(DefEvent *evt) {
    char *beg, *end;
    char *text = strdup(lexer.YYText());
    if (!text || ':' != text[0])
        goto fail;

    // parse line
    beg = text + 1;
    end = strchr(beg, ':');
    if (!end)
        goto fail;

    *end = '\0';
    evt->line = boost::lexical_cast<int>(beg);

    // parse column
    beg = end + 1;
    end = strchr(beg, ':');
    if (end) {
        *end = '\0';
        evt->column = boost::lexical_cast<int>(beg);
    }
    else
        evt->column = 0;

    free(text);
    return true;

fail:
    free(text);
    return false;
}

bool CovParser::Private::parseMsg(DefEvent *evt) {
    char *text;

    // parse file
    if (seekForToken(T_FILE))
        evt->fileName = lexer.YYText();
    else
        goto fail;

    // parse line/column
    if (!seekForToken(T_LINE) || !parseLine(evt))
        goto fail;

    // parse basic msg
    if (!seekForToken(T_MSG))
        goto fail;

    text = const_cast<char *>(lexer.YYText());
    if (!text)
        goto fail;

    // parse event name (if any)
    if (!isupper((unsigned char) text[0])) {
        char *pos = strchr(text, ':');
        if (pos && pos[1]) {
            *pos = '\0';
            evt->event = text;
            *pos = ':';
            text = pos /* skip ": " */ + 2;
        }
    }

    // store basic msg
    evt->msg = text;

    // parse extra msg
    for (;;) {
        code = lexer.readNext();
        switch (code) {
            case T_NULL:
            case T_INIT:
            case T_FILE:
                // all OK
                return true;

            case T_MSG_EX:
                evt->msg += "\n";
                evt->msg += lexer.YYText();
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
    if (!seekForToken(T_INIT))
        return false;

    if (!seekForToken(T_DEFECT) || !parseClass(def))
        goto fail;

    // parse defect body
    while (T_NULL != code && T_INIT != code) {
        DefEvent evt;
        if (!parseMsg(&evt))
            return false;

        // append single event
        def->events.push_back(evt);
    }

    if (this->keDigger.guessKeyEvent(def))
        // all OK
        return true;

fail:
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
