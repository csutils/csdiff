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

CMAKE ?= cmake
CTEST ?= ctest

CPPCHECK = cppcheck -j5 \
		   --enable=style,performance,portability,information,missingInclude \
		   --template gcc \
		   --inline-suppr

CMAKE_BUILD_TYPE ?= RelWithDebInfo

.PHONY: all check clean cppcheck distclean distcheck fast install

all:
	mkdir -p csdiff_build
	cd csdiff_build && $(CMAKE) -D 'CMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)' ..
	$(MAKE) -C csdiff_build

fast:
	$(MAKE) -sC csdiff_build

check: all
	cd csdiff_build && $(CTEST) --output-on-failure

cppcheck: all
	$(CPPCHECK) .

clean:
	if test -e csdiff_build/Makefile; then $(MAKE) clean -C csdiff_build; fi

distclean:
	rm -rf csdiff_build

distcheck: distclean
	$(MAKE) check

install: all
	$(MAKE) -C csdiff_build install
