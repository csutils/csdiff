/*
 * Copyright (C) 2011-2021 Red Hat, Inc.
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

#include "xml-parser.hh"

#include "abstract-tree.hh"

#include <boost/property_tree/xml_parser.hpp>

// executable of the dynamic linker (used as ELF interpreter)
#ifndef LD_LINUX_SO
#   define LD_LINUX_SO "/lib64/ld-linux-x86-64.so.2"
#endif

/// tree decoder for valgrind XML output
class ValgrindTreeDecoder: public AbstractTreeDecoder {
    public:
        virtual bool readNode(Defect *def, pt::ptree::const_iterator defIter);

        virtual void readRoot(
                const pt::ptree       **pDefList,
                const pt::ptree        *root);

    private:
        Defect defPrototype = Defect("VALGRIND_WARNING");
};

/// hide explicit invocation of dynamic linker from command-line args
bool /* continue */ skipLdArgs(
        std::string                    *pExe,
        pt::ptree::const_iterator      *pIt,
        const pt::ptree::const_iterator itEnd)
{
    if (*pExe != LD_LINUX_SO)
        return /* continue */ true;

    for (bool skipArg = false; *pIt != itEnd; ++(*pIt)) {
        if (skipArg) {
            skipArg = false;
            continue;
        }

        const std::string argVal = (*pIt)->second.get_value<std::string>();
        if (argVal == "--preload")
            goto skip_arg;

        if (argVal == "--argv0")
            goto skip_arg;

        // record path of the real binary being executed
        *pExe = argVal;
        ++(*pIt);
        return /* continue */ (itEnd != *pIt);

skip_arg:
        skipArg = true;
    }

    return /* break */ false;
}

/// read command-line of the executed program
void readExeArgs(
        std::string                    *pExe,
        std::string                    *pArgs,
        const pt::ptree                *root)
{
    const pt::ptree *argsNode;
    if (!findChildOf(&argsNode, *root, "args"))
        return;

    const pt::ptree *argvNode;
    if (!findChildOf(&argvNode, *argsNode, "argv"))
        return;

    // read name of executable
    *pExe = valueOf<std::string>(*argvNode, "exe", *pExe);

    // read command-line args
    pt::ptree::const_iterator it;
    for (it = argvNode->begin(); argvNode->end() != it; ++it) {
        if (it->first != "arg")
            // skip this node
            continue;

        if (!skipLdArgs(pExe, &it, argvNode->end()))
            break;

        *pArgs += " ";
        *pArgs += it->second.get_value<std::string>();
    }
}

void ValgrindTreeDecoder::readRoot(
        const pt::ptree               **pDefList,
        const pt::ptree                *root)
{
    // valgrind reports will be at the same level in the XML tree
    *pDefList = root;

    const int pid = valueOf<int>(*root, "pid", 0);
    if (!pid)
        // insufficient data
        return;

    // read command-line
    std::string exe = "<unknown>";
    std::string args;
    readExeArgs(&exe, &args, root);

    // create a note event in the defect prototype
    this->defPrototype.events.push_back(DefEvent("note"));
    DefEvent &noteEvt = this->defPrototype.events.back();
    noteEvt.fileName = exe;

    // record PID and command-line args
    std::ostringstream str;
    str << "while executing process " << pid;
    if (!args.empty())
        str << " with arguments:" << args;
    noteEvt.msg = str.str();
    noteEvt.verbosityLevel = /* note */ 1;
}

/// read valgrind's message
std::string readMsg(const pt::ptree &defNode)
{
    const pt::ptree *whatNode;
    if (findChildOf(&whatNode, defNode, "what"))
        // message found in <what>...</what>
        return whatNode->get_value<std::string>();

    if (findChildOf(&whatNode, defNode, "xwhat")
            && findChildOf(&whatNode, *whatNode, "text"))
        // message found in <xwhat><text>...</text></xwhat>
        return whatNode->get_value<std::string>();

    // message not found
    return "<unknown>";
}

bool ValgrindTreeDecoder::readNode(Defect *pDef, pt::ptree::const_iterator defIter)
{
    static const std::string errorKey = "error";
    if (errorKey != defIter->first)
        // not a node we are interested in
        return false;

    // the current "error" node representing a single valgrind's report
    const pt::ptree &defNode = defIter->second;

    // initialize the defect structure
    Defect &def = *pDef;
    def = this->defPrototype;

    // initialize the key event
    def.keyEventIdx = def.events.size();
    def.events.push_back(DefEvent("warning"));
    DefEvent &keyEvent = def.events.back();
    keyEvent.fileName = "<unknown>";
    keyEvent.msg = readMsg(defNode);

    // read "kind" of the report
    pt::ptree::const_assoc_iterator itKind = defNode.find("kind");
    if (defNode.not_found() != itKind)
        keyEvent.event += "[" + itKind->second.get_value<std::string>() + "]";

    // TODO
    return true;
}

struct XmlParser::Private {
    InStream                       &input;
    AbstractTreeDecoder            *decoder = nullptr;
    pt::ptree                       root;
    const pt::ptree                *defList = nullptr;
    pt::ptree::const_iterator       defIter = root.end();

    Private(InStream &input):
        input(input)
    {
    }

    ~Private()
    {
        delete this->decoder;
    }
};

XmlParser::XmlParser(InStream &input):
    d(new Private(input))
{
    try {
        // parse XML
        read_xml(d->input.str(), d->root);

        // recognize inner format of the XML document
        pt::ptree *node = nullptr;
        if (findChildOf(&node, d->root, "valgrindoutput"))
            // valgrind XML format
            d->decoder = new ValgrindTreeDecoder;
        else
            throw pt::ptree_error("unknown XML format");

        // process the root node
        d->decoder->readRoot(&d->defList, node);

        // initialize the traversal through the list of defects/issues
        d->defIter = d->defList->begin();
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

XmlParser::~XmlParser()
{
    delete d;
}

bool XmlParser::hasError() const
{
    return d->input.anyError();
}

bool XmlParser::getNext(Defect *pDef)
{
    if (!d->defList)
        // initialization failed, error has already been reported
        return false;

    while (d->defList->end() != d->defIter) {
        // get the current node and move to the next one
        try {
            if (d->decoder->readNode(pDef, d->defIter++))
                return true;
        }
        catch (pt::ptree_error &e) {
            d->input.handleError(e.what());
        }
    }

    // EOF
    return false;
}
