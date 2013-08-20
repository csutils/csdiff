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

#include "abstract-parser.hh"
#include "deflookup.hh"
#include "html-writer.hh"
#include "instream.hh"
#include "version.hh"

#include <boost/program_options.hpp>
#include <boost/regex.hpp>

std::string titleFromFileName(const std::string &fileName) {
    if (!fileName.compare("-"))
        return "";

    const boost::regex reNoVer("^(.*/)?[^/0-9]*$");
    if (boost::regex_match(fileName, reNoVer))
        // no version information -> bailing out
        return "";

    const boost::regex reTitle("^(?:.*/)?([^/]*)\\.(?:err|js)$");

    boost::smatch sm;
    if (!boost::regex_match(fileName, sm, reTitle))
        return "";

    return sm[/* title */ 1];
}

int main(int argc, char *argv[])
{
    using std::string;
    const char *name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] proj.js, where options are", /* line_length */ 0x80);

    typedef std::vector<string> TStringList;
    string defUrlTemplate, fnBase, plainTextUrl, spPosition;

    try {
        desc.add_options()
            ("defect-url-template", po::value(&defUrlTemplate),
             "e.g. http://localhost/index.php?proj=%d&defect=%d")
            ("diff-base", po::value(&fnBase),
             "use the given list of defects as diff base")
            ("plain-text-url", po::value(&plainTextUrl),
             "generate a link to plain-text version")
            ("scan-props-placement",
             po::value<string>(&spPosition)->default_value("top"),
             "placement of the table with scan properties: top, bottom, none")
            ("quiet,q", "do not report any parsing errors")
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

    if (!vm.count("input-file")) {
        desc.print(std::cerr);
        return 1;
    }

    const TStringList inputFiles(vm["input-file"].as<TStringList>());
    if (1 != inputFiles.size()) {
        desc.print(std::cerr);
        return 1;
    }

    const string &fnInput = inputFiles.front();
    const bool silent = vm.count("quiet");

    try {
        // initialize parser for .err
        InStream strInput(fnInput.c_str());
        Parser pInput(strInput.str(), fnInput, silent);

        DefLookup baseLookup;
        TScanProps baseProps;

        // read old defects if given
        if (!fnBase.empty()) {
            InStream strBase(fnBase.c_str());
            Parser pBase(strBase.str(), fnBase, silent);
            Defect def;
            while (pBase.getNext(&def))
                baseLookup.hashDefect(def);

            baseProps = pBase.getScanProps();
        }

        // initialize HTML writer
        const std::string titleFallback = titleFromFileName(fnInput);
        HtmlWriter writer(std::cout, titleFallback, defUrlTemplate, spPosition);
        writer.setScanProps(pInput.getScanProps());
        if (!plainTextUrl.empty())
            writer.setPlainTextUrl(plainTextUrl);

        if (!fnBase.empty()) {
            const std::string diffTitleFallback = titleFromFileName(fnBase);
            writer.setDiffBase(&baseLookup, baseProps, diffTitleFallback);
        }

        // write HTML
        writer.handleFile(pInput, fnInput);
        writer.flush();

        return pInput.hasError();
    }
    catch (const InFileException &e) {
        std::cerr << e.fileName << ": failed to open input file\n";
        return EXIT_FAILURE;
    }
    catch (const std::exception &e) {
        std::cerr << name << ": error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
}
