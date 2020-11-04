/*
 * Copyright (C) 2012 - 2013 Red Hat, Inc.
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
#include "cwe-mapper.hh"
#include "deflookup.hh"
#include "defqueue.hh"
#include "gcc-parser.hh"
#include "instream.hh"
#include "json-writer.hh"
#include "version.hh"

#include <boost/program_options.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace pt = boost::property_tree;

void parseError(
        const std::string          &msg,
        const std::string          &fName,
        const unsigned long         line = 0)
{
    std::cerr << fName;

    if (line)
        // line number available
        std::cerr << ":" << line;

    std::cerr << ": parse error: " << msg << "\n";
}

void printError(const InFileException &e)
{
    std::cerr << e.fileName << ": failed to open input file\n";
}

bool loadPropsFromIniFile(
        AbstractWriter             &writer,
        const std::string          &fName)
{
    try {
        // open the input file
        InStream input(fName.c_str());

        // parse .ini
        pt::ptree root;
        read_ini(input.str(), root);

        // read the old scan properties from writer (if any)
        TScanProps props(writer.getScanProps());

        // update scan properties from the ptree node
        pt::ptree scanNode = root.get_child("scan");
        for (const pt::ptree::value_type &item : scanNode)
            props[item.first] = item.second.data();

        // write the updated scan properties back to the writer
        writer.setScanProps(props);
        return true;
    }
    catch (const InFileException &e) {
        printError(e);
        return false;
    }
    catch (pt::file_parser_error &e) {
        parseError(e.message(), fName, e.line());
        return false;
    }
    catch (pt::ptree_error &e) {
        parseError(e.what(), fName);
        return false;
    }
}

class ImpFlagDecorator: public GenericAbstractFilter {
    public:
        ImpFlagDecorator(AbstractWriter *writer):
            GenericAbstractFilter(writer)
        {
        }

        void hashImpDefect(const Defect &);

        virtual void handleDef(const Defect &def);

    private:
        DefLookup impSet_;
};

void ImpFlagDecorator::hashImpDefect(const Defect &impDef)
{
    impSet_.hashDefect(impDef);
}

void ImpFlagDecorator::handleDef(const Defect &defOrig)
{
    if (impSet_.lookup(defOrig)) {
        // found -> set "imp" flag to 1
        Defect def = defOrig;
        def.imp = 1;
        slave_->handleDef(def);
    }
    else {
        slave_->handleDef(defOrig);
    }
}

class ParsingRulesDecorator: public GenericAbstractFilter {
    public:
        ParsingRulesDecorator(AbstractWriter *writer):
            GenericAbstractFilter(writer)
        {
        }

        virtual void handleDef(const Defect &def);

    private:
        GccPostProcessor gccPostProc_;
};

void ParsingRulesDecorator::handleDef(const Defect &defOrig)
{
    Defect def = defOrig;
    gccPostProc_.apply(&def);
    slave_->handleDef(def);
}

class OrphanWriter {
    public:
        OrphanWriter(AbstractWriter &writer):
            writer_(writer)
        {
        }

        bool operator()(const Defect &def) {
            writer_.handleDef(def);
            return /* continue */ true;
        }

    private:
        AbstractWriter &writer_;
};

bool writeMappedDefects(
        AbstractWriter             &writer,
        DefQueue                   &defQueue,
        std::istream               &input,
        const std::string          &fName)
{
    DefQueryParser qParser(input, fName);
    DefQueryParser::QRow row;
    while (qParser.getNext(row)) {
        Defect def;
        if (!defQueue.lookup(def, row.checker, row.fileName)) {
            std::cerr
                << fName << ": warning: defect lookup failed, cid = "
                << row.cid << "\n";

            DefEvent evt;
            evt.fileName    = row.fileName;
            evt.event       = "defect_lookup_failed";
            evt.msg         = "unmatched defect in ";
            evt.msg        += row.fnc;

            def = Defect();
            def.checker = row.checker;
            def.events.push_back(evt);
        }

        def.defectId = row.cid;
        def.function = row.fnc;
        writer.handleDef(def);
    }

    OrphanWriter visitor(writer);
    return defQueue.walk(visitor);
}

template <class TVal, class TVar>
inline TVal valueOf(const TVar &var)
{
    if (var.empty())
        return TVal();
    else
        return var.template as<TVal>();
}

