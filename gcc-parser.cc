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

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

enum EToken {
    T_NULL = 0,
    T_UNKNOWN,

    T_INC,
    T_SCOPE,
    T_MSG,
    T_MSG_EXTRA,
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

class Tokenizer: public ITokenizer {
    public:
        Tokenizer(std::istream &input):
            input_(input),
            lineNo_(0),
            reMarker_("^ *\\^$"),
            reMsg_(
                    /* location */ "^([^:]+)(?::([0-9]+))?(?::([0-9]+))?:"
                    /* evt/mesg */ " ([a-z]+): (.*)$")
        {
        }

        virtual int lineNo() const {
            return lineNo_;
        }

        virtual EToken readNext(DefEvent *pEvt);

    private:
        std::istream           &input_;
        int                     lineNo_;
        const boost::regex      reMarker_;
        const boost::regex      reMsg_;
};

EToken Tokenizer::readNext(DefEvent *pEvt) {
    std::string line;
    if (!std::getline(input_, line))
        return T_NULL;

    lineNo_++;

    if (boost::regex_match(line, reMarker_))
        return T_MARKER;

    boost::smatch sm;
    if (!boost::regex_match(line, sm, reMsg_))
        return T_UNKNOWN;

    // read file name, event, and msg
    pEvt->fileName    = sm[/* file */ 1];
    pEvt->event       = sm[/* evt  */ 4];
    pEvt->msg         = sm[/* msg  */ 5];

    // parse line number
    try {
        pEvt->line = boost::lexical_cast<int>(sm[/* line */ 2]);
    }
    catch (boost::bad_lexical_cast &) {
        pEvt->line = 0;
    }

    // parse column number
    try {
        pEvt->column = boost::lexical_cast<int>(sm[/* col */ 3]);
    }
    catch (boost::bad_lexical_cast &) {
        pEvt->column = 0;
    }

    return T_MSG;
}

class MarkerRemover: public AbstractTokenFilter {
    public:
        MarkerRemover(ITokenizer *slave):
            AbstractTokenFilter(slave)
        {
        }

        virtual EToken readNext(DefEvent *pEvt);
};

EToken MarkerRemover::readNext(DefEvent *pEvt) {
    EToken tok = slave_->readNext(pEvt);
    if (T_UNKNOWN != tok)
        return tok;

    tok = slave_->readNext(pEvt);
    if (T_MARKER != tok)
        return tok;

    return slave_->readNext(pEvt);
}

struct GccParser::Private {
    Tokenizer                   rawTokenizer;
    MarkerRemover               tokenizer;
    const std::string           fileName;
    const bool                  silent;
    const boost::regex          reChecker;
    bool                        hasError;

    Private(
            std::istream       &input_,
            const std::string  &fileName_,
            const bool          silent_):
        rawTokenizer(input_),
        tokenizer(&rawTokenizer),
        fileName(fileName_),
        silent(silent_),
        reChecker("^([A-Za-z]+): (.*)$"),
        hasError(false)
    {
    }
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

bool GccParser::getNext(Defect *def) {
    // make sure the Defect structure is properly initialized
    (*def) = Defect();
    def->events.resize(1U);
    DefEvent &evt = def->events.front();

    // error recovery loop
    for (;;) {
        const EToken tok = d->tokenizer.readNext(&evt);
        switch (tok) {
            case T_NULL:
                return false;

            case T_MSG:
                break;

            // TODO
            default:
                d->hasError = true;
                if (!d->silent)
                    std::cerr << d->fileName << ":" << d->tokenizer.lineNo()
                        << ": error: invalid syntax\n";
                continue;
        }

        // use cppcheck's ID as the checker string if available
        boost::smatch sm;
        if (boost::regex_match(evt.msg, sm, d->reChecker)) {
            def->checker = sm[/* id  */ 1];
            evt.msg      = sm[/* msg */ 2];
        }
        else
            def->checker = "COMPILER_WARNING";

        return true;
    }
}

bool GccParser::hasError() const {
    return d->hasError;
}
