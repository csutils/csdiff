/*
 * Copyright (C) 2011 - 2023 Red Hat, Inc.
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

#include "abstract-filter.hh"
#include "filter.hh"
#include "finger-print.hh"
#include "glob-expand.hh"
#include "msg-filter.hh"
#include "parser.hh"
#include "parser-common.hh"
#include "regex.hh"
#include "version.hh"
#include "writer-cov.hh"
#include "writer-json.hh"

#include <cstdlib>
#include <iomanip>
#include <map>

#include <boost/program_options.hpp>

class StatWriter: public AbstractWriter {
    public:
        /// silently drop scan properties when printing stats only
        void setScanProps(const TScanProps &) override { }
};

class FilePrinter: public StatWriter {
    private:
        std::string file_;

    protected:
        void notifyFile(const std::string &fileName) override {
            file_ = fileName;
        }

        void handleDef(const Defect &) override {
            if (file_.empty())
                return;

            std::cout << file_ << "\n";
            file_.clear();
        }
};

class GroupPrinter: public StatWriter {
    private:
        std::string file_;

    protected:
        void notifyFile(const std::string &fileName) override {
            file_ = fileName;
        }

        void handleDef(const Defect &def) override {
            if (!file_.empty()) {
                std::cout << "\n\n=== " << file_ << " ===\n";
                file_.clear();
            }

            CovWriter writer(std::cout);
            writer.handleDef(def);
        }
};

class KeyEventPrinter: public StatWriter {
    protected:
        void handleDef(const Defect &def) override {
            const DefEvent &keyEvent = def.events[def.keyEventIdx];
            std::cout << def.checker << "\t" << keyEvent.event << "\n";
        }
};

class DefCounter: public StatWriter {
    private:
        typedef std::map<std::string, int> TMap;
        TMap cnt_;

    public:
        void handleDef(const Defect &def) override {
            ++cnt_[def.checker];
        }

        void flush() override {
            for (TMap::const_reference item : cnt_) {
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

class EvtCounter: public StatWriter {
    private:
        typedef std::pair<std::string, std::string>     TKey;
        typedef std::map<TKey, int>                     TMap;
        TMap cnt_;

    public:
        void handleDef(const Defect &def) override {
            const DefEvent &evt = def.events[def.keyEventIdx];
            const TKey key(def.checker, evt.event);
            ++cnt_[key];
        }

        void flush() override {
            for (TMap::const_reference item : cnt_) {
                using namespace std;
                const TKey &key = item.first;

                // save iostream flags
                const ios_base::fmtflags oldFlags = cout.flags();
                const int oldWidth = cout.width();

                cout << fixed << setw(7) << item.second;
                cout << "\t" << left << setw(48) << key.first;

                // restore iostream flags
                cout.width(oldWidth);
                cout.flags(oldFlags);

                cout << "\t" << key.second << "\n";
            }
        }
};

class FileDefCounter: public StatWriter {
    private:
        typedef std::map<std::string, DefCounter *> TMap;
        TMap cntMap_;

    public:
        ~FileDefCounter() override {
            for (TMap::const_reference item : cntMap_)
                delete /* (DefCounter *) */ item.second;
        }

        void handleDef(const Defect &def) override {
            const std::string fName = def.events[def.keyEventIdx].fileName;
            TMap::const_iterator it = cntMap_.find(fName);

            DefCounter *defCnt = (cntMap_.end() == it)
                ? (cntMap_[fName] = new DefCounter)
                : (it->second);

            defCnt->handleDef(def);
        }

        void flush() override {
            for (TMap::const_reference item : cntMap_) {
                const std::string fName = item.first;
                std::cout << "\n\n--- " << fName << " ---\n";

                DefCounter *defCnt = item.second;
                defCnt->flush();
            }
        }
};

class MsgPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        MsgPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            for (const DefEvent &evt : def.events) {
                if (boost::regex_search(evt.msg, re_))
                    return true;
            }

            return false;
        }
};

class ToolPredicate: public IPredicate {
    private:
        const ImpliedAttrDigger digger_;
        const RE re_;

    public:
        ToolPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &defOrig) const override {
            // detect tool in case it is not explicitly specified
            Defect def = defOrig;
            digger_.inferToolFromChecker(&def, /* onlyIfMissing */ true);

            return boost::regex_search(def.tool, re_);
        }
};