int main(int argc, char *argv[])
{
    using std::string;
    const char *name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] proj.err [...], where options are");

    typedef std::vector<string> TStringList;

    try {
        desc.add_options()
            ("cwelist", po::value<string>(),
             "(re)assign CWE numbers to defects by the given CSV list")
            ("implist", po::value<string>(),
             "mark reports from the specified list as important")
            ("inifile", po::value<string>(),
             "load scan properties from the given INI file")
            ("mapfile", po::value<string>(),
             "load defect IDs from comma-separated mapfile")
            ("reapply-parsing-rules", "canonicalize data originally parsed "
             "by an older version of the parser")
            ("quiet,q", "do not report non-fatal errors")
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
        desc.print(std::cerr);
        return 1;
    }

    if (vm.count("help")) {
        desc.print(std::cout);
        return 0;
    }

    if (vm.count("version")) {
        std::cout << CS_VERSION << "\n";
        return 0;
    }

    const string fnCwe = valueOf<string>(vm["cwelist"]);
    const string fnImp = valueOf<string>(vm["implist"]);
    const string fnIni = valueOf<string>(vm["inifile"]);
    const string fnMap = valueOf<string>(vm["mapfile"]);
    const bool silent = vm.count("quiet");

    const po::variables_map::const_iterator it = vm.find("input-file");
    TStringList files;
    if (it != vm.end())
        files = it->second.as<TStringList>();
    else if (fnIni.empty()) {
        // nor list of defects, neither ini-file was given, this looks bogus
        desc.print(std::cerr);
        return 1;
    }

    AbstractWriter *jsonWriter = new JsonWriter(std::cout);
    ImpFlagDecorator *impDec = new ImpFlagDecorator(jsonWriter);
    CweMapDecorator *cweDec = new CweMapDecorator(impDec, silent);
    AbstractWriter *writer = cweDec;
    if (vm.count("reapply-parsing-rules"))
        writer = new ParsingRulesDecorator(writer);

    DefQueue defQueue;

    bool hasError = false;

    if (!fnCwe.empty()) {
        try {
            // load CWE mapping from the given file
            InStream strCwe(fnCwe.c_str());
            if (!cweDec->cweMap().loadCweMap(strCwe.str(), fnCwe))
                hasError = true;
        }
        catch (const InFileException &e) {
            printError(e);
            hasError = true;
        }
    }

    if (!fnImp.empty()) {
        try {
            // load list of important defects
            InStream strImp(fnImp.c_str());
            Parser pImp(strImp.str(), fnImp);
            Defect defImp;
            while (pImp.getNext(&defImp))
                impDec->hashImpDefect(defImp);
        }
        catch (const InFileException &e) {
            printError(e);
            hasError = true;
        }
    }

    const unsigned filesCnt = files.size();
    if (!filesCnt && !fnIni.empty() && !loadPropsFromIniFile(*writer, fnIni))
        hasError = true;

    for (unsigned i = 0U; i < filesCnt; ++i) {
        const string &fnErr = files[i];

        try {
            // initialize parser for .err
            InStream strErr(fnErr.c_str());
            Parser pErr(strErr.str(), fnErr, silent);

            if (!i) {
                // try to load scan properties from the first input file
                writer->setScanProps(pErr.getScanProps());

                // load .ini if available
                if (!fnIni.empty() && !loadPropsFromIniFile(*writer, fnIni))
                    hasError = true;
            }

            if (fnMap.empty()) {
                // no .map file given
                writer->handleFile(pErr, fnErr);
            }
            else {
                // load defects from .err
                Defect def;
                while (pErr.getNext(&def))
                    defQueue.hashDefect(def);
            }

            hasError |= pErr.hasError();
        }
        catch (const InFileException &e) {
            printError(e);
            hasError = true;
        }
    }

    if (!fnMap.empty()) {
        try {
            // process the given .map file
            InStream strMap(fnMap.c_str());
            if (!writeMappedDefects(*writer, defQueue, strMap.str(), fnMap))
                hasError = true;
        }
        catch (const InFileException &e) {
            printError(e);
            hasError = true;
        }
    }

    writer->flush();
    delete writer;
    return hasError;
}
