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

#include "abstract-parser.hh"
#include "csfilter.hh"
#include "cswriter.hh"
#include "deflookup.hh"
#include "instream.hh"
#include "json-writer.hh"

#include <cstdlib>

#include <boost/foreach.hpp>
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/regex.hpp>

// FIXME: some keys should be merge more intelligently if they already exist
// TODO: define a nesting limit for keys like diffbase-diffbase-diffbase-...
void mergeScanProps(TScanProps &props, const TScanProps &oldProps)
{
    BOOST_FOREACH(TScanProps::const_reference item, oldProps) {
        const std::string &oldKey = item.first;
        const std::string &oldVal = item.second;
        std::string key("diffbase-");
        key += oldKey;
        props[key] = oldVal;
    }
}

int main(int argc, char *argv[])
{
    using std::string;
    const char *name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(string("Usage: ") + name
            + " [options] old.err new.err, where options are");

    typedef std::vector<string> TStringList;
    string mode;

    try {
        desc.add_options()
            ("coverity-output,c", "write the result in Coverity format")
            ("fixed,x", "print fixed defects (just swaps the arguments)")
            ("ignore-path,z", "ignore directory structure when matching")
            ("json-output,j", "write the result in JSON format")
            ("quiet,q", "do not report any parsing errors")
            ("file-rename,s", po::value<TStringList>(),
             "account the file base-name change, [OLD,NEW] (*testing*)")
            ("help", "produce help message");

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

    const bool forceCov  = !!vm.count("coverity-output");
    const bool forceJson = !!vm.count("json-output");
    if (forceCov && forceJson) {
        std::cerr << name << ": error: options --coverity-output(-c) "
            "and --json-output(-j) are mutually exclusive\n\n";
        return 1;
    }

    // there are probably better solutions for this (Custom Validations)
    if (vm.count("file-rename")) {
        const TStringList &substList = vm["file-rename"].as<TStringList>();
        boost::smatch sm;
        const boost::regex reSubst("([^,]+),(.*)");
        BOOST_FOREACH(const string &subst, substList) {
            if (!boost::regex_match(subst, sm, reSubst)) {
                std::cerr << "bad substutution format: " << subst
                    << std::endl << "use: -s OLD,NEW" << std::endl;
                return 1;
            }
        }
        MsgFilter::inst()->setFileNameSubstitution(sm[1], sm[2]);
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
        MsgFilter::inst()->setIgnorePath(true);

    const bool swap = vm.count("fixed");
    const string &fnOld = files[swap];
    const string &fnNew = files[!swap];

    const bool silent = vm.count("quiet");

    try {
        // open streams
        InStream strOld(fnOld.c_str());
        InStream strNew(fnNew.c_str());

        // create Parsers
        Parser pOld(strOld.str(), fnOld, silent);
        Parser pNew(strNew.str(), fnNew, silent);

        // decide which format use for the output
        const bool json = forceJson
            || (!forceCov && pNew.isJson());

        // create the appropriate writer
        boost::shared_ptr<AbstractWriter> writer;
        if (json)
            writer.reset(new JsonWriter);
        else
            writer.reset(new CovWriter);

        // propagate scan properties if available
        TScanProps props = pNew.getScanProps();
        mergeScanProps(props, pOld.getScanProps());
        writer->setScanProps(props);

        // read old
        DefLookup stor;
        Defect def;
        while (pOld.getNext(&def))
            stor.hashDefect(def);

        // read new
        while (pNew.getNext(&def)) {
            if (stor.lookup(def))
                continue;

            // a newly added defect found
            writer->handleDef(def);
        }

        writer->flush();

        return pOld.hasError()
            || pNew.hasError();
    }
    catch (const InFileException &e) {
        std::cerr << e.fileName << ": failed to open input file\n";
        return EXIT_FAILURE;
    }
}
