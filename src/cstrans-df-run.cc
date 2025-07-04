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

#include "regex.hh"
#include "version.hh"

#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <cctype>
#include <fstream>
#include <iostream>

typedef std::vector<std::string> TStringList;

const char *prog_name;

/// read non-empty list from value map "vm" with key "key" and store to "dst"
template<class TDst, class TMap>
bool readListFromValMap(TDst *pDst, const TMap &vm, const char *key)
{
    if (!vm.count(key))
        // "key" not found in "vm"
        return false;

    // store the list to "*pDst" and return "true" if the list is not empty
    TDst &dst = *pDst;
    dst = vm[key].template as<TDst>();
    return !dst.empty();
}

/// transformation properties set on cmd-line
struct TransformerProps {
    TStringList prefixCmd;  ///< cmd-line operands
    bool shellForm;         ///< if true, write shell form of RUN lines
    bool verbose;           ///< if true, print in/out of each transformation
};

class DockerFileTransformer {
    public:
        DockerFileTransformer(const TransformerProps &tp):
            tp_(tp),
            lineNum_(0)
        {
        }

        /// transform Dockerfile on in and write to out
        bool transform(std::istream &in, std::ostream &out);

    private:
        const TransformerProps  tp_;            ///< props set on cmd-line
        int                     lineNum_;       ///< line number being read

        void transformRunLine(std::string *);

        /// match ... in RUN ...
        const RE reLineRun_     = RE("^RUN (.*)$");

        /// match ... in ... BS-NL
        const RE reLineCont_    = RE("(^.*[^\\\\])\\\\ *$");

        // split RUN directive with options from the actual command
        const RE reLineRunOpts_ = RE("^(RUN +(?:--[A-Za-z0-9_]+=[^ ]+ +)*)(.*)$");

        /// text to construct RE taking "..." where inner quotes can be escaped
        const std::string rtQuotedStr_ = "\"([^\"\\\\]|\\\\.)*\"";

        /// match RUN ["cmd", "opt1", "opt2", ...] with zero or more opts
        const RE reLineRunExec_ = RE("^\\[\\s*(" + rtQuotedStr_
                + "(?:\\s*,\\s*" + rtQuotedStr_ + ")*)\\s*\\]\\s*$");

        /// match in-line comments
        const RE reComment_     = RE("^\\s*#.*$");

