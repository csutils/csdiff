#include "csparser.hh"
#include "csparser-priv.hh"

#include <FlexLexer.h>

#include <cctype>
#include <cstdlib>
#include <cstring>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

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

std::ostream& operator<<(std::ostream &str, const Defect &def) {
    str << "\nError: " << def.defClass << ":\n";

    BOOST_FOREACH(const DefMsg &msg, def.msgs) {
        str << msg.fileName << ":" << msg.line << ":";

        if (0 < msg.column)
            str << msg.column << ":";

        str << " " << msg.msg << "\n";
    }

    return str;
}

class FlexLexerWrap: public yyFlexLexer {
    public:
        FlexLexerWrap(std::istream &input, std::string fileName):
            yyFlexLexer(&input, &std::cerr),
            fileName_(fileName),
            hasError_(false)
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

struct Parser::Private {
    FlexLexerWrap           lexer;
    std::string             fileName;
    bool                    hasError;
    EToken                  code;

    Private(std::istream &input_, std::string fileName_):
        lexer(input_, fileName_),
        fileName(fileName_),
        hasError(false),
        code(T_NULL)
    {
    }

    void wrongToken();
    bool seekForToken(const EToken);
    bool parseClass(Defect *);
    bool parseLine(DefMsg *);
    bool parseMsg(DefMsg *);
    bool parseNext(Defect *);
};

Parser::Parser(std::istream &input, std::string fileName):
    d(new Private(input, fileName))
{
}

Parser::~Parser() {
    delete d;
}

bool Parser::hasError() const {
    return d->lexer.hasError()
        || d->hasError;
}

void Parser::Private::wrongToken() {
    this->hasError = true;
    std::cerr << this->fileName
        << ":" << this->lexer.lineno()
        << ": parse error: wrong token: "
        << this->code << "\n";
}

bool Parser::Private::seekForToken(const EToken token) {
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

bool Parser::Private::parseClass(Defect *def) {
    char *end;
    char *text = strdup(lexer.YYText());
    if (!text || !isupper(text[0]))
        goto fail;

    end = strchr(text, ':');
    if (!end || end[1])
        goto fail;

    // OK
    *end = '\0';
    def->defClass = text;
    def->msgs.clear();
    free(text);
    return true;

fail:
    free(text);
    return false;
}

bool Parser::Private::parseLine(DefMsg *msg) {
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
    msg->line = boost::lexical_cast<int>(beg);

    // parse column
    beg = end + 1;
    end = strchr(beg, ':');
    if (end) {
        *end = '\0';
        msg->column = boost::lexical_cast<int>(beg);
    }
    else
        msg->column = 0;

    free(text);
    return true;

fail:
    free(text);
    return false;
}

bool Parser::Private::parseMsg(DefMsg *msg) {
    // parse file
    if (seekForToken(T_FILE))
        msg->fileName = lexer.YYText();
    else
        goto fail;

    // parse line/column
    if (!seekForToken(T_LINE) || !parseLine(msg))
        goto fail;

    // parse basic msg
    if (seekForToken(T_MSG))
        msg->msg = lexer.YYText();
    else
        goto fail;

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
                msg->msg += "\n";
                msg->msg += lexer.YYText();
                continue;

            default:
                goto fail;
        }
    }

fail:
    this->wrongToken();
    return false;
}

bool Parser::Private::parseNext(Defect *def) {
    // parse defect header
    if (!seekForToken(T_INIT))
        return false;

    if (!seekForToken(T_DEFECT) || !parseClass(def))
        goto fail;

    // parse defect body
    while (T_NULL != code && T_INIT != code) {
        DefMsg msg;
        if (!parseMsg(&msg))
            return false;

        // append single message
        def->msgs.push_back(msg);
    }

    if (!def->msgs.empty())
        // all OK
        return true;

fail:
    this->wrongToken();
    return false;
}

bool Parser::getNext(Defect *def) {
    // error recovery loop
    do {
        if (d->parseNext(def))
            return true;
    }
    while (T_NULL != d->code);

    return false;
}
