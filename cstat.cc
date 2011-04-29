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

#include <errno.h>
#include <error.h>

#include <cstdlib>
#include <fstream>
#include <map>
#include <set>

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>

class AbstractEngine {
    protected:
        virtual void handleDef(const Defect &def) = 0;
        virtual void notifyFile(const std::string &) { }
        friend class AbstractFilter;

    public:
        virtual ~AbstractEngine() { }

        bool handleFile(const std::string &fileName, bool silent) {
            std::fstream fstr;
            std::istream *pStr = &fstr;

            const char *szFileName = fileName.c_str();
            const bool isFile = !!fileName.compare("-");
            if (isFile)
                fstr.open(szFileName, std::ios::in);
            else
                pStr = &std::cin;

            if (!fstr) {
                error(0, errno, "failed to open %s", szFileName);
                return false;
            }

            this->notifyFile(fileName);

            Parser parser(*pStr, fileName, silent);
            Defect def;
            while (parser.getNext(&def))
                this->handleDef(def);

            if (isFile)
                fstr.close();

            return !parser.hasError();
        }

        virtual void flush() { };
};

class DefPrinter: public AbstractEngine {
    public:
        virtual void handleDef(const Defect &def) {
            std::cout << def;
        }
};

class FilePrinter: public AbstractEngine {
    private:
        std::string                 file_;
        std::set<std::string>       fset_;

    protected:
        virtual void notifyFile(const std::string &fileName) {
            file_ = fileName;
        }

        virtual void handleDef(const Defect &) {
            fset_.insert(file_);
        }

    public:
        virtual void flush() {
            BOOST_FOREACH(const std::string &fileName, fset_)
                std::cout << fileName << "\n";
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

class AbstractFilter: public AbstractEngine {
    protected:
        AbstractEngine *slave_;
        virtual bool matchDef(const Defect &def) = 0;

        virtual void notifyFile(const std::string &fileName) {
            slave_->notifyFile(fileName);
        }

    public:
        AbstractFilter(AbstractEngine *slave):
            slave_(slave)
        {
        }

        ~AbstractFilter() {
            delete slave_;
        }

        virtual void handleDef(const Defect &def) {
            if (matchDef(def))
                slave_->handleDef(def);
        }

        virtual void flush() {
            slave_->flush();
        }
};

class MsgFilter: public AbstractFilter {
    private:
        boost::regex        re_;

    public:
        MsgFilter(
                AbstractEngine                                 *slave,
                const std::string                               reStr,
                boost::regex_constants::syntax_option_type      flags):
            AbstractFilter(slave),
            re_(reStr, flags)
        {
        }

        virtual bool matchDef(const Defect &def) {
            BOOST_FOREACH(const DefMsg &msg, def.msgs) {
                if (boost::regex_search(msg.msg, re_))
                    return true;
            }

            return false;
        }
};

class EngineFactory {
    private:
        typedef std::map<std::string, AbstractEngine* (*)(void)> TTable;
        TTable tbl_;

        static AbstractEngine* createStat()  { return new DefCounter;  }
        static AbstractEngine* createGrep()  { return new DefPrinter;  }
        static AbstractEngine* createFiles() { return new FilePrinter; }

    public:
        EngineFactory() {
            tbl_["stat"]    = createStat;
            tbl_["grep"]    = createGrep;
            tbl_["files"]   = createFiles;
        }

        AbstractEngine* create(const std::string mode) const {
            TTable::const_iterator it = tbl_.find(mode);
            if (tbl_.end() == it)
                return 0;

            return it->second();
        }
};

int main(int argc, char *argv[])
{
    using std::string;
    namespace po = boost::program_options;

    const string name(argv[0]);

    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [--mode=stat|grep|files] [--msg=PATTERN] [file1.err [...]]");

    typedef std::vector<string> TStringList;
    string mode;

    try {
        desc.add_options()
            ("help", "produce help message")
            ("ignore-case,i", "ignore case when matching regular expressions")
            ("mode", po::value<string>(&mode)->default_value("stat"),
             "stat, grep, or files")
            ("msg", po::value<string>(), "match msgs by the given regex")
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
        desc.print(std::cerr);
        return 0;
    }

    boost::regex_constants::syntax_option_type flags = 0;
    if (vm.count("ignore-case"))
        flags |= boost::regex_constants::icase;

    EngineFactory factory;
    AbstractEngine *eng = factory.create(mode);
    if (!eng) {
        std::cerr << name << ": error: unknown mode: " << mode << "\n";
        return 1;
    }

    if (vm.count("msg")) {
        const string &reStr = vm["msg"].as<string>();
        try {
            eng = new MsgFilter(eng, reStr, flags);
        }
        catch (...) {
            // NOTE: eng is already free'd by AbstractFilter::~AbstractFilter()
            std::cerr << name << ": error: invalid regex: " << reStr << "\n";
            return 1;
        }
    }

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
