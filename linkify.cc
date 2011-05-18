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

#include "csfilter.hh"
#include "csparser.hh"

#include <cstdlib>
#include <fstream>
#include <map>
#include <list>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>

#define DEBUG_DEF_MATCH                 0
#define DEBUG_LOOKUP_OFFSET             0

class DefQueue {
    private:
        typedef std::list<Defect>                       TDefList;
        typedef std::map<std::string, TDefList>         TDefByFile;
        typedef std::map<std::string, TDefByFile>       TDefByClass;

        TDefByClass                     stor_;
        MsgFilter                      *filt_;

    public:
        DefQueue():
            filt_(MsgFilter::inst())
        {
        }

        void hashDefect(const Defect &);

        bool lookup(
                Defect                  &dst,
                const std::string       &checker,
                const std::string       &fileName);

        bool empty() const {
            return stor_.empty();
        }

        template <class TVisitor> bool walk(TVisitor &);
};

void DefQueue::hashDefect(const Defect &def)
{
    TDefByFile &row = stor_[def.defClass];
    TDefList &col = row[filt_->filterPath(def.fileName)];
    col.push_back(def);
}

bool DefQueue::lookup(
        Defect                  &dst,
        const std::string       &checker,
        const std::string       &fileName)
{
    // look for the given defect class
    TDefByClass::iterator iRow = stor_.find(checker);
    if (stor_.end() == iRow) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": not found\n";
#endif
        return false;
    }

    TDefByFile &row = iRow->second;
    if (row.empty()) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": row empty\n";
#endif
        return false;
    }

    // look for the given file name
    std::string path = filt_->filterPath(fileName);
    TDefByFile::iterator iCol = row.find(path);
    if (row.end() == iCol) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": " << path << ": not found\n";
#endif
        return false;
    }

    TDefList &col = iCol->second;
    if (row.empty()) {
#if DEBUG_DEF_MATCH
        std::cerr << checker << ": " << path << ": list empty\n";
#endif
        return false;
    }

    // remove the first defect in the list...
    dst = col.front();
    col.pop_front();
    if (col.empty()) {
        // ... and subsequently the list itself once it becomes empty
        row.erase(iCol);
#if DEBUG_LOOKUP_OFFSET
        std::cerr << checker << ": " << path
            << ": list removed, row.size() = " << row.size() << "\n";
#endif
        if (row.empty()) {
            // ... and eventually also the row where the list belongs to
            stor_.erase(iRow);
#if DEBUG_LOOKUP_OFFSET
            std::cerr << checker << ": row removed, stor_.size() = "
                << stor_.size() << "\n";
#endif
        }
    }

    // TODO: What else should we (and are we able to) check? fnc names?
    return true;
}

template <class TVisitor> bool DefQueue::walk(TVisitor &visitor) {
    BOOST_FOREACH(const TDefByClass::const_reference iRow, stor_)
        BOOST_FOREACH(const TDefByFile::const_reference iCol, iRow.second)
            BOOST_FOREACH(const Defect &def, iCol.second)
                if (! /* continue */ visitor(def))
                    return false;

    return true;
}

class DefQueryParser {
    public:
        struct QRow {
            int                         cid;
            std::string                 defClass;
            std::string                 fileName;
            std::string                 fnc;

            QRow(): cid(-1) { }
        };

        DefQueryParser():
            lineno_(0),
            hasError_(false)
        {
        }

        bool getNext(QRow &dst);

        bool hasError() const {
            return hasError_;
        }

    private:
        int lineno_;
        bool hasError_;
        bool parse(QRow &dst);
};

bool DefQueryParser::parse(DefQueryParser::QRow &dst) {
    // read one line from stdin
    std::string line;
    if (!std::getline(std::cin, line))
        return false;

    // increment the line counter
    ++lineno_;

    // tokenize the line
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::algorithm::is_any_of(","));
    if (tokens.size() < 3) {
        std::cerr << "-:" << lineno_ << ": error: not enough ',' at the line\n";
        return false;
    }

    // parse cid
    try {
        dst.cid = boost::lexical_cast<int>(tokens[/* cid */ 0]);
    }
    catch(boost::bad_lexical_cast &) {
        std::cerr << "-:" << lineno_ << ": error: failed to parse CID\n";
        return false;
    }

    // all OK
    dst.defClass = tokens[/* defClass */ 1];
    dst.fileName = tokens[/* fileName */ 2];
    if (3 < tokens.size())
        dst.fnc  = tokens[/* fnc      */ 3];

    return true;
}

bool DefQueryParser::getNext(DefQueryParser::QRow &dst) {
    // error recovery loop
    while (std::cin) {
        if (this->parse(dst))
            return true;
        else
            hasError_ = true;
    }

    // EOF
    return false;
}

struct HtWriter {
#define PRE_STYLE "white-space: pre-wrap;"

    static void docOpen(const char *projName, const char *projURL) {
        std::cout << "<?xml version='1.0' encoding='utf-8'?>\n\
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.1//EN' \
'http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd'>\n\
<html xmlns='http://www.w3.org/1999/xhtml'>\n\
<head><title>" << projName << " (defects listing)</title></head>\n\
<body>\n<pre style='" PRE_STYLE "'>\n";

        if (projURL && *projURL) {
            std::cout << "Browse the defect list via <b>Integrity Manager</b>: "
                "<a href='" << projURL << "'>" << projName << "</a>\n\n";
        }
    }

    static void docClose() {
        std::cout << "</pre>\n</body>\n</html>\n";
    }

    static void initSection(std::string name) {
        std::cout << "</pre>\n<h3>" << name << "</h3>\n"
            "<pre style='" PRE_STYLE "'>\n";
    }

