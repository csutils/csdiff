# Copyright (C) 2021 Red Hat, Inc.
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

# a generic template for a csdiff test-case
macro(test_csdiff num)
    set(tst "${CMAKE_CURRENT_SOURCE_DIR}/${num}")

    set(cmd "${csdiff} -cf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("filter-file-${num}-added" "${cmd}")

    set(cmd "${csdiff} -xf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("filter-file-${num}-fixed" "${cmd}")

    set(cmd "${csdiff} -zf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add-z.err -")
    add_test_wrap("filter-file-${num}-added-with-z" "${cmd}")

    set(cmd "${csdiff} -xzf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csjson} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix-z.err -")
    add_test_wrap("filter-file-${num}-fixed-with-z" "${cmd}")

    set(cmd "${csdiff} -cf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${diffcmd} ${tst}-add.err -")
    add_test_wrap("filter-file-${num}-added-with-c" "${cmd}")

    set(cmd "${csdiff} -jxf ${tst}-filter.json ${tst}-old.err ${tst}-new.err")
    set(cmd "${cmd} | ${csgrep}")
    set(cmd "${cmd} | ${diffcmd} ${tst}-fix.err -")
    add_test_wrap("filter-file-${num}-fixed-with-j" "${cmd}")
endmacro()

test_csdiff(01-basic)
test_csdiff(02-checker-regex)
