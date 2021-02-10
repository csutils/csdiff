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
#include "csfilter.hh"
#include "cswriter.hh"
#include "json-writer.hh"
#include "regex.hh"
#include "version.hh"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <map>

#include <boost/program_options.hpp>

class StatWriter: public AbstractWriter {
    public:
        /// silently drop scan properties when printing stats only
        virtual void setScanProps(const TScanProps &) { }
};

class FilePrinter: public StatWriter {
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

class GroupPrinter: public StatWriter {
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

class KeyEventPrinter: public StatWriter {
    protected:
        virtual void handleDef(const Defect &def) {
            const DefEvent &keyEvent = def.events[def.keyEventIdx];
            std::cout << def.checker << "\t" << keyEvent.event << "\n";
        }
};

class DefCounter: public StatWriter {
    private:
        typedef std::map<std::string, int> TMap;
        TMap cnt_;

    public:
        virtual void handleDef(const Defect &def) {
            ++cnt_[def.checker];
        }

        virtual void flush() {
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
        virtual void handleDef(const Defect &def) {
            const DefEvent &evt = def.events[def.keyEventIdx];
            const TKey key(def.checker, evt.event);
            ++cnt_[key];
        }

        virtual void flush() {
            for (TMap::const_reference item : cnt_) {
                using namespace std;
                const ios_base::fmtflags oldFlags = cout.flags();
                const int oldWidth = cout.width();
                cout << fixed << setw(7) << item.second;
                cout.width(oldWidth);
                cout.flags(oldFlags);

                const TKey &key = item.first;
                cout << "\t" << key.first
                    << "\t" << key.second
                    << "\n";
            }
        }
};

class FileDefCounter: public StatWriter {
    private:
        typedef std::map<std::string, DefCounter *> TMap;
        TMap cntMap_;

    public:
        virtual ~FileDefCounter() {
            for (TMap::const_reference item : cntMap_)
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

        virtual bool matchDef(const Defect &def) const {
            for (const DefEvent &evt : def.events) {
                if (boost::regex_search(evt.msg, re_))
                    return true;
            }

            return false;
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

        virtual bool matchDef(const Defect &def) const {
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

        virtual bool matchDef(const Defect &def) const {
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

        virtual bool matchDef(const Defect &def) const {
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

        virtual bool matchDef(const Defect &def) const {
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

        virtual bool matchDef(const Defect &def) const {
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

class PathStripper: public GenericAbstractFilter {
    public:
        PathStripper(AbstractWriter *agent, const std::string &prefix):
            GenericAbstractFilter(agent),
            prefStr_(prefix),
            prefSize_(prefix.size())
        {
        }

        virtual void handleDef(const Defect &defOrig) {
            Defect def(defOrig);

            // iterate through all events
            for (DefEvent &evt : def.events) {
                std::string &path = evt.fileName;
                if (path.size() < prefSize_)
                    continue;

                const std::string str(path, /* pos */ 0U, prefSize_);
                if (str != prefStr_)
                    continue;

                // strip path prefix in this event
                path.erase(/* pos */ 0U, prefSize_);
            }

            agent_->handleDef(def);
        }

    private:
        const std::string           prefStr_;
        const size_t                prefSize_;
};

class DuplicateFilter: public AbstractFilter {
    public:
        DuplicateFilter(AbstractWriter *agent):
            AbstractFilter(agent)
        {
        }

    protected:
        virtual bool matchDef(const Defect &def) {
            DefEvent evt = def.events[def.keyEventIdx];

            // abstract out differences we do not deem important
            evt.msg = MsgFilter::inst()->filterMsg(evt.msg, def.checker);

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
            return new JsonWriter(std::cout);
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

template <typename TFlags>
bool chainFiltersCore(
        PredicateFilter                                 *pf,
        const po::variables_map                         &vm,
        const TFlags                                    flags)
{
    return appendPredIfNeeded<CheckerPredicate>   (pf, vm, flags, "checker")
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
void printUsage(TStream &str, const TDesc &desc)
{
    desc.print(str);
}

template <class TDecorator>
bool chainDecorator(
        AbstractWriter            **pEng,
        const po::variables_map    &vm,
        const char                 *key)
{
    if (!vm.count(key))
        // nothing to chain
        return true;

    const int val = vm[key].as<int>();
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
            ("msg",                 po::value<string>(),        "defect matches if any of its messages matches the given regex")
            ("annot",               po::value<string>(),        "defect matches if its annotation matches the given regex")
            ("src-annot",           po::value<string>(),        "defect matches if an annotation in the _source_ file matches the given regex")

            ("embed-context,U",     po::value<int>(),           "embed a number of lines of context from the source file for the key event")
            ("prune-events",        po::value<int>(),           "event is preserved if its verbosity level is below the given number")
            ("remove-duplicates,u",                             "remove defects that are not unique by their key event")
            ("strip-path-prefix",   po::value<string>(),        "string prefix to strip from path (applied after all filters)")

            ("ignore-case,i",                                   "ignore case when matching regular expressions")
            ("invert-match,v",                                  "select defects that do not match the selected criteria")
            ("invert-regex,n",                                  "invert regular expressions in all predicates");

        addColorOptions(&desc);
        desc.add_options()
            ("quiet,q",                                         "do not report any parsing errors")

            ("mode",                po::value<string>(&mode)
                                    ->default_value("grep"),    "grep, json, evtstat, files, filestat, grouped, stat, or dig_key_events")

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

    // create a writer according to the selected mode
    WriterFactory factory;
    AbstractWriter *eng = factory.create(mode);
    if (!eng) {
        std::cerr << name << ": error: unknown mode: " << mode << "\n\n";
        printUsage(std::cerr, desc);
        return 1;
    }

    const po::variables_map::const_iterator it = vm.find("strip-path-prefix");
    if (it != vm.end())
        // insert PathStripper into the chain
        eng = new PathStripper(eng, it->second.as<std::string>());

    // chain all filters
    if (!chainFilters(&eng, vm))
        // an error message already printed out
        return 1;

    if (vm.count("remove-duplicates"))
        eng = new DuplicateFilter(eng);

    const bool silent = vm.count("quiet");
    bool hasError = false;

    if (!chainDecorator<EventPrunner>(&eng, vm, "prune-events")
            || !chainDecorator<CtxEmbedder>(&eng, vm, "embed-context"))
        // error message already printed, eng already feeed
        return 1;

    if (!vm.count("input-file")) {
        hasError = !eng->handleFile("-", silent);
    }
    else {
        const TStringList &files = vm["input-file"].as<TStringList>();
        for (const string &fileName : files) {
            if (!eng->handleFile(fileName, silent))
                hasError = true;
        }
    }

    eng->flush();
    delete eng;
    return hasError;
}