    static void writeEscaped(std::string text) {
        using boost::algorithm::replace_all;

        replace_all(text,  "&", "&amp;" );
        replace_all(text, "\"", "&quot;");
        replace_all(text, "\'", "&apos;");
        replace_all(text,  "<", "&lt;"  );
        replace_all(text,  ">", "&gt;"  );

        std::cout << text;
    }

    static void writeCheckerLine(
            const std::string           &defBase,
            const std::string           &chkBase,
            const DefQueryParser::QRow  &row);

    private:
        // library class
        HtWriter();
};

void HtWriter::writeCheckerLine(
        const std::string               &defBase,
        const std::string               &chkBase,
        const DefQueryParser::QRow      &row)
{
    using std::cout;
    cout << "<b>Error: ";

    const bool hasChkLnk = !chkBase.empty();
    if (hasChkLnk)
        cout << "<a href='" << chkBase << row.defClass << "'>";

    cout << row.defClass;
    if (hasChkLnk)
        cout << "</a>";

    cout << "</b>";

    const int cid = row.cid;
    const bool hasDefLnk = !defBase.empty() && (0 < cid);
    if (hasDefLnk) {
        cout << " <a href='" << defBase << cid
            << "'>[Go to <b>Integrity Manager</b>: ";

        if (!row.fnc.empty())
            cout << row.fnc << ", ";

        cout << "CID " << cid << "]</a>";
    }

    cout << "\n";
}

class DefLinker {
    private:
        std::string                     defBase_;
        std::string                     chkBase_;

    public:
        typedef DefQueryParser::QRow    QRow;

        DefLinker(const char *defBase, const char *chkBase):
            defBase_(defBase),
            chkBase_(chkBase)
        {
        }

        void printDef(const Defect &def, QRow row = QRow());

        void printBareCid(const QRow &);
};

void DefLinker::printDef(
        const Defect                    &def,
        DefQueryParser::QRow            row)
{
    using std::cout;

    if (-1 == row.cid)
        // no row was given, take defClass from def
        row.defClass = def.defClass;

    HtWriter::writeCheckerLine(defBase_, chkBase_, row);

    const unsigned cnt = def.msgs.size();
    for (unsigned i = 0; i < cnt; ++i) {
        const DefMsg &msg = def.msgs[i];
        cout << msg.fileName << ":" << msg.line << ":";

        if (0 < msg.column)
            cout << msg.column << ":";

        cout << " ";
        if (!msg.event.empty())
            cout << "<b>" << msg.event << "</b>: ";

        HtWriter::writeEscaped(msg.msg);
        cout << "\n";
    }

    cout << "\n";
}

void DefLinker::printBareCid(const DefQueryParser::QRow &row) {
    using std::cout;

    HtWriter::writeCheckerLine(defBase_, chkBase_, row);

    if (!row.fileName.empty()) {
        // print file name
        cout << row.fileName << ":";

        // print a function name if available
        if (!row.fnc.empty())
            cout << " <b>" << row.fnc << "</b>";

        cout << " [<i>Sorry, no more details available...</i>]\n";
    }

    cout << "\n";
}

class OrphanPrinter {
    private:
        DefLinker                       linker_;

    public:
        OrphanPrinter(const DefLinker &linker):
            linker_(linker)
        {
        }

        bool operator()(const Defect &def) {
            linker_.printDef(def);
            return /* continue */ true;
        }
};

int main(int argc, char *argv[])
{
    // check if a file name was given
    if (argc != 6) {
        std::cerr << "WARNING: " << argv[0]
            << " is UNDOCUMENTED and is NOT supposed to be used on its own\n";
        return EXIT_FAILURE;
    }

    // open .err
    const char *defListFile = argv[/* .err */ 5];
    std::fstream defListStream(defListFile, std::ios::in);
    if (!defListStream) {
        std::cerr << defListFile << ": failed to open input file\n";
        return EXIT_FAILURE;
    }

    // output HTML header
    HtWriter::docOpen(
            argv[/* IM project name */ 1],
            argv[/* IM project URL  */ 2]);

    // read defects from .err
    Parser defParser(defListStream, defListFile);
    DefQueue stor;
    Defect def;
    while (defParser.getNext(&def))
        stor.hashDefect(def);

    // close stream
    defListStream.close();

    // a list of CIDs not matched in the .err file (they are going to appear
    // in a separate section)
    std::list<DefQueryParser::QRow> unmatched;

    // this allows to write translated defects to stdout
    DefLinker linker(
            argv[/* defect  URL base */ 3],
            argv[/* checker URL base */ 4]);

    // read defects IDs from stdin
    DefQueryParser qParser;
    DefQueryParser::QRow row;
    while (qParser.getNext(row)) {
        const int cid = row.cid;

        // look for the corresponding entry in .err (already hashed)
        if (!stor.lookup(def, row.defClass, row.fileName)) {
            std::cerr << defListFile
                << ": warning: defect lookup failed, cid = " << cid << "\n";
            unmatched.push_back(row);
            continue;
        }

        // output a single defect
        linker.printDef(def, row);
    }

    if (!stor.empty()) {
        std::cerr << defListFile << ": warning: IM data seems incomplete\n";
        HtWriter::initSection("Defects Not Found in the Integrity Manager");

        // set up a visitor and guide it through orphans
        OrphanPrinter visitor(linker);
        stor.walk(visitor);
    }

    if (!unmatched.empty()) {
        std::string secHead("Defects Not matched in ");
        HtWriter::initSection(secHead + defListFile);

        do {
            linker.printBareCid(unmatched.front());
            unmatched.pop_front();
        }
        while (!unmatched.empty());
    }

    // output HTML footer
    HtWriter::docClose();

    // we treat only parsing errors as errors, lookup errors are warnings for us
    return qParser.hasError()
        || defParser.hasError();
}
