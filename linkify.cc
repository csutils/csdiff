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
#include "deflookup.hh"
#include "defqueue.hh"

#include <cstdlib>
#include <fstream>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/regex.hpp>

class DefQueryParser {
    public:
        struct QRow {
            int                         cid;
            std::string                 checker;
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
    dst.checker = tokens[/* checker */ 1];
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

    static void docOpen(
            const char                  *projName,
            const char                  *projURL,
            const char                  *defBase,
            const char                  *projNameOld);

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
            const std::string           &projNameOld,
            const DefQueryParser::QRow  &row,
            const bool                   isNew,
            const std::string           &comm = std::string());

    private:
        // library class
        HtWriter();
};

void HtWriter::docOpen(
        const char                      *projName,
        const char                      *projURL,
        const char                      *defBase,
        const char                      *projNameOld)
{
    std::cout << "<?xml version='1.0' encoding='utf-8'?>\n\
<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.1//EN' \
'http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd'>\n\
<html xmlns='http://www.w3.org/1999/xhtml'>\n\
<head><title>" << projName << " (defects listing)</title></head>\n\
<body>\n<h1>" << projName;

    const bool haveProject = (projURL && *projURL);

    if (!haveProject) {
        if (projNameOld && *projNameOld) {
            if (!!strcmp(projNameOld, ".security"))
                std::cout << " - defects not occurring in " << projNameOld;
        }
        else
            std::cout << " - defects not occurring upstream";
    }

    std::cout << "</h1>\n";

    if (defBase && *defBase) {
        const boost::regex re("([^/])/[^/].*$");
        const std::string urlOrigin(defBase);
        const std::string url(boost::regex_replace(urlOrigin, re, "$1"));
        std::cout << "<div style='margin: 48px 0px;'>\n  "
            "<span style='border: 4px #00FF00 solid; padding: 16px;'>To access "
            "the <b>Integrity Manager</b>, you need to log in first:\n    "
            "<form action='" << url << "/j_spring_security_check' "
            "method='post' target='_blank' style='display: inline;'>\n      "
            "<input type='hidden' name='j_username' value='admin' />\n      "
            "<input type='hidden' name='j_password' value='xxxxxx' />\n      "
            "<input type='submit' value='Log in' />\n    "
            "</form>\n  </span>\n</div>\n";
    }

    std::cout << "<pre style='" PRE_STYLE "'>\n";
    if (haveProject) {
        std::cout << "Browse the defect list via <b>Integrity Manager</b>: "
            "<a href='" << projURL << "'>" << projName << "</a>\n\n";
    }
}

void HtWriter::writeCheckerLine(
        const std::string               &defBase,
        const std::string               &chkBase,
        const std::string               &projNameOld,
        const DefQueryParser::QRow      &row,
        const bool                       isNew,
        const std::string               &comm)
{
    using std::cout;
    cout << "<b>Error: ";

    const bool hasChkLnk = !chkBase.empty();
    if (hasChkLnk)
        cout << "<a href='" << chkBase << row.checker << "'>";

    cout << row.checker;
    if (hasChkLnk)
        cout << "</a>";

    cout << "</b>";

    if (isNew) {
        cout << " <span style='color: #00FF00;'>"
            "[<b>warning:</b> defect not occurring ";

        if (projNameOld.empty())
            cout << "<b>upstream";
        else
            cout << "in <b>" << projNameOld;

        cout << "</b>]</span>";
    }

    if (!comm.empty())
        cout << " <i style='color: #808080;'>(" << comm << ")</i>";

    const int cid = row.cid;
    const bool hasDefLnk = !defBase.empty() && (0 < cid);
    if (hasDefLnk) {
        cout << " <a href='" << defBase << cid
            << "'>[Go to <b>Integrity Manager</b>: ";

        if (!row.fnc.empty()) {
            HtWriter::writeEscaped(row.fnc);
            cout << ", ";
        }

        cout << "CID " << cid << "]</a>";
    }

    cout << "\n";
}

class DefLinker {
    private:
        const std::string               defBase_;
        const std::string               chkBase_;
        const std::string               projNameOld_;
        const bool                      onlyNew_;

        DefLookup                      *oldLookup_;

        std::map<std::string, std::string>  chkComments_;

    public:
        typedef DefQueryParser::QRow    QRow;

        DefLinker(
                const char             *defBase,
                const char             *chkBase,
                const char             *chkComments,
                const char             *projNameOld,
                const bool              onlyNew,
                DefLookup              *oldLookup):
            defBase_(defBase),
            chkBase_(chkBase),
            projNameOld_(projNameOld),
            onlyNew_(onlyNew),
            oldLookup_(oldLookup)
        {
            std::fstream fstr(chkComments, std::ios::in);
            std::string line;
            while (std::getline(fstr, line)) {
                std::vector<std::string> tokens;
                boost::split(tokens, line, boost::algorithm::is_any_of("\t"));
                if (tokens.size() < 2)
                    continue;

                const std::string &chk     = tokens[0];
                const std::string &comment = tokens[1];
                chkComments_[chk] = comment;
            }
        }

