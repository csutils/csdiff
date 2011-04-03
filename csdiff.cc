#include "csparser.hh"

#include <fstream>
#include <map>

#include <boost/regex.hpp>

// if 1, debug string substitutions while matching them
#define DEBUG_SUBST 0

inline std::string regexReplaceWrap(
        const std::string       &input,
        const boost::regex      &re,
        const std::string       &fmt)
{
    std::string output(boost::regex_replace(input, re, fmt));
#if DEBUG_SUBST
    if (input != output)
        std::cerr << "regex_replace: " << input << " -> " << output << "\n";
#endif
    return output;
}

class MsgFilter {
    private:
        static MsgFilter *self_;
        const boost::regex reMsg_, rePath_;

        MsgFilter():
            reMsg_("[0-9][0-9]* out of [0-9][0-9]* times"),
            rePath_("^(?:/builddir/build/BUILD/)?[^/]+/")
        {
        }

    public:
        // we use singleton in order to compile the regexes only once per run
        // NOTE: we do not care about destruction of the single instance
        static MsgFilter* inst() {
            return (self_)
                ? (self_)
                : (self_ = new MsgFilter);
        }

        std::string filterMsg(const std::string &msg) {
            return regexReplaceWrap(msg, reMsg_, "");
        }

        std::string filterPath(const std::string &path) {
            return regexReplaceWrap(path, rePath_, "");
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
    MsgFilter *filter = MsgFilter::inst();
    TDefByMsg &col = row[filter->filterPath(msg.fileName)];
    TDefList &cell = col[filter->filterMsg(msg.msg)];

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
    MsgFilter *filter = MsgFilter::inst();
    const std::string path(filter->filterPath(msg.fileName));

    // look for file name
    TDefByFile &row = iRow->second;
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol)
        return false;

    // look by msg
    TDefByMsg &col = iCol->second;
    TDefByMsg::iterator iCell = col.find(filter->filterMsg(msg.msg));
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
