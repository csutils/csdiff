#include "csdiff.hh"

#include <FlexLexer.h>

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <string>
#include <vector>

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

class PrivateFlexLexer: public yyFlexLexer {
    public:
        PrivateFlexLexer(std::istream &input, std::string fileName):
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

struct DefMsg {
    std::string             fileName;
    int                     line;
    int                     column;
    std::string             msg;
};

struct Defect {
    std::string             defClass;
    std::vector<DefMsg>     msgs;
};

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

class Parser {
    public:
        Parser(std::istream &input, std::string fileName):
            lexer_(input, fileName),
            fileName_(fileName),
            hasError_(false),
            code_(T_NULL)
        {
        }

        bool getNext(Defect *);
        bool hasError() const { return lexer_.hasError() || hasError_; }

    private:
        PrivateFlexLexer    lexer_;
        std::string         fileName_;
        bool                hasError_;
        EToken              code_;

    private:
        void wrongToken();
        bool seekForToken(const EToken);
        bool parseClass(Defect *);
        bool parseLine(DefMsg *);
        bool parseMsg(DefMsg *);
        bool parseNext(Defect *);
};

void Parser::wrongToken() {
    hasError_ = true;
    std::cerr << fileName_ << ":" << lexer_.lineno()
        << ": parse error: wrong token: " << code_ << "\n";
}

bool Parser::seekForToken(const EToken token) {
    if (token == code_)
        return true;

    do {
        code_ = lexer_.readNext();
        if (T_NULL == code_)
            return false;

        if (token == code_)
            return true;

        this->wrongToken();
    }
    while (T_INIT != code_);

    return false;
}

bool Parser::parseClass(Defect *def) {
    char *end;
    char *text = strdup(lexer_.YYText());
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
    this->wrongToken();
    return false;
}

bool Parser::parseLine(DefMsg *msg) {
    char *beg, *end;
    char *text = strdup(lexer_.YYText());
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
    this->wrongToken();
    return false;
}

bool Parser::parseMsg(DefMsg *msg) {
    // parse file
    if (seekForToken(T_FILE))
        msg->fileName = lexer_.YYText();
    else
        return false;

    // parse line/column
    if (!seekForToken(T_LINE) || !parseLine(msg))
        return false;

    // parse basic msg
    if (seekForToken(T_MSG))
        msg->msg = lexer_.YYText();
    else
        return false;

    // parse extra msg
    for (;;) {
        code_ = lexer_.readNext();
        switch (code_) {
            case T_NULL:
            case T_INIT:
            case T_FILE:
                return true;

            case T_MSG_EX:
                msg->msg += "\n";
                msg->msg += lexer_.YYText();
                continue;

            default:
                this->wrongToken();
                return false;
        }
    }
}

bool Parser::parseNext(Defect *def) {
    // parse defect header
    if (!seekForToken(T_INIT) || !seekForToken(T_DEFECT) || !parseClass(def))
        return false;

    // parse defect body
    while (T_NULL != code_ && T_INIT != code_) {
        DefMsg msg;
        if (!parseMsg(&msg))
            return false;

        // append single message
        def->msgs.push_back(msg);
    }

    return true;
}

bool Parser::getNext(Defect *def) {
    // error recovery loop
    do {
        if (this->parseNext(def))
            return true;
    }
    while (T_NULL != code_);

    return false;
}

class PathFilter {
    private:
        static PathFilter *self_;
        const boost::regex re_;

        PathFilter():
            re_("(?:/builddir/build/BUILD/)[^/]+/")
        {
        }

    public:
        static PathFilter* inst() {
            return (self_)
                ? (self_)
                : (self_ = new PathFilter);
        }

        std::string filter(const std::string &path) {
            return boost::regex_replace(path, re_, "");
        }
};

PathFilter* PathFilter::self_;

class MsgFilter {
    private:
        static MsgFilter *self_;
        const boost::regex re_;

        MsgFilter():
            re_("[0-9][0-9]* out of [0-9][0-9]* times")
        {
        }

    public:
        static MsgFilter* inst() {
            return (self_)
                ? (self_)
                : (self_ = new MsgFilter);
        }

        std::string filter(const std::string &msg) {
            return boost::regex_replace(msg, re_, "");
        }
};

MsgFilter* MsgFilter::self_;

// TODO: optimize such that no deep copies of strings are necessary
typedef std::vector<Defect>                     TDefList;
typedef std::map<std::string, TDefList>         TDefByMsg;
typedef std::map<std::string, TDefByMsg>        TDefByFile;
typedef std::map<std::string, TDefByFile>       TDefByClass;

template <class TStor>
void hashDefect(TStor &stor, const Defect &def)
{
    TDefByFile &row = stor[def.defClass];

    const DefMsg &msg = def.msgs.front();
    TDefByMsg &col = row[PathFilter::inst()->filter(msg.fileName)];
    TDefList &cell = col[MsgFilter::inst()->filter(msg.msg)];

    cell.push_back(def);
}

template <class TStor>
bool lookup(TStor &stor, const Defect &def)
{
    // look for defect class
    TDefByClass::iterator iRow = stor.find(def.defClass);
    if (stor.end() == iRow)
        return false;

    // simplify path
    const DefMsg &msg = def.msgs.front();
    const std::string path(PathFilter::inst()->filter(msg.fileName));

    // look for file name
    TDefByFile &row = iRow->second;
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol)
        return false;

    // look by msg
    TDefByMsg &col = iCol->second;
    TDefByMsg::iterator iCell = col.find(MsgFilter::inst()->filter(msg.msg));
    if (col.end() == iCell)
        return false;

    // FIXME: nasty over-approximation
    TDefList &defs = iCell->second;
    unsigned cnt = defs.size();
    if (cnt)
        // just remove an arbitrary one
        defs.resize(cnt - 1);
    else
        return false;

    // TODO: add some other criteria in order to make the match more precise
    return true;
}

int main(int argc, char *argv[])
{
    // check if file names were given
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " old.err new.err\n";
        return EXIT_FAILURE;
    }

    // open old
    const char *fnOld = argv[1];
    std::fstream strOld(fnOld, std::ios::in);
    if (!strOld) {
        std::cerr << fnOld << ": failed to open input file\n";
        return EXIT_FAILURE;
    }

    // open new
    const char *fnNew = argv[2];
    std::fstream strNew(fnNew, std::ios::in);
    if (!strNew) {
        std::cerr << fnNew << ": failed to open input file\n";
        strOld.close();
        return EXIT_FAILURE;
    }

    // read old
    Parser pOld(strOld, fnOld);
    TDefByClass stor;
    Defect def;
    while (pOld.getNext(&def))
        hashDefect(stor, def);

    // read new
    Parser pNew(strNew, fnNew);
    while (pNew.getNext(&def)) {
        if (lookup(stor, def))
            continue;

        // a newly added defect found
        std::cout << def;
    }

    // close streams
    strOld.close();
    strNew.close();

    return pOld.hasError()
        || pNew.hasError();
}
