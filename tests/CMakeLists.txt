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
set(csgrep      "${csdiff_BINARY_DIR}/csgrep")
set(cssort      "${csdiff_BINARY_DIR}/cssort")
set(testdir     "${csdiff_SOURCE_DIR}/tests")
set(csjson      "${csgrep} --mode=json")
set(diffcmd     "diff -up")

# new versions of Boost tend to escape '/' in JSON strings, no idea why
set(jsfilter    "sed 's|\\\\\\\\\\\\\\\\/|/|g'")

macro(add_test_wrap test_name cmd)
    add_test("${test_name}" sh -c "${cmd}")
    set_tests_properties(${test_name} PROPERTIES COST ${test_cost})
    math(EXPR test_cost "${test_cost} - 1")
endmacro()

set(test_cost 1048576)

# a generic template for a csdiff test-case
macro(test_csdiff dir num)
    set(tst "${testdir}/${dir}/${num}")

    set(cmd "${csdiff} -c ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("${dir}-${num}-added" "${cmd}")

    set(cmd "${csdiff} -x ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("${dir}-${num}-fixed" "${cmd}")

    set(cmd "${csdiff} -z ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add-z.err -")
    add_test_wrap("${dir}-${num}-added-with-z" "${cmd}")

    set(cmd "${csdiff} -xz ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix-z.err -")
    add_test_wrap("${dir}-${num}-fixed-with-z" "${cmd}")

    set(cmd "${csdiff} -c ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("${dir}-${num}-added-with-c" "${cmd}")

    set(cmd "${csdiff} -jx ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("${dir}-${num}-fixed-with-j" "${cmd}")
endmacro()

# a generic template for csparser test-cases
macro(test_csparser dir num)
    set(tst "${testdir}/${dir}/${num}")

    set(cmd "${csgrep} ${tst}-stdin.txt 2>/dev/null")
    set(cmd "${cmd} | ${diffcmd} ${tst}-stdout.txt -")
    add_test_wrap("${dir}-${num}-stdout" "${cmd}")

    set(cmd "${csgrep} ${tst}-stdin.txt 2>&1 >/dev/null")
    set(cmd "${cmd} | sed -s 's|^[^:]*/||' | ${diffcmd} ${tst}-stderr.txt -")
    add_test_wrap("${dir}-${num}-stderr" "${cmd}")
endmacro()

# a generic template for csgrep test-cases
macro(test_csgrep dir num)
    set(tst "${testdir}/${dir}/${num}")

    file(READ ${tst}-args.txt args)
    string(REPLACE "\n" "" args ${args})
    set(cmd "${csgrep} ${args} ${tst}-stdin.txt")
    set(cmd "${cmd} | ${diffcmd} ${tst}-stdout.txt -")
    add_test_wrap("${dir}-${num}" "${cmd}")
endmacro()

# a generic template for cssort test-cases
macro(test_cssort dir num)
    set(tst "${testdir}/${dir}/${num}")

    set(cmd "${cssort} --key=checker ${tst}-input.err 2>/dev/null")
    set(cmd "${cmd} | ${jsfilter} | ${diffcmd} ${tst}-by-checker.err -")
    add_test_wrap("${dir}-${num}-by-checker" "${cmd}")

    set(cmd "${cssort} --key=path ${tst}-input.err 2>/dev/null")
    set(cmd "${cmd} | ${jsfilter} | ${diffcmd} ${tst}-by-path.err -")
    add_test_wrap("${dir}-${num}-by-path" "${cmd}")
endmacro()

# csgrep tests
test_csgrep(csgrep      "00-exclude-conftest"         )
test_csgrep(csgrep      "01-remove-duplicates"        )
test_csgrep(csgrep      "02-compiler-warnings"        )
test_csgrep(csgrep      "03-compiler-warnings"        )
test_csgrep(csgrep      "04-compiler-warnings"        )
test_csgrep(csgrep      "05-compiler-warnings"        )
test_csgrep(csgrep      "06-cppcheck-warnings"        )
test_csgrep(csgrep      "07-cppcheck-warnings"        )
test_csgrep(csgrep      "08-cppcheck-warnings"        )
test_csgrep(csgrep      "09-err-file-comments"        )
test_csgrep(csgrep      "10-err-file-comments"        )
test_csparser(csparser-5.8                          00)
test_csparser(csparser-5.8                          01)
test_csparser(csparser-5.8                          02)

# cssort tests
test_cssort(cssort-5.8                              00)
test_cssort(cssort-5.8                              01)
test_cssort(cssort-5.8                              02)
test_cssort(cssort-5.8                              03)

# csdiff tests
test_csdiff(diff5.9-kernel                          00)
test_csdiff(diff7.0-qt                              00)
test_csdiff(diff7.0-fftw                            00)
test_csdiff(diff7.0-sudo                            00)
test_csdiff(diff7.0-libssh                          00)
test_csdiff(diff7.0-icu                             00)
test_csdiff(diff7.0-virtuoso-opensource             00)
test_csdiff(diff5.8-kernel                          00)
test_csdiff(diff6.4-iok                             00)
test_csdiff(diff6.4-rpm                             00)
test_csdiff(diff6.4-ksh                             00)
test_csdiff(diff6.4-samba4                          00)
test_csdiff(diff6.4-papi                            00)
test_csdiff(diff6.4-kernel                          00)
