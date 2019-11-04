/*
 * Copyright (C) 2019 Red Hat, Inc.
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

#include "version.hh"

#include <boost/algorithm/string/replace.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/tokenizer.hpp>

#include <cctype>
#include <iostream>

typedef std::vector<std::string> TStringList;

const char *prog_name;

class DockerFileTransformer {
    public:
        DockerFileTransformer(const TStringList &prefixCmd, const bool verbose):
            prefixCmd_(prefixCmd),
            verbose_(verbose),
            reLineRun_("^RUN (.*)$"),
            reLineRunExec_("^RUN  *\\[(.*)\\] *$"),
            reLineCont_("(^.*[^\\\\])\\\\$"),
            lineNum_(0)
        {
        }

        /// transform Dockerfile on in and write to out
        bool transform(std::istream &in, std::ostream &out);

    private:
        const TStringList   prefixCmd_;         ///< cmd-line operands
        const bool          verbose_;           ///< --verbose on cmd-line
        const boost::regex  reLineRun_;         ///< match ... in RUN ...
        const boost::regex  reLineRunExec_;     ///< match ... in RUN [...]
        const boost::regex  reLineCont_;        ///< match ... in ... BS-NL
        int                 lineNum_;           ///< line number being read

        bool transformRunLine(std::string *);
};

/// parse serialized list in the form: "item1", "item2", ...
void appendExecArgs(TStringList *pExecList, const std::string &str)
{
    enum EState {
        ES_SEEK_QUOT_OPEN,
        ES_BACK_SLASH,
        ES_SEEK_QUOT_CLOSE,
        ES_SEEK_COMMA
    } state = ES_SEEK_QUOT_OPEN;

    std::string arg;

    // process the given string char by char
    for (const unsigned char c : str) {
        switch (state) {
            case ES_SEEK_QUOT_OPEN:
                if ('\"' == c)
                    // found opening quote
                    state = ES_SEEK_QUOT_CLOSE;
                else if (!isspace(c))
                    throw std::runtime_error("quote expected");
                continue;

            case ES_BACK_SLASH:
                // one back-slash has been consumed
                arg.push_back(c);
                state = ES_SEEK_QUOT_CLOSE;
                continue;

            case ES_SEEK_QUOT_CLOSE:
                if ('\"' == c) {
                    // found closing quote -> append the string
                    pExecList->push_back(arg);
                    arg.clear();
                    state = ES_SEEK_COMMA;
                    continue;
                }
                else if ('\\' == c)
                    // consume one back-slash
                    state = ES_BACK_SLASH;
                else
                    // pick one char
                    arg.push_back(c);
                continue;

            case ES_SEEK_COMMA:
                if (',' == c)
                    // comma found -> look for opening quote
                    state = ES_SEEK_QUOT_OPEN;
                else if (!isspace(c))
                    throw std::runtime_error("comma expected");
                continue;
        }
    }

    if (ES_SEEK_COMMA != state)
        throw std::runtime_error("unexpected end of input while parsing list");
}

/// invoke shell interpreter explicitly in case the wrapper uses exec()
void appendShellExec(TStringList *pExecList, const std::string &str)
{
    pExecList->push_back("sh");
    pExecList->push_back("-c");
    pExecList->push_back(str);
}

/// precede each back-slash and each quote by back-slash
std::string runQuoteArg(std::string arg)
{
    boost::algorithm::replace_all(arg, "\\", "\\\\");
    boost::algorithm::replace_all(arg, "\"", "\\\"");
    boost::algorithm::replace_all(arg, "\t", "\\t");
    return arg;
}

std::string runLineFromExecList(const TStringList &execList)
{
    // construct RUN ["cmd", "arg1", "arg2", ...] from execList
    std::string runLine = "RUN [";
    int i = 0;
    for (const std::string &arg : execList) {
        if (i++)
            runLine += ", ";

        runLine += "\"" + runQuoteArg(arg) + "\"";
    }
    runLine += "]";
    return runLine;
}

bool DockerFileTransformer::transformRunLine(std::string *pRunLine)
{
    // start with the prefix specified on cmd-line
    TStringList execList = prefixCmd_;

    try {
        boost::smatch sm;
        if (boost::regex_match(*pRunLine, sm, reLineRunExec_))
            // RUN ["cmd", "arg1", "arg2", ...]
            appendExecArgs(&execList, sm[1]);

        else if (boost::regex_match(*pRunLine, sm, reLineRun_))
            // RUN arbitrary shell code...
            appendShellExec(&execList, sm[1]);

        else
            // should never happen
            throw std::runtime_error("internal error");
    }
    catch (const std::runtime_error &e) {
        std::cerr << prog_name << "error: parsing error on line "
            << lineNum_ << ": " << e.what() << std::endl;
        return false;
    }

    const std::string newRunLine = runLineFromExecList(execList);
    if (verbose_) {
        // diagnostic output printed with --verbose
        std::cerr << prog_name << " <<< " << *pRunLine << std::endl;
        std::cerr << prog_name << " >>> " << newRunLine << std::endl;
    }

    // return the result of a successful tranformation
    *pRunLine = newRunLine;
    return true;
}

bool DockerFileTransformer::transform(std::istream &in, std::ostream &out)
{
    bool anyError = false;
    bool anyRunLine = false;        ///< true if any RUN line was transformed
    bool readingRunLine = false;    ///< true if multi-line RUN is being read
    std::string line;
    std::string runLine;
    lineNum_ = 0;

    // read input line by line
    while (std::getline(in, line)) {
        lineNum_++;

        if (!readingRunLine && !boost::regex_match(line, reLineRun_)) {
            // pass unrelated contents of Dockerfile unchanged
            out << line << std::endl;
            continue;
        }

        // check for line ending with back-slash (multi-line RUN)
        boost::smatch sm;
        const bool lineCont = boost::regex_match(line, sm, reLineCont_);
        if (lineCont)
            line = sm[1];

        // append the current line to our linearized RUN line
        runLine += line;
        readingRunLine = lineCont;
        if (readingRunLine)
            continue;

        // transform the linearized RUN line
        if (!this->transformRunLine(&runLine))
            anyError = true;

        // write the transformed RUN line and update state
        out << runLine << std::endl;
        runLine.clear();
        anyRunLine = true;
    }

    if (!anyRunLine) {
        // no match is treated as error
        std::cerr << prog_name << ": error: no RUN line found\n";
        anyError = true;
    }

    return !anyError;
}

int main(int argc, char *argv[])
{
    // used also in diagnostic messages
    ::prog_name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(std::string("Usage: ") + prog_name
            + " [--verbose] cmd [arg1 [arg2 [...]]]");

    try {
        desc.add_options()
            ("verbose", "print transformations to standard error output");

        desc.add_options()
            ("help", "produce help message")
            ("version", "print version");

        po::options_description hidden("");
        hidden.add_options()
            ("prefix-cmd", po::value<TStringList>(), "cmd [arg1 [arg2 [...]]]");
        po::positional_options_description p;
        p.add("prefix-cmd", -1);

        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        po::options_description opts;
        opts.add(desc).add(hidden);
        po::store(po::command_line_parser(argc, argv).
                options(opts).positional(p).run(), vm);
        po::notify(vm);
    }
    catch (po::error &e) {
        std::cerr << prog_name << ": error: " << e.what() << "\n\n";
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

    const bool verbose = !!vm.count("verbose");

    if (!vm.count("prefix-cmd")) {
        desc.print(std::cerr);
        return 1;
    }

    const TStringList &prefixCmd = vm["prefix-cmd"].as<TStringList>();
    if (prefixCmd.empty()) {
        desc.print(std::cerr);
        return 1;
    }

    // pass cmd-line args to DockerFileTransformer
    DockerFileTransformer dft(prefixCmd, verbose);

    // transform Dockerfile on stdin and write to stdout
    return !dft.transform(std::cin, std::cout);
}
