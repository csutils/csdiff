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

#include "parser-xml.hh"

#include "abstract-tree.hh"

#include <boost/property_tree/xml_parser.hpp>

// executable of the dynamic linker (used as ELF interpreter)
#ifndef LD_LINUX_SO
#   define LD_LINUX_SO "/lib64/ld-linux-x86-64.so.2"
#endif

/// tree decoder for valgrind XML output
class ValgrindTreeDecoder: public AbstractTreeDecoder {
    public:
        bool readNode(Defect *def) override;

        void readRoot(const pt::ptree *root) override;

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

        const std::string argVal = getStringValue(*pIt);
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
        *pArgs += getStringValue(it);
    }
}

void ValgrindTreeDecoder::readRoot(const pt::ptree *root)
{
    // valgrind reports will be at the same level in the XML tree
    defList_ = root;
    defIter_ = root->begin();

    // only valgrind produces this data format
    this->defPrototype.tool = "valgrind";

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
        return getStringValue(*whatNode);

    if (findChildOf(&whatNode, defNode, "xwhat")
            && findChildOf(&whatNode, *whatNode, "text"))
        // message found in <xwhat><text>...</text></xwhat>
        return getStringValue(*whatNode);

    // message not found
    return "<unknown>";
}

/// return true if the given frame is internal to valgrind itself
bool isInternalFrame(const pt::ptree &frameNode)
{
    std::string obj = valueOf<std::string>(frameNode, "obj", "");
    if (obj.empty())
        return false;

    static const std::string valgrindPrefix = "/usr/libexec/valgrind/";
    static const size_t valgrindPrefixLen = valgrindPrefix.size();
    if (obj.size() <= valgrindPrefixLen)
        return false;

    obj.resize(valgrindPrefixLen);
    return (valgrindPrefix == obj);
}

/// go through stack, append "note" events, and update the key event
void readStack(Defect *pDef, const pt::ptree &stackNode)
{
    int keyEventBestScore = -1;

    for (const pt::ptree::value_type &frame : stackNode) {
        const pt::ptree &frameNode = frame.second;
        const bool intFrame = isInternalFrame(frameNode);
        int keyEventScore = 0;

        // initialize "note" event
        DefEvent noteEvt("note");
        noteEvt.msg = "called from ";
        noteEvt.verbosityLevel = /* note */ 1 + static_cast<int>(intFrame);

        // read function name if available
        const std::string fn = valueOf<std::string>(frameNode, "fn", "");
        noteEvt.msg += (fn.empty())
            ? "here"
            : fn + "()";

        const pt::ptree *fileNode;
        if (findChildOf(&fileNode, frameNode, "file")) {
            // read absolute path of the source file
            noteEvt.fileName = getStringValue(*fileNode);
            const std::string dir = valueOf<std::string>(frameNode, "dir", "");
            if (!dir.empty())
                noteEvt.fileName = dir + "/" + noteEvt.fileName;

            // read line number
            noteEvt.line = valueOf<int>(frameNode, "line", 0);
            keyEventScore = 8;
        }
        else if (findChildOf(&fileNode, frameNode, "obj")) {
            // pick path of the object file
            noteEvt.fileName = getStringValue(*fileNode);
            keyEventScore = 4;
        }
        else if (findChildOf(&fileNode, frameNode, "ip")) {
            // pick address of the code in memory
            noteEvt.fileName = getStringValue(*fileNode);
            keyEventScore = 2;
        }
        else {
            // no location info found --> skip this frame
            continue;
        }

        if (!intFrame && keyEventBestScore < keyEventScore) {
            // update key event
            keyEventBestScore = keyEventScore;
            DefEvent &keyEvent = pDef->events[pDef->keyEventIdx];
            keyEvent.fileName = noteEvt.fileName;
            keyEvent.line     = noteEvt.line;
        }

        // finally push the "note" event
        pDef->events.push_back(noteEvt);
    }
}

bool ValgrindTreeDecoder::readNode(Defect *pDef)
{
    if (!defList_)
        // initialization failed
        return false;

    pt::ptree::const_iterator it;
    do {
        if (defList_->end() == defIter_)
            // EOF
            return false;

        // move the iterator after we get the current position
        it = defIter_++;
    }
    while ("error" != it->first);

    // the current "error" node representing a single valgrind's report
    const pt::ptree &defNode = it->second;

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
    const std::string kind = valueOf<std::string>(defNode, "kind", "");
    if (!kind.empty())
        keyEvent.event += "[" + kind + "]";

    // go through stack trace
    const pt::ptree *stackNode;
    if (findChildOf(&stackNode, defNode, "stack"))
        // this invalidates &keyEvent !!!
        readStack(pDef, *stackNode);

    // read aux valgrind's message if available and insert _after_ the key event
    const pt::ptree *auxwhat;
    if (findChildOf(&auxwhat, defNode, "auxwhat")) {
        DefEvent auxEvent = def.events[def.keyEventIdx];
        auxEvent.event = "note";
        auxEvent.verbosityLevel = /* note */ 1;
        auxEvent.msg = getStringValue(*auxwhat);
        def.events.insert(def.events.begin() + def.keyEventIdx + 1, auxEvent);
    }

    return true;
}

struct XmlParser::Private {
    using TDecoderPtr = std::unique_ptr<AbstractTreeDecoder>;

    InStream                       &input;
    TDecoderPtr                     decoder;
    pt::ptree                       root;

    Private(InStream &input):
        input(input)
    {
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
            d->decoder.reset(new ValgrindTreeDecoder);
        else
            throw pt::ptree_error("unknown XML format");

        // process the root node
        d->decoder->readRoot(node);
    }
    catch (pt::file_parser_error &e) {
        d->input.handleError(e.message(), e.line());
    }
    catch (pt::ptree_error &e) {
        d->input.handleError(e.what());
    }
}

XmlParser::~XmlParser() = default;

bool XmlParser::hasError() const
{
    return d->input.anyError();
}

bool XmlParser::getNext(Defect *pDef)
{
    // error recovery loop
    for (;;) {
        try {
            return d->decoder->readNode(pDef);
        }
        catch (pt::ptree_error &e) {
            d->input.handleError(e.what());
        }
    }
}
