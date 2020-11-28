# Copyright (C) 2020 Red Hat, Inc.
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

# go through all subdirs
file(GLOB test_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS *)
foreach(test ${test_list})
    set(test_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/${test})
    set(test_script ${test_src_dir}/runtest.sh)
    if(EXISTS ${test_script})
        # create a working directory for the test-case
        set(test_dst_dir ${CMAKE_CURRENT_BINARY_DIR}/${test})
        file(MAKE_DIRECTORY ${test_dst_dir})

        # append a single test-case
        add_test(
            NAME "cshtml/${test}"
            COMMAND env
                "TEST_SRC_DIR=${test_src_dir}"
                "CSHTML_BIN=${cshtml}"
                ${test_script}
            WORKING_DIRECTORY ${test_dst_dir})
    endif()
endforeach()
