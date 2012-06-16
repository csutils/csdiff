/*
 * Copyright (C) 2012 Red Hat, Inc.
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

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

class SortFactory {
    public:
        AbstractWriter* create(const std::string &key);
};

template <class TItem>
class GenericSort: public AbstractWriter {
    private:
        typedef std::vector<TItem> TCont;

        TCont           cont_;
        TScanProps      scanProps_;

    public:
        virtual void flush() {
            // sort the container
            std::sort(cont_.begin(), cont_.end());

            // use the same output format is the input format
            AbstractWriter *writer = createWriter(this->inputFormat());
            writer->setScanProps(scanProps_);

            // write the data
            BOOST_FOREACH(const Defect &def, cont_)
                writer->handleDef(def);

            // flush data and destroy writer
            writer->flush();
            delete writer;
        }

        virtual const TScanProps& getScanProps() const {
            return scanProps_;
        }

        virtual void setScanProps(const TScanProps &scanProps) {
            scanProps_ = scanProps;
        }

    protected:
        virtual void handleDef(const Defect &def) {
            cont_.push_back(static_cast<const TItem &>(def));
        }
};

#define RETURN_CMP_RESULT(result) do {  \
    *pResult = (result);                \
    return true;                        \
} while (0)

inline bool cmpEvents(bool *pResult, const DefEvent &ea, const DefEvent &eb)
{
    // compare path
    if (ea.fileName < eb.fileName)
        RETURN_CMP_RESULT(true);
    if (eb.fileName < ea.fileName)
        RETURN_CMP_RESULT(false);

    // compare line numbers
    if (ea.line < eb.line)
        RETURN_CMP_RESULT(true);
    if (eb.line < ea.line)
        RETURN_CMP_RESULT(false);

    // compare column numbers
    if (ea.column < eb.column)
        RETURN_CMP_RESULT(true);
    if (eb.column < ea.column)
        RETURN_CMP_RESULT(false);

    // compare events
    if (ea.event < eb.event)
        RETURN_CMP_RESULT(true);
    if (eb.event < ea.event)
        RETURN_CMP_RESULT(false);

    // compare messages
    if (ea.msg < eb.msg)
        RETURN_CMP_RESULT(true);
    if (eb.msg < ea.msg)
        RETURN_CMP_RESULT(false);

    // incomparable events
    return false;
}

inline bool cmpFileNames(const Defect &a, const Defect &b) {
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
bool operator<(const DefByChecker &a, const DefByChecker &b) {
    const std::string &ca = a.checker;
    const std::string &cb = b.checker;

    if (ca < cb)
        return true;
    if (cb < ca)
        return false;

    return cmpFileNames(a, b);
}

struct DefByPath: public Defect { };
bool operator<(const DefByPath &a, const DefByPath &b) {
    return cmpFileNames(a, b);
}

AbstractWriter* SortFactory::create(const std::string &key) {
    if (!key.compare("checker"))
        return new GenericSort<DefByChecker>;

    if (!key.compare("path"))
        return new GenericSort<DefByPath>;

    // no comparator matched
    return 0;
}

static std::string name;

namespace po = boost::program_options;

template <class TDesc, class TStream>
void printUsage(TStream &str, const TDesc &desc) {
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
            ("help", "produce help message")
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
        printUsage(std::cerr, desc);
        return 1;
    }

    if (vm.count("help")) {
        printUsage(std::cout, desc);
        return 0;
    }

    SortFactory factory;
    AbstractWriter *eng = factory.create(key);
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
        BOOST_FOREACH(const string &fileName, files) {
            if (!eng->handleFile(fileName, silent))
                hasError = true;
        }
    }

    eng->flush();
    delete eng;
    return hasError;
}
