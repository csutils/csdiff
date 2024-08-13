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

# common setup for all tests
set(csdiff      "${CMAKE_BINARY_DIR}/src/csdiff")
set(csgrep      "${CMAKE_BINARY_DIR}/src/csgrep")
set(cshtml      "${CMAKE_BINARY_DIR}/src/cshtml")
set(cslinker    "${CMAKE_BINARY_DIR}/src/cslinker")
set(cssort      "${CMAKE_BINARY_DIR}/src/cssort")
set(csjson      "${csgrep} --mode=json")
set(diffcmd     "diff -up")

# eliminate csdiff's version string in the output
set(jsfilter "sed -e 's|\"version\": \"[^\"]*\"|\"version\": \"\"|g'")
set(jsfilter "${jsfilter} -e 's|${CMAKE_SOURCE_DIR}/tests/csfilter-kfp/|\$PROJECT_ROOT/tests/csfilter-kfp/|'")

macro(add_test_wrap test_name cmd)
    add_test("${test_name}" bash -c "${cmd}")
    set_tests_properties(${test_name} PROPERTIES ENVIRONMENT
        "PATH=${CMAKE_BINARY_DIR}/src:$ENV{PATH};PROJECT_ROOT=${CMAKE_SOURCE_DIR}")

    set_tests_properties(${test_name} PROPERTIES COST ${test_cost})
    math(EXPR test_cost "${test_cost} - 1")

    # print whole stacktrace for UBSAN reports
    if(SANITIZERS)
        set_property(TEST ${test_name} APPEND PROPERTY
                     ENVIRONMENT UBSAN_OPTIONS="print_stacktrace=1")
    endif()
endmacro()

set(test_cost 1048576)

add_subdirectory(csdiff)
add_subdirectory(csfilter-kfp)
add_subdirectory(csgrep)
add_subdirectory(cshtml)
add_subdirectory(cslinker)
add_subdirectory(cssort)
add_subdirectory(cstrans-df-run)
