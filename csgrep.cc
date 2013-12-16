/*
 * Copyright (C) 2011 - 2013 Red Hat, Inc.
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

#include "abstract-parser.hh"
#include "abstract-filter.hh"
#include "cswriter.hh"
#include "json-writer.hh"
#include "version.hh"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <map>

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>

class FilePrinter: public AbstractWriter {
    private:
        std::string file_;

    protected:
        virtual void notifyFile(const std::string &fileName) {
            file_ = fileName;
        }

        virtual void handleDef(const Defect &) {
            if (file_.empty())
                return;

            std::cout << file_ << "\n";
            file_.clear();
        }
};

class GroupPrinter: public AbstractWriter {
    private:
        std::string file_;

    protected:
        virtual void notifyFile(const std::string &fileName) {
            file_ = fileName;
        }

        virtual void handleDef(const Defect &def) {
            if (!file_.empty()) {
                std::cout << "\n\n=== " << file_ << " ===\n";
                file_.clear();
            }

            CovWriter writer(std::cout);
            writer.handleDef(def);
        }
};

class KeyEventPrinter: public AbstractWriter {
    protected:
        virtual void handleDef(const Defect &def) {
            const DefEvent &keyEvent = def.events[def.keyEventIdx];
            std::cout << def.checker << "\t" << keyEvent.event << "\n";
        }
};

class DefCounter: public AbstractWriter {
    private:
        typedef std::map<std::string, int> TMap;
        TMap cnt_;

    public:
        virtual void handleDef(const Defect &def) {
            ++cnt_[def.checker];
        }

        virtual void flush() {
            BOOST_FOREACH(TMap::const_reference item, cnt_) {
                using namespace std;
                const ios_base::fmtflags oldFlags = cout.flags();
                const int oldWidth = cout.width();
                cout << fixed << setw(7) << item.second;
                cout.width(oldWidth);
                cout.flags(oldFlags);
                cout << "\t" << item.first << "\n";
            }
        }
};

class FileDefCounter: public AbstractWriter {
    private:
        typedef std::map<std::string, DefCounter *> TMap;
        TMap cntMap_;

    public:
        virtual ~FileDefCounter() {
            BOOST_FOREACH(TMap::const_reference item, cntMap_)
                delete /* (DefCounter *) */ item.second;
        }

        virtual void handleDef(const Defect &def) {
            const std::string fName = def.events[def.keyEventIdx].fileName;
            TMap::const_iterator it = cntMap_.find(fName);

            DefCounter *defCnt = (cntMap_.end() == it)
                ? (cntMap_[fName] = new DefCounter)
                : (it->second);

            defCnt->handleDef(def);
        }

        virtual void flush() {
            BOOST_FOREACH(TMap::const_reference item, cntMap_) {
                const std::string fName = item.first;
                std::cout << "\n\n--- " << fName << " ---\n";

                DefCounter *defCnt = item.second;
                defCnt->flush();
            }
        }
};

class MsgPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        MsgPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            BOOST_FOREACH(const DefEvent &evt, def.events) {
                if (boost::regex_search(evt.msg, re_))
                    return true;
            }

            return false;
        }
};

class KeyEventPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        KeyEventPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            const DefEvent &keyEvent = def.events[def.keyEventIdx];
            return boost::regex_search(keyEvent.event, re_);
        }
};

class ErrorPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        ErrorPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            const DefEvent &evt = def.events[def.keyEventIdx];
            return boost::regex_search(evt.msg, re_);
        }
};

class PathPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        PathPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            const DefEvent &evt = def.events[def.keyEventIdx];
            return boost::regex_search(evt.fileName, re_);
        }
};

class DefClassPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        DefClassPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            return boost::regex_search(def.checker, re_);
        }
};

class AnnotPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        AnnotPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            return boost::regex_search(def.annotation, re_);
        }
};

class SrcAnnotPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        SrcAnnotPredicate(const boost::regex &re):
            re_(re)
        {
        }

        // FIXME: this implementation is desperately inefficient
        virtual bool matchDef(const Defect &def) const {
            const DefEvent &evt = def.events[def.keyEventIdx];
            const std::string &fname = evt.fileName;
            std::fstream fstr(fname.c_str(), std::ios::in);
            if (!fstr) {
                std::cerr << "failed to open source file: " << fname << "\n";
                return false;
            }

            bool matched = false;

            const int lineno = evt.line;
            std::string line;
            for (int i = 1; i <= lineno; i++) {
                if (std::getline(fstr, line))
                    continue;

                std::cerr << "failed to seek line "
                    << lineno << " in the source file: "
                    << fname << "\n";

                goto fail;
            }

            matched = boost::regex_search(line, re_);
fail:
            fstr.close();
            return matched;
        }
};

class DuplicateFilter: public AbstractFilter {
    public:
        DuplicateFilter(AbstractWriter *slave):
            AbstractFilter(slave)
        {
        }

    protected:
        virtual bool matchDef(const Defect &def) {
            const DefEvent &evt = def.events[def.keyEventIdx];
            return lookup_.insert(evt)./* inserted */second;
        }

    private:
        typedef std::set<DefEvent> TLookup;
        TLookup lookup_;
};

class WriterFactory {
    private:
        typedef std::map<std::string, AbstractWriter* (*)(void)> TTable;
        TTable tbl_;

        static AbstractWriter* createFiles()    { return new FilePrinter;   }
        static AbstractWriter* createGrouped()  { return new GroupPrinter;  }
        static AbstractWriter* createStat()     { return new DefCounter;    }
        static AbstractWriter* createFileStat() { return new FileDefCounter;}

        static AbstractWriter* createGrep() {
            return new CovWriter(std::cout);
        }

        static AbstractWriter* createJson() {
            return new JsonWriter(std::cout);
        }

        static AbstractWriter* createKeyEventPrinter() {
            return new KeyEventPrinter;
        }

    public:
        WriterFactory() {
            tbl_["dig_key_events"]  = createKeyEventPrinter;
            tbl_["files"]           = createFiles;
            tbl_["filestat"]        = createFileStat;
            tbl_["grep"]            = createGrep;
            tbl_["grouped"]         = createGrouped;
            tbl_["json"]            = createJson;
            tbl_["stat"]            = createStat;
        }

        AbstractWriter* create(const std::string &mode) const {
            TTable::const_iterator it = tbl_.find(mode);
            if (tbl_.end() == it)
                return 0;

            return it->second();
        }
};

static std::string name;

namespace po = boost::program_options;

template <class TPred>
bool appendPredIfNeeded(
        PredicateFilter                                 *pf,
        const po::variables_map                         &vm,
        boost::regex_constants::syntax_option_type      flags,
        const char                                      *key)
{
    if (!vm.count(key))
        return true;

    TPred *pred = 0;
    const std::string &reStr = vm[key].as<std::string>();
    try {
        boost::regex re(reStr, flags);
        pred = new TPred(re);
    }
    catch (...) {
        std::cerr << ::name << ": error: failed to compile regex: --"
            << key << " '" << reStr << "'\n";
    }

    if (!pred)
        return false;

    // append a predicate
    pf->append(pred);
    return true;
}

template <typename TFlags>
bool chainFiltersCore(
        PredicateFilter                                 *pf,
        const po::variables_map                         &vm,
        const TFlags                                    flags)
{
    return appendPredIfNeeded<DefClassPredicate>  (pf, vm, flags, "checker")
        && appendPredIfNeeded<SrcAnnotPredicate>  (pf, vm, flags, "src-annot")
        && appendPredIfNeeded<AnnotPredicate>     (pf, vm, flags, "annot")
        && appendPredIfNeeded<ErrorPredicate>     (pf, vm, flags, "error")
        && appendPredIfNeeded<KeyEventPredicate>  (pf, vm, flags, "event")
        && appendPredIfNeeded<MsgPredicate>       (pf, vm, flags, "msg")
        && appendPredIfNeeded<PathPredicate>      (pf, vm, flags, "path");
}

bool chainFilters(
        AbstractWriter                                  **pEng,
        const po::variables_map                         &vm)
{
    // insert a filter predicate into the chain
    PredicateFilter *pf = new PredicateFilter(*pEng);
    *pEng = pf;

    // common matching flags
    boost::regex_constants::syntax_option_type flags = 0;
    if (vm.count("ignore-case"))
        flags |= boost::regex_constants::icase;

    if (vm.count("invert-match"))
        pf->setInvertMatch();

    if (vm.count("invert-regex"))
        pf->setInvertEachMatch();

    if (chainFiltersCore(pf, vm, flags))
        return true;

    // failed to create the chain of filters
    delete pf;
    *pEng = 0;
    return false;
}