class ImpLevelFilter: public AbstractFilter {
    private:
        const int minLevel_;

    public:
        ImpLevelFilter(AbstractWriter *agent, const int minLevel):
            AbstractFilter(agent),
            minLevel_(minLevel)
        {
        }

    protected:
        bool matchDef(const Defect &def) override {
            return minLevel_ <= def.imp;
        }
};

class FingerPrintFilter: public AbstractFilter {
    private:
        const std::string hashPrefix_;

    public:
        FingerPrintFilter(AbstractWriter *agent, const std::string &hashPrefix):
            AbstractFilter(agent),
            hashPrefix_(hashPrefix)
        {
        }

    protected:
        bool matchDef(const Defect &def) override {
            const FingerPrinter fp(def);
            std::string hash = fp.getHash(FPV_CSDIFF_WITH_LINE_CONTENT);
            if (hash.empty())
                // fingerprint not available for this finding
                return false;

            const size_t prefixLen = hashPrefix_.size();
            if (hash.size() < prefixLen)
                // the prefix we are looking for is longer than the hash itself
                return false;

            // make size of the hash equal to size of the prefix and compare
            hash.resize(prefixLen);
            return (hashPrefix_ == hash);
        }
};

class KeyEventPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        KeyEventPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            const DefEvent &keyEvent = def.events[def.keyEventIdx];
            return boost::regex_search(keyEvent.event, re_);
        }
};

class ErrorPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        ErrorPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            const DefEvent &evt = def.events[def.keyEventIdx];
            return boost::regex_search(evt.msg, re_);
        }
};

class PathPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        PathPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            const DefEvent &evt = def.events[def.keyEventIdx];
            return boost::regex_search(evt.fileName, re_);
        }
};

class CheckerPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        CheckerPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            return boost::regex_search(def.checker, re_);
        }
};

class AnnotPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        AnnotPredicate(const RE &re):
            re_(re)
        {
        }

        bool matchDef(const Defect &def) const override {
            return boost::regex_search(def.annotation, re_);
        }
};

class SrcAnnotPredicate: public IPredicate {
    private:
        const RE re_;

    public:
        SrcAnnotPredicate(const RE &re):
            re_(re)
        {
        }