        /// construct transformed RUN command from execList
        std::string runCmdFromExecList(const TStringList &execList);
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
                if ('n' == c)
                    arg.push_back('\n');
                else if ('t' == c)
                    arg.push_back('\t');
                else
                    // FIXME: this works for back-slash and quote only
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

/// precede selected special chars by back-slash
std::string runQuoteArg(std::string arg, const bool escapeTick=false)
{
    boost::algorithm::replace_all(arg, "\\", "\\\\");
    boost::algorithm::replace_all(arg, "\"", "\\\"");
    boost::algorithm::replace_all(arg, "\n", "\\n");
    boost::algorithm::replace_all(arg, "\t", "\\t");

    if (escapeTick)
        boost::algorithm::replace_all(arg, "'", "\\'");

    return arg;
}

/// construct "'cmd' 'arg1' 'arg2' ..." from execList
std::string runShellCmdFromExecList(const TStringList &execList)
{
    std::string cmd;

    int i = 0;
    for (const std::string &arg : execList) {
        if (i++)
            // space-separator
            cmd += " ";

        const std::string quoted = runQuoteArg(arg, /* escapeTick */ true);
        if (quoted != arg)
            // construct $'...'
            cmd += "$";

        // append the quoted arg
        cmd += "'" + quoted + "'";
    }

    return cmd;
}

/// construct transformed RUN command from execList
std::string DockerFileTransformer::runCmdFromExecList(
        const TStringList &execList)
{
    if (this->tp_.shellForm)
        return runShellCmdFromExecList(execList);

    // construct ["cmd", "arg1", "arg2", ...] from execList
    std::string runLine = "[";
    int i = 0;
    for (const std::string &arg : execList) {
        if (i++)
            runLine += ", ";

        runLine += "\"" + runQuoteArg(arg) + "\"";
    }
    runLine += "]";
    return runLine;
}

void DockerFileTransformer::transformRunLine(std::string *pRunLine)
{
    // split RUN directive with options from the actual command
    boost::smatch sm;
    if (!boost::regex_match(*pRunLine, sm, reLineRunOpts_))
        // should never happen
        throw std::runtime_error("internal error");

    std::string newRunLine = sm[1];
    const std::string cmd = sm[2];

    // start with the prefix specified on cmd-line
    TStringList execList = tp_.prefixCmd;

    if (boost::regex_match(cmd, sm, reLineRunExec_))
        // ["cmd", "arg1", "arg2", ...]
        appendExecArgs(&execList, sm[1]);
    else
        // arbitrary shell code...
        appendShellExec(&execList, cmd);

    newRunLine += this->runCmdFromExecList(execList);
    if (tp_.verbose) {
        // diagnostic output printed with --verbose
        std::cerr << prog_name << " <<< " << *pRunLine << std::endl;
        std::cerr << prog_name << " >>> " << newRunLine << std::endl;
    }

    // return the result of a successful transformation
    *pRunLine = std::move(newRunLine);
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

        if (readingRunLine) {
            // check for comment because it does not need to end with back-slash
            if (boost::regex_match(line, reComment_))
                continue;
        }
        else if (!boost::regex_match(line, reLineRun_)) {
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
        try {
            this->transformRunLine(&runLine);
        }
        catch (const std::runtime_error &e) {
            std::cerr << prog_name << "error: parsing error on line "
                << lineNum_ << ": " << e.what() << std::endl;
            anyError = true;
        }

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

void printOpenError(const char *msg, const std::string &fileName)
{
    std::cerr << prog_name << ": error: "
        << msg << ": " << fileName
        << " (" << std::strerror(errno) << ")\n";
}

bool transformInPlace(DockerFileTransformer &dft, const std::string &fileName)
{
    using namespace boost::filesystem;

    // open input file and temporary output file
    std::ifstream fin(fileName);
    if (!fin) {
        printOpenError("failed to open input file", fileName);
        return false;
    }

    const path tmpFilePath = unique_path();
    const std::string tmpFileName = tmpFilePath.native();
    std::ofstream fout(tmpFileName);
    if (!fout) {
        printOpenError("failed to create temporary file", tmpFileName);
        return false;
    }

    // transform fin -> fout and close the streams
    const bool ok = dft.transform(fin, fout);
    fin.close();
    fout.close();

    if (ok)
        // rewrite input file by the temporary file
        rename(tmpFileName, fileName);
    else
        // something failed, drop the temporary file
        remove(tmpFileName);

    return ok;
}

int main(int argc, char *argv[])
{
    // used also in diagnostic messages
    ::prog_name = argv[0];

    namespace po = boost::program_options;
    po::variables_map vm;
    po::options_description desc(std::string("Usage: ") + prog_name
            + " [--in-place Dockerfile] [--verbose] cmd [arg1 [arg2 [...]]]");

    try {
        desc.add_options()
            ("in-place,i", po::value<std::string>(),
             "modify the specified file in-place")
            ("shell-form", "write transformed RUN lines using the shell form"
             " (rather than exec form, which is the default format)")
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

    // read cmd-line flags
    TransformerProps tp;
    tp.shellForm    = !!vm.count("shell-form");
    tp.verbose      = !!vm.count("verbose");

    // read the prefix command
    if (!readListFromValMap(&tp.prefixCmd, vm, "prefix-cmd")) {
        desc.print(std::cerr);
        return 1;
    }

    // create the transformer object
    DockerFileTransformer dft(tp);

    if (vm.count("in-place"))
        // transform Dockerfile in-place
        return !transformInPlace(dft, vm["in-place"].as<std::string>());

    // transform Dockerfile on stdin and write to stdout
    return !dft.transform(std::cin, std::cout);
}