template <class TDesc, class TStream>
void printUsage(TStream &str, const TDesc &desc) {
    desc.print(str);
    str << "\n\n\
DESCRIPTION OF AVAILABLE MODES\n\
------------------------------\n\
\n\
dig_key_events - for each defect, print only the checker and key event\n\
\n\
files - print only names of error files that contain the matched defects\n\
\n\
filestat - print statistics of matched defects per individual source files\n\
\n\
grep - print matched defects using the same format as expected on the input\n\
\n\
grouped - print matched defects, grouped by error files they originate from\n\
\n\
json - print matched defects in a JSON format\n\
\n\
stat - print overall statistics of the matched defects in given error files\n\n";
}

int main(int argc, char *argv[])
{
    using std::string;

    ::name = argv[0];

    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] [file1.err [...]], where options are");

    typedef std::vector<string> TStringList;
    string mode;

    try {
        desc.add_options()
            ("annot", po::value<string>(),
             "match annotations by the given regex")
            ("checker", po::value<string>(),
             "match checkers by the given regex")
            ("error", po::value<string>(), "match errors by the given regex")
            ("event", po::value<string>(), "match key event by the given regex")
            ("help", "produce help message")
            ("ignore-case,i", "ignore case when matching regular expressions")
            ("invert-match,v", "select defects that do not match the regex")
            ("invert-regex,n", "invert all given regexes before matching them")
            ("mode", po::value<string>(&mode)->default_value("grep"),
             "dig_key_events, files, filestat, grep, grouped, json, or stat")
            ("msg", po::value<string>(), "match messages by the given regex")
            ("path", po::value<string>(),
             "match source path by the given regex")
            ("prune-events", po::value<int>(),
             "prune events with greater or equal verbosity level")
            ("quiet,q", "do not report any parsing errors")
            ("remove-duplicates,u", "remove defects with repeated key events")
            ("src-annot", po::value<string>(),
             "match annotations in the _source_ file by the given regex")
            ("version", "print version");

        po::options_description hidden("");
        hidden.add_options()
            ("input-file", po::value<TStringList>(), "input file");
        po::positional_options_description p;
        p.add("input-file", -1);

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        po::options_description opts;
        opts.add(desc).add(hidden);
        po::store(po::command_line_parser(argc, argv).
                options(opts).positional(p).run(), vm);
        po::notify(vm);
    }
    catch (po::error &e) {
        std::cerr << name << ": error: " << e.what() << "\n\n";
        printUsage(std::cerr, desc);
        return 1;
    }

    if (vm.count("help")) {
        printUsage(std::cout, desc);
        return 0;
    }

    if (vm.count("version")) {
        std::cout << CS_VERSION << "\n";
        return 0;
    }

    WriterFactory factory;
    AbstractWriter *eng = factory.create(mode);
    if (!eng) {
        std::cerr << name << ": error: unknown mode: " << mode << "\n\n";
        printUsage(std::cerr, desc);
        return 1;
    }

    // chain all filters
    if (!chainFilters(&eng, vm))
        // an error message already printed out
        return 1;

    if (vm.count("remove-duplicates"))
        eng = new DuplicateFilter(eng);

    const bool silent = vm.count("quiet");
    bool hasError = false;

    if (vm.count("prune-events")) {
        const int thr = vm["prune-events"].as<int>();
        if (thr < 0) {
            std::cerr << name << ": error: invalid value for --prune-events: "
                << thr << "\n";
            delete eng;
            return 1;
        }

        // chain event prunner
        eng = new EventPrunner(eng, thr);
    }

    if (!vm.count("input-file")) {
        hasError = !eng->handleFile("-", silent);
    }
    else {
        const TStringList &files = vm["input-file"].as<TStringList>();
        BOOST_FOREACH(const string &fileName, files) {
            if (!eng->handleFile(fileName, silent))
                hasError = true;
        }
    }

    eng->flush();
    delete eng;
    return hasError;
}
