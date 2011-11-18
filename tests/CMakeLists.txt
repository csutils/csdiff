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

# common setup for all tests
set(csdiff      "${csdiff_BINARY_DIR}/csdiff")
set(testdir     "${csdiff_SOURCE_DIR}/tests")
set(diffcmd     "diff -up")

# a generic template for a csdiff test-case
macro(test_csdiff dir num)
    set(tst "${testdir}/${dir}/${num}")

    set(cmd "${csdiff} ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test("${dir}-${num}-added" sh -c "${cmd}")

    set(cmd "${csdiff} -x ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test("${dir}-${num}-fixed" sh -c "${cmd}")

    set(cmd "${csdiff} -z ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add-z.err -")
    add_test("${dir}-${num}-added-with-z" sh -c "${cmd}")

    set(cmd "${csdiff} -xz ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix-z.err -")
    add_test("${dir}-${num}-fixed-with-z" sh -c "${cmd}")
endmacro()

# add regression tests ony by one
test_csdiff(diff7.0-qt                              00)
test_csdiff(diff7.0-fftw                            00)
test_csdiff(diff7.0-sudo                            00)
test_csdiff(diff7.0-libssh                          00)
test_csdiff(diff7.0-icu                             00)
test_csdiff(diff7.0-virtuoso-opensource             00)
test_csdiff(diff5.8-kernel                          00)
