# Copyright (C) 2024 Red Hat, Inc.
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

# a generic template for csfilter-kpf tests
macro(test_csfilter_kfp tst)
    set(test_data_prefix "${CMAKE_CURRENT_SOURCE_DIR}/${tst}")
    set(cmd "set -o pipefail && ${CMAKE_SOURCE_DIR}/src/csfilter-kfp")
    file(READ ${test_data_prefix}-args.txt args)
    string(REPLACE "\n" "" args "${args}")
    set(cmd "${cmd} ${args}")
    if(EXISTS "${test_data_prefix}-stdin.txt")
        set(cmd "${cmd} <${test_data_prefix}-stdin.txt")
    endif()
    set(cmd "${cmd} | ${jsfilter} | ${diffcmd} ${test_data_prefix}-stdout.txt -")
    add_test_wrap("csfilter-kfp-${tst}" "${cmd}")
endmacro()

# use a glob search to add all tests
file(GLOB test_args RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *-args.txt)
foreach(args ${test_args})
    string(REGEX REPLACE "-args.txt$" "" test "${args}")
    test_csfilter_kfp(${test})
endforeach()