        void printDef(const Defect &def, QRow row = QRow());

        void printBareCid(const QRow &);
};

void DefLinker::printDef(
        const Defect                    &def,
        DefQueryParser::QRow            row)
{
    using std::cout;

    bool isNew = oldLookup_ && !oldLookup_->lookup(def);
    if (onlyNew_) {
        if (isNew)
            isNew = false;
        else
            return;
    }

    if (-1 == row.cid)
        // no row was given, take checker from def
        row.checker = def.checker;

    const std::string &comm = chkComments_[row.checker];
    HtWriter::writeCheckerLine(
            defBase_,
            chkBase_,
            projNameOld_,
            row, isNew, comm);

    const unsigned cnt = def.events.size();
    for (unsigned i = 0; i < cnt; ++i) {
        const DefEvent &evt = def.events[i];
        cout << evt.fileName << ":" << evt.line << ":";

        if (0 < evt.column)
            cout << evt.column << ":";

        cout << " ";
        if (!evt.event.empty())
            cout << "<b>" << evt.event << "</b>: ";

        HtWriter::writeEscaped(evt.msg);
        cout << "\n";
    }

    cout << "\n";
}

void DefLinker::printBareCid(const DefQueryParser::QRow &row) {
    using std::cout;

    const std::string &comm = chkComments_[row.checker];
    HtWriter::writeCheckerLine(
            defBase_,
            chkBase_,
            projNameOld_,
            row,
            /* isNew */ false,
            comm);

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

class OrphanValidityChk {
    private:
        DefLookup                       invalid_;

    public:
        OrphanValidityChk(const DefLookup &invalid):
            invalid_(invalid)
        {
        }

        bool operator()(const Defect &def) {
            return /* continue */ invalid_.lookup(def);
        }
};

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

bool haveValidOrphans(DefQueue &stor, const DefLookup &invalid) {
    OrphanValidityChk visitor(invalid);
    return !stor.walk(visitor);
}

int main(int argc, char *argv[])
{
    // check if a file name was given
    if (argc < 6 || 9 < argc) {
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

    // filter out the directory part of the path when matching
    MsgFilter::inst()->setIgnorePath(true);

    // read defects from .err
    Parser defParser(defListStream, defListFile);
    DefQueue stor;
    Defect def;
    while (defParser.getNext(&def))
        stor.hashDefect(def);

    // close stream
    defListStream.close();

    DefLookup diffBase;
    const char *defBaseFile = "";
    if (7 < argc)
        defBaseFile = argv[/* .err */ 7];
    if (defBaseFile[0]) {
        std::fstream defBaseStream(defBaseFile, std::ios::in);
        if (!defBaseStream) {
            std::cerr << defBaseFile << ": failed to open input file\n";
            return EXIT_FAILURE;
        }

        // load defect list from run0 (or old release)
        Parser defBaseParser(defBaseStream, defBaseFile);
        while (defBaseParser.getNext(&def))
            diffBase.hashDefect(def);

        // here encountered parsing errors have no effect on the exit code
        defBaseStream.close();
    }

    const char *projNameOld = "";
    if (8 < argc)
        projNameOld = argv[/* IM project name of the old pkg */ 8];

    // output HTML header
    const char *const projName = argv[/* IM project name */ 1];
    const char *const projURL  = argv[/* IM project URL  */ 2];
    const char *const defBase  = argv[/* defect URL base */ 3];
    HtWriter::docOpen(projName, projURL, defBase, projNameOld);

    // a list of CIDs not matched in the .err file (they are going to appear
    // in a separate section)
    std::list<DefQueryParser::QRow> unmatched;

    // are we going to diff the list with an old defect list
    DefLookup *oldLookup = 0;
    const bool diffOld = defBaseFile[0];
    if (diffOld)
        oldLookup = &diffBase;

    // 'linker' writes translated defects to stdout
    const bool onlyNew = diffOld && !projURL[0];
    DefLinker linker(
            defBase,
            argv[/* checker URL base */ 4],
            argv[/* checker comments */ 6],
            projNameOld,
            onlyNew,
            oldLookup);

    // read defects IDs from stdin
    DefQueryParser qParser;
    DefQueryParser::QRow row;
    while (qParser.getNext(row)) {
        const int cid = row.cid;

        // look for the corresponding entry in .err (already hashed)
        if (!stor.lookup(def, row.checker, row.fileName)) {
            std::cerr << defListFile
                << ": warning: defect lookup failed, cid = " << cid << "\n";
            unmatched.push_back(row);
            continue;
        }

        // output a single defect
        linker.printDef(def, row);
    }

    if (!stor.empty() && (!onlyNew || haveValidOrphans(stor, diffBase))) {
        std::cerr << defListFile << ": warning: IM data seems incomplete\n";
        HtWriter::initSection("Defects Not Found in the Integrity Manager");

        // set up a visitor and guide it through orphans
        OrphanPrinter visitor(linker);
        stor.walk(visitor);
    }

    if (!unmatched.empty()) {
        std::string secHead("Defects Not Matched in ");
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