        // FIXME: this implementation is desperately inefficient
        bool matchDef(const Defect &def) const override {
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

class WriterFactory {
    private:
        typedef std::map<std::string, AbstractWriter* (*)(void)> TTable;
        TTable tbl_;

        static EColorMode cm_;

        static AbstractWriter* createFiles()    { return new FilePrinter;   }
        static AbstractWriter* createGrouped()  { return new GroupPrinter;  }
        static AbstractWriter* createStat()     { return new DefCounter;    }
        static AbstractWriter* createEvtStat()  { return new EvtCounter;    }
        static AbstractWriter* createFileStat() { return new FileDefCounter;}

        static AbstractWriter* createGrep() {
            return new CovWriter(std::cout, cm_);
        }

        static AbstractWriter* createJson() {
            return new JsonWriter(std::cout, FF_JSON);
        }

        static AbstractWriter* createSarif() {
            return new JsonWriter(std::cout, FF_SARIF);
        }

        static AbstractWriter* createKeyEventPrinter() {
            return new KeyEventPrinter;
        }

    public:
        static void setColorMode(const EColorMode cm) {
            cm_ = cm;
        }

        WriterFactory() {
            tbl_["dig_key_events"]  = createKeyEventPrinter;
            tbl_["evtstat"]         = createEvtStat;
            tbl_["files"]           = createFiles;
            tbl_["filestat"]        = createFileStat;
            tbl_["grep"]            = createGrep;
            tbl_["grouped"]         = createGrouped;
            tbl_["json"]            = createJson;
            tbl_["sarif"]           = createSarif;
            tbl_["stat"]            = createStat;
        }

        AbstractWriter* create(const std::string &mode) const {
            TTable::const_iterator it = tbl_.find(mode);
            if (tbl_.end() == it)
                return 0;

            return it->second();
        }
};

EColorMode WriterFactory::cm_;

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
        const RE re(reStr, flags);
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

template <class TDesc, class TStream>
void printUsage(TStream &str, const TDesc &desc)
{
    desc.print(str);
}

template <class TDecorator, class TArg = std::string>
bool chainDecoratorGeneric(
        AbstractWriter            **pEng,
        const po::variables_map    &vm,
        const char                 *key)
{
    const auto it = vm.find(key);
    if (it == vm.end())
        // nothing to chain
        return true;

    const auto &val = it->second.as<TArg>();

    try {
        // chain the decorator
        *pEng = new TDecorator(*pEng, val);
        return true;
    }
    catch (const std::runtime_error &e) {
        std::cerr << name << ": error: invalid value for --"
            << key << ": " << e.what() << "\n";

        // *pEng is already deleted by destructor of GenericAbstractFilter
        *pEng = nullptr;
        return false;
    }
}

template <class TDecorator>
bool chainDecoratorIntArg(
        AbstractWriter            **pEng,
        const po::variables_map    &vm,
        const char                 *key)
{
    const auto it = vm.find(key);
    if (it == vm.end())
        // nothing to chain
        return true;

    const int val = it->second.as<int>();
    if (val < 0) {
        std::cerr << name << ": error: invalid value for --"
            << key << ": " << val << "\n";
        delete *pEng;
        *pEng = 0;
        return false;
    }

    // chain the decorator
    *pEng = new TDecorator(*pEng, val);
    return true;
}

template <typename TFlags>
bool chainFiltersCore(
        PredicateFilter                                 *pf,
        const po::variables_map                         &vm,
        const TFlags                                    flags)
{
    return appendPredIfNeeded<AnnotPredicate>     (pf, vm, flags, "annot")
        && appendPredIfNeeded<CheckerPredicate>   (pf, vm, flags, "checker")
        && appendPredIfNeeded<ErrorPredicate>     (pf, vm, flags, "error")
        && appendPredIfNeeded<KeyEventPredicate>  (pf, vm, flags, "event")
        && appendPredIfNeeded<MsgPredicate>       (pf, vm, flags, "msg")
        && appendPredIfNeeded<PathPredicate>      (pf, vm, flags, "path")
        && appendPredIfNeeded<SrcAnnotPredicate>  (pf, vm, flags, "src-annot")
        && appendPredIfNeeded<ToolPredicate>      (pf, vm, flags, "tool");
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

    if (!chainFiltersCore(pf, vm, flags)) {
        // failed to create the chain of filters
        delete pf;
        *pEng = 0;
        return false;
    }

    return chainDecoratorGeneric<FingerPrintFilter>(pEng, vm, "hash-v1")
        && chainDecoratorIntArg<ImpLevelFilter>    (pEng, vm, "imp-level");
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
            ("checker",             po::value<string>(),        "defect matches if its checker matches the given regex (each defect has assigned exactly one checker)")
            ("path",                po::value<string>(),        "defect matches if the path of its key event matches the given regex")
            ("event",               po::value<string>(),        "defect matches if its key event matches the given regex (each defect has exactly one key event, which determines its location in the code)")
            ("error",               po::value<string>(),        "defect matches if the message of its key event matches the given regex")
            ("hash-v1",             po::value<string>(),        "defect matches if its csdiff/v1 fingerprint starts with the given prefix")
            ("msg",                 po::value<string>(),        "defect matches if any of its messages matches the given regex")
            ("tool",                po::value<string>(),        "defect matches if it was detected by tool that matches the given regex")
            ("annot",               po::value<string>(),        "defect matches if its annotation matches the given regex")
            ("src-annot",           po::value<string>(),        "defect matches if an annotation in the _source_ file matches the given regex")
            ("imp-level",           po::value<int>(),           "defect matches if the importance level is greater than or equal to the given number")

            ("drop-scan-props",                                 "do not propagate scan properties")
            ("embed-context,U",     po::value<int>(),           "embed a number of lines of context from the source file for the key event")
            ("prune-events",        po::value<int>(),           "event is preserved if its verbosity level is less than or equal to the given number")
            ("warning-rate-limit",  po::value<int>(),           "stop processing a warning if the count of its occurrences exceeds the specified limit")
            ("limit-msg-len",       po::value<int>(),           "limit message length by a number provided")
            ("remove-duplicates,u",                             "remove defects that are not unique by their key event")
            ("set-imp-level",       po::value<int>(),           "set importance level on all defects to the specified value")
            ("set-scan-prop",       po::value<TStringList>(),   "NAME:VALUE pair to override the specified scan property")
            ("strip-path-prefix",   po::value<string>(),        "string prefix to strip from path (applied after all filters)")
            ("prepend-path-prefix", po::value<string>(),        "string prefix to prepend to relative paths (applied after all filters)")

            ("file-glob",                                       "expand glob patterns in the names of input files")
            ("ignore-case,i",                                   "ignore case when matching regular expressions")
            ("ignore-parser-warnings",                          "if enabled, parser warnings about the input files do not affect exit code")
            ("invert-match,v",                                  "select defects that do not match the selected criteria")
            ("invert-regex,n",                                  "invert regular expressions in all predicates")
            ("filter-file,f",       po::value<TStringList>(),   "read custom filtering rules from a file in JSON format");
        addColorOptions(&desc);
        desc.add_options()
            ("quiet,q",                                         "do not report any parsing errors")

            ("mode",                po::value<string>(&mode)
                                    ->default_value("grep"),    "grep, json, evtstat, files, filestat, grouped, sarif, stat, or dig_key_events")

            ("help",                                            "print the usage of csgrep")
            ("version",                                         "print the version of csgrep");

        po::options_description hidden("");
        hidden.add_options()
            ("input-file",          po::value<TStringList>(),   "input file");
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

    // handle --[no-]color options
    EColorMode cm;
    const char *err;
    if (readColorOptions(&cm, &err, vm))
        WriterFactory::setColorMode(cm);
    else {
        std::cerr << name << ": error: " << err << std::endl;
        return 1;
    }

    const bool silent = vm.count("quiet");

    if (vm.count("filter-file")) {
        const TStringList &filterFiles = vm["filter-file"].as<TStringList>();
        if (!MsgFilter::inst().setFilterFiles(filterFiles, silent))
            // an error message already printed out
            return 1;
    }

    // if the --file-glob flag was used, check whether a glob pattern was given
    const bool fileGlob = !!vm.count("file-glob");
    const bool hasInputFile = !!vm.count("input-file");
    if (fileGlob && !hasInputFile) {
        std::cerr << name
            << ": error: glob pattern is required with --file-glob\n";
        return 1;
    }

    // create a writer according to the selected mode
    WriterFactory factory;
    AbstractWriter *eng = factory.create(mode);
    if (!eng) {
        std::cerr << name << ": error: unknown mode: " << mode << "\n\n";
        printUsage(std::cerr, desc);
        return 1;
    }

    // insert PathStripper into the chain if requested
    if (!chainDecoratorGeneric<PathStripper>(&eng, vm, "strip-path-prefix"))
        return 1;

    // insert PathPrepender into the chain if requested
    if (!chainDecoratorGeneric<PathPrepender>(&eng, vm, "prepend-path-prefix"))
        return 1;

    // insert ScanPropSetter into the chain if requested
    if (!chainDecoratorGeneric<ScanPropSetter, TStringList>(&eng, vm,
            "set-scan-prop"))
        return 1;

    // chain all filters
    if (!chainFilters(&eng, vm))
        // an error message already printed out
        return 1;

    if (vm.count("drop-scan-props"))
        eng = new DropScanProps(eng);

    if (vm.count("remove-duplicates"))
        eng = new DuplicateFilter(eng);

    if (!chainDecoratorIntArg<EventPrunner>(&eng, vm, "prune-events")
            || !chainDecoratorIntArg<RateLimitter>(&eng, vm, "warning-rate-limit")
            || !chainDecoratorIntArg<MsgTrimmer>(&eng, vm, "limit-msg-len")
            || !chainDecoratorIntArg<ImpLevelSetter>(&eng, vm, "set-imp-level")
            || !chainDecoratorIntArg<CtxEmbedder>(&eng, vm, "embed-context"))
        // error message already printed, eng already feeed
        return 1;

    if (vm.count("ignore-parser-warnings"))
        eng->setIgnoreParserWarnings(true);

    bool hasError = false;

    // if no input file is given, read from stdin
    TStringList files = { "-" };

    if (hasInputFile)
        // use the given list of input files (or glob patterns)
        files = vm["input-file"].as<TStringList>();

    if (fileGlob)
        // expand file globs
        hasError |= !globExpand(&files);

    // process all input files one by one
    for (const string &fileName : files)
        hasError |= !eng->handleFile(fileName, silent);

    eng->flush();
    delete eng;
    return hasError;
}
