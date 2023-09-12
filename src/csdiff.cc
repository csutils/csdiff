/*
 * Copyright (C) 2011-2023 Red Hat, Inc.
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

#include "csdiff-core.hh"
#include "instream.hh"
#include "msg-filter.hh"
#include "regex.hh"
#include "version.hh"

#include <cstdlib>

#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
    using std::string;
    const char *name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] old.err new.err, where options are");

    using TStringList = std::vector<string>;
    string mode;

    try {
        desc.add_options()
            ("fixed,x", "print fixed defects (just swaps the arguments)")
            ("ignore-path,z", "ignore directory structure when matching")
            ("show-internal,i", "include internal warnings in the output")
            ("quiet,q", "do not report any parsing errors")
            ("coverity-output,c", "write the result in Coverity format")
            ("json-output,j", "write the result in JSON format")
            ("html-output", "write the result in HTML format")
            ("file-rename,s", po::value<TStringList>(),
             "account the file base-name change, [OLD,NEW] (*testing*)")
            ("filter-file,f", po::value<TStringList>(),
             "read custom filtering rules from a file in JSON format");

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

    const bool forceCov  = !!vm.count("coverity-output");
    const bool forceJson = !!vm.count("json-output");
    const bool useHtml = !!vm.count("html-output");
    if (1 < static_cast<int>(forceCov) + forceJson + useHtml) {
        std::cerr << name << ": error: options --coverity-output(-c) "
            "--json-output(-j), and --html-output are mutually exclusive\n\n";
        return 1;
    }

    EFileFormat format;
    if (forceCov)
        format = FF_COVERITY;
    else if (forceJson)
        format = FF_JSON;
    else if (useHtml)
        format = FF_HTML;
    else
        format = FF_AUTO;

    EColorMode cm;
    const char *err;
    if (!readColorOptions(&cm, &err, vm)) {
        std::cerr << name << ": error: " << err << std::endl;
        return 1;
    }

    // there are probably better solutions for this (Custom Validations)
    if (vm.count("file-rename")) {
        const TStringList &substList = vm["file-rename"].as<TStringList>();
        std::smatch sm;
        const RE reSubst("([^,]+),(.*)");
        for (const string &subst : substList) {
            if (!std::regex_match(subst, sm, reSubst)) {
                std::cerr << "bad substitution format: " << subst
                    << std::endl << "use: -s OLD,NEW" << std::endl;
                return 1;
            }
        }
        MsgFilter::inst().setFileNameSubstitution(sm[1], sm[2]);
    }

    if (!vm.count("input-file")) {
        desc.print(std::cerr);
        return 1;
    }

    const TStringList &files = vm["input-file"].as<TStringList>();
    if (2 != files.size()) {
        desc.print(std::cerr);
        return 1;
    }

    if (vm.count("ignore-path"))
        MsgFilter::inst().setIgnorePath(true);

    const bool swap = vm.count("fixed");
    const string &fnOld = files[swap];
    const string &fnNew = files[!swap];

    const bool showInternal = vm.count("show-internal");
    const bool silent       = vm.count("quiet");

    if (vm.count("filter-file")) {
        const TStringList &filterFiles = vm["filter-file"].as<TStringList>();
        if (!MsgFilter::inst().setFilterFiles(filterFiles, silent))
            // an error message already printed out
            return 1;
    }

    try {
        // open streams
        InStream strOld(fnOld, silent);
        InStream strNew(fnNew, silent);

        // run the core
        return diffScans(std::cout, strOld, strNew, showInternal, format, cm);
    }
    catch (const InFileException &e) {
        std::cerr << e.fileName << ": failed to open input file\n";
        return EXIT_FAILURE;
    }
}
