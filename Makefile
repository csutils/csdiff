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

NUM_CPU ?= $(shell getconf _NPROCESSORS_ONLN 2>/dev/null || echo 1)

CMAKE ?= cmake
CTEST ?= ctest -j$(NUM_CPU) --progress

SANITIZERS ?= OFF

CMAKE_BUILD_TYPE ?= RelWithDebInfo

.PHONY: all check clean sanitizers distclean distcheck distcheck-sanitizers \
	fast install version.cc src/lib/version.cc

all: version.cc
	mkdir -p csdiff_build
	cd csdiff_build && $(CMAKE) \
		-D 'CMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)' \
		-D SANITIZERS='$(SANITIZERS)' ..
	$(MAKE) -sC csdiff_build -j$(NUM_CPU)

fast: version.cc
	$(MAKE) -sC csdiff_build

check: all
	cd csdiff_build && $(CTEST) --output-on-failure

clean:
	if test -e csdiff_build/Makefile; then $(MAKE) clean -C csdiff_build; fi

sanitizers:
	$(MAKE) -s all SANITIZERS=ON

distclean:
	if test -e .git; then rm -f src/lib/version.cc; fi
	rm -rf csdiff_build

distcheck: distclean
	$(MAKE) -s check

distcheck-sanitizers:
	$(MAKE) -s distcheck SANITIZERS=ON

install: all
	$(MAKE) -C csdiff_build install

version.cc: src/lib/version.cc

src/lib/version.cc:
	@if test -e .git; then \
		cmd='git describe --always | sed -e "s/^csdiff-//" -e "s/-.*-/.$$(git log --pretty="%cd" --date=iso -1 | tr -d ":-" | tr " " . | cut -d. -f 1,2)./"'; \
	else \
		cmd='basename $$(readlink -f .) | cut -f2 -d-'; \
	fi \
		&& printf "#include \"version.hh\"\nconst char *CS_VERSION = \"%s\";\n" \
			"$$(eval "$$cmd")" > $@.tmp \
		&& install -m0644 -C -v $@.tmp $@ \
		&& rm -f $@.tmp
