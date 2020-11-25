# Copyright (C) 2011 - 2020 Red Hat, Inc.
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

# a generic template for cssort test-cases
macro(test_cssort dir num)
    set(tst "${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${num}")

    set(cmd "${cssort} --key=checker ${tst}-input.err 2>/dev/null")
    set(cmd "${cmd} | ${jsfilter} | ${diffcmd} ${tst}-by-checker.err -")
    add_test_wrap("${dir}-${num}-by-checker" "${cmd}")

    set(cmd "${cssort} --key=path ${tst}-input.err 2>/dev/null")
    set(cmd "${cmd} | ${jsfilter} | ${diffcmd} ${tst}-by-path.err -")
    add_test_wrap("${dir}-${num}-by-path" "${cmd}")
endmacro()

# cssort tests
test_cssort(cssort-5.8                              00)
test_cssort(cssort-5.8                              01)
test_cssort(cssort-5.8                              02)
test_cssort(cssort-5.8                              03)
test_cssort(cssort-misc                             00)
