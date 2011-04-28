# Copyright (C) 2011 Red Hat, Inc.
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

CXXFLAGS = -Wall -Wextra -O2

.PHONY: all clean
all: csdiff cstat

PARSER_OBJS = csparser.o csparser.yy.o
csdiff: csdiff.o $(PARSER_OBJS)
	g++ -o $@ csdiff.o $(PARSER_OBJS) -lboost_regex

cstat: cstat.o $(PARSER_OBJS)
	g++ -o $@ cstat.o $(PARSER_OBJS) -lboost_program_options -lboost_regex

csparser.yy.cc: csparser.lex
	flex -o $@ $<

# .hh deps (built manually for now)
$(PARSER_OBJS): csparser-priv.hh
csparser.o csdiff.o cstat.o: csparser.hh

clean:
	rm -fv csdiff csdiff.o cstat cstat.o $(PARSER_OBJS) csparser.yy.cc
