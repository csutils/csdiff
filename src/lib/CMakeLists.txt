# Copyright (C) 2011 - 2022 Red Hat, Inc.
#
# This file is part of csdiff.
#
# csdiff is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# csdiff is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with csdiff.  If not, see <http://www.gnu.org/licenses/>.

# cslib.a
add_library(cs STATIC
    abstract-filter.cc
    color.cc
    csdiff-core.cc
    csv-parser.cc
    cwe-mapper.cc
    cwe-name-lookup.cc
    deflookup.cc
    filter.cc
    finger-print.cc
    glob-expand.cc
    instream.cc
    msg-filter.cc
    parser.cc
    parser-common.cc
    parser-cov.cc
    parser-gcc.cc
    parser-json.cc
    parser-json-cov.cc
    parser-json-gcc.cc
    parser-json-sarif.cc
    parser-json-shchk.cc
    parser-json-simple.cc
    parser-json-zap.cc
    parser-xml.cc
    parser-xml-valgrind.cc
    version.cc
    writer.cc
    writer-cov.cc
    writer-html.cc
    writer-json.cc
    writer-json-common.cc
    writer-json-sarif.cc
    writer-json-simple.cc
)
