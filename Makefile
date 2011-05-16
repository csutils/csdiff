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

TARGETS = csdiff csgrep cstat
all: $(TARGETS)

PARSER_OBJS = csparser.o csparser.yy.o
CSLIB_OBJS = csfilter.o $(PARSER_OBJS) cstat-core.o
cslib.a: $(CSLIB_OBJS)
	ar r $@ $(CSLIB_OBJS)
	ranlib $@

csdiff: csdiff.o cslib.a
	g++ -o $@ csdiff.o cslib.a -lboost_regex

csgrep: csgrep.o cslib.a
	g++ -o $@ csgrep.o cslib.a -lboost_program_options -lboost_regex

cstat: cstat.o cslib.a
	g++ -o $@ cstat.o cslib.a -lboost_program_options -lboost_regex

csparser.yy.cc: csparser.lex
	flex -o $@ $<

# .hh deps (built manually for now)
$(PARSER_OBJS): csparser-priv.hh
csparser.o csdiff.o cstat-core.o: csparser.hh
csgrep.o cstat.o cstat-core.o: cstat-core.hh
csdiff.o csfilter.o: csfilter.hh

clean:
	rm -fv *.o cslib.a $(TARGETS) csparser.yy.cc
