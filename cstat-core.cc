/*
 * Copyright (C) 2011 Red Hat, Inc.
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
#include "cstat-core.hh"
#include "abstract-filter.hh"
#include "json-writer.hh"

#include <cstdlib>
#include <map>

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>

class DefPrinter: public AbstractEngine {
    public:
        virtual void handleDef(const Defect &def) {
            std::cout << def;
        }
};

class FilePrinter: public AbstractEngine {
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

class GroupPrinter: public AbstractEngine {
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

            std::cout << def;
        }
};

class DefCounter: public AbstractEngine {
    private:
        typedef std::map<std::string, int> TMap;
        TMap cnt_;

    public:
        virtual void handleDef(const Defect &def) {
            ++cnt_[def.defClass];
        }

        virtual void flush() {
            BOOST_FOREACH(TMap::const_reference item, cnt_) {
                std::cout << item.second << "\t" << item.first << "\n";
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

class ErrorPredicate: public IPredicate {
    private:
        boost::regex re_;

    public:
        ErrorPredicate(const boost::regex &re):
            re_(re)
        {
        }

        virtual bool matchDef(const Defect &def) const {
            const DefEvent &evt = def.events.front();
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
            const DefEvent &evt = def.events.front();
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
            return boost::regex_search(def.defClass, re_);
        }
};

class EngineFactory {
    private:
        typedef std::map<std::string, AbstractEngine* (*)(void)> TTable;
        TTable tbl_;

        static AbstractEngine* createFiles()    { return new FilePrinter;   }
        static AbstractEngine* createGrep()     { return new DefPrinter;    }
        static AbstractEngine* createGrouped()  { return new GroupPrinter;  }
        static AbstractEngine* createStat()     { return new DefCounter;    }
        static AbstractEngine* createJson()     { return new JsonWriter;    }

    public:
        EngineFactory() {
            tbl_["files"]   = createFiles;
            tbl_["grep"]    = createGrep;
            tbl_["grouped"] = createGrouped;
            tbl_["stat"]    = createStat;
            tbl_["json"]    = createJson;
        }

        AbstractEngine* create(const std::string mode) const {
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
        AbstractEngine                                  **pEng,
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

    if (!pred) {
        delete *pEng;
        *pEng = 0;
        return false;
    }

    // append a predicate
    PredicateFilter *pf = dynamic_cast<PredicateFilter *>(*pEng);
    pf->append(pred);

    return true;
}

bool chainFilters(
        AbstractEngine                                  **pEng,
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
        pf->setInvertEachMatch();

    return appendPredIfNeeded<DefClassPredicate>  (pEng, vm, flags, "checker")
        && appendPredIfNeeded<ErrorPredicate>     (pEng, vm, flags, "error")
        && appendPredIfNeeded<MsgPredicate>       (pEng, vm, flags, "msg")
        && appendPredIfNeeded<PathPredicate>      (pEng, vm, flags, "path");
}

int cStatCore(int argc, char *argv[], const char *defMode)
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
            ("checker", po::value<string>(),
             "match checkers by the given regex")
            ("error", po::value<string>(), "match errors by the given regex")
            ("help", "produce help message")
            ("ignore-case,i", "ignore case when matching regular expressions")
            ("invert-match,v", "select defects that do not match the regex")
            ("mode", po::value<string>(&mode)->default_value(defMode),
             "stat, grep, files, grouped, or json")
            ("msg", po::value<string>(), "match messages by the given regex")
            ("path", po::value<string>(),
             "match source path by the given regex")
            ("quiet,q", "do not report any parsing errors");

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
        desc.print(std::cerr);
        return 1;
    }

    if (vm.count("help")) {
        desc.print(std::cout);
        return 0;
    }

    EngineFactory factory;
    AbstractEngine *eng = factory.create(mode);
    if (!eng) {
        std::cerr << name << ": error: unknown mode: " << mode << "\n\n";
        desc.print(std::cerr);
        return 1;
    }

    // chain all filters
    if (!chainFilters(&eng, vm))
        // an error message already printed out
        return 1;

    const bool silent = vm.count("quiet");
    bool hasError = false;

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
