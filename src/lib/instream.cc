/*
 * Copyright (C) 2011 - 2022 Red Hat, Inc.
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

#include "instream.hh"

InStream::InStream(std::string fileName, const bool silent):
    fileName_(std::move(fileName)),
    silent_(silent),
    str_((fileName_ == "-")
                ? std::cin
                : fileStr_)
{
    if (&str_ == &fileStr_)
        fileStr_.open(fileName_);

    if (!fileStr_)
        throw InFileException(fileName_);
}

InStream::InStream(std::istringstream &str, const bool silent):
    silent_(silent),
    str_(str)
{
}

void InStream::handleError(const std::string &msg, const unsigned long line)
{
    anyError_ = true;
    if (silent_ || msg.empty())
        return;

    std::cerr << fileName_;

    if (line)
        // line number available
        std::cerr << ":" << line;

    std::cerr << ": error: " << msg << "\n";
}

InStreamLookAhead::InStreamLookAhead(
        InStream               &input,
        const unsigned          size,
        const bool              skipBOM,
        bool                    skipWhiteSpaces)
{
    std::istream &inStr = input.str();

    int c = inStr.get();
    if (skipBOM
            // try to read BOM ... [0xEF, 0xBB, 0xBF]
            && (0xEF == c)
            && (0xBB == (c = inStr.get()))
            && (0xBF == (c = inStr.get())))
        // BOM successfully read -> read the next char
        c = inStr.get();

    // read chars from input
    for (;;) {
        if (skipWhiteSpaces && isspace(c))
            // skip a white-space
            goto next;

        // only the leading white-spaces are skipped
        skipWhiteSpaces = false;

        // append one char to the buffer
        buf_.push_back(c);
        if (size <= buf_.size())
            // the requested number of chars have been read
            break;
next:
        // read the next char
        c = inStr.get();
    }

    // put the chars back to the input stream
    for (auto it = buf_.rbegin(); it != buf_.rend(); ++it)
        inStr.putback(*it);
}
