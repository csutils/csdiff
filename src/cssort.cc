/*
 * Copyright (C) 2012-2022 Red Hat, Inc.
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

#include "abstract-writer.hh"
#include "regex.hh"
#include "version.hh"

#include <boost/program_options.hpp>

class SortFactory {
    public:
        AbstractWriter* create(const std::string &key, EColorMode cm);
};

template <class TItem>
class GenericSort: public AbstractWriter {
    private:
        typedef std::vector<TItem> TCont;

        TCont           cont_;
        TScanProps      scanProps_;
        EColorMode      cm_;

    public:
        GenericSort(const EColorMode cm):
            cm_(cm)
        {
        }

        void flush() override {
            // sort the container
            std::sort(cont_.begin(), cont_.end());

            // use the same output format is the input format
            TWriterPtr writer =
                createWriter(std::cout, this->inputFormat(), cm_, scanProps_);

            // write the data
            for (const Defect &def : cont_)
                writer->handleDef(def);

            // flush data
            writer->flush();
        }

        const TScanProps& getScanProps() const override {
            return scanProps_;
        }

        void setScanProps(const TScanProps &scanProps) override {
            scanProps_ = scanProps;
        }

    protected:
        void handleDef(const Defect &def) override {
            cont_.push_back(static_cast<const TItem &>(def));
        }
};

inline bool cmpFileNames(const Defect &a, const Defect &b)
{
    const TEvtList &ea = a.events;
    const TEvtList &eb = b.events;

    // first compare the key events
    bool result;
    if (cmpEvents(&result, ea[a.keyEventIdx], eb[b.keyEventIdx]))
        return result;

    // the key events are incomparable, compare all events
    for (unsigned idx = 0;; ++idx) {
        if (eb.size() <= idx)
            // this includes the case where the events are equal
            return false;

        if (ea.size() <= idx)
            return true;

        if (cmpEvents(&result, ea[idx], eb[idx]))
            return result;
    }
}

struct DefByChecker: public Defect { };
bool operator<(const DefByChecker &a, const DefByChecker &b)
{
    // compare checker names
    RETURN_IF_COMPARED(a, b, checker);

    // resolve key events
    const DefEvent &ea = a.events[a.keyEventIdx];
    const DefEvent &eb = b.events[b.keyEventIdx];

    if ("SHELLCHECK_WARNING" == a.checker /* == b.checker */) {
        // sort ShellCheck warnings by the [SC1234] suffixes
        const RE reCode("^.* \\[SC([0-9]+)\\]$");
        std::string aCode, bCode;
        boost::smatch sm;
        if (boost::regex_match(ea.msg, sm, reCode))
            aCode = sm[1];
        if (boost::regex_match(eb.msg, sm, reCode))
            bCode = sm[1];
        if (aCode < bCode)
            return true;
        if (bCode < aCode)
            return false;
    }

    // compare name of the key events
    RETURN_IF_COMPARED(ea, eb, event);

    return cmpFileNames(a, b);
}

struct DefByPath: public Defect { };
bool operator<(const DefByPath &a, const DefByPath &b)
{
    return cmpFileNames(a, b);
}

AbstractWriter* SortFactory::create(const std::string &key, const EColorMode cm)
{
    if (!key.compare("checker"))
        return new GenericSort<DefByChecker>(cm);

    if (!key.compare("path"))
        return new GenericSort<DefByPath>(cm);

    // no comparator matched
    return 0;
}

static std::string name;

namespace po = boost::program_options;

template <class TDesc, class TStream>
void printUsage(TStream &str, const TDesc &desc)
{
    desc.print(str);
    // TODO: output some additional documentation
}

int main(int argc, char *argv[])
{
    using std::string;

    ::name = argv[0];

    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] [file1.err [...]], where options are");

    typedef std::vector<string> TStringList;
    string key;

    try {
        desc.add_options()
            ("key", po::value<string>(&key)->default_value("path"),
             "checker, path")
            ("quiet,q", "do not report any parsing errors");

        addColorOptions(&desc);

        desc.add_options()
            ("help", "produce help message")
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

    EColorMode cm;
    const char *err;
    if (!readColorOptions(&cm, &err, vm)) {
        std::cerr << name << ": error: " << err << std::endl;
        return 1;
    }

    SortFactory factory;
    AbstractWriter *eng = factory.create(key, cm);
    if (!eng) {
        std::cerr << name << ": error: unknown key: " << key << "\n\n";
        printUsage(std::cerr, desc);
        return 1;
    }

    const bool silent = vm.count("quiet");
    bool hasError = false;

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
