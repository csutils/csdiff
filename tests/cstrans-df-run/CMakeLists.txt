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

# a generic template for cstrans-df-run tests
macro(tests_cstrans_df_run tst)
    set(test_data_prefix "${CMAKE_CURRENT_SOURCE_DIR}/${tst}")
    set(cmd "${CMAKE_BINARY_DIR}/src/cstrans-df-run")
    set(cmd "${cmd} -- /opt/cov-sa-2019.09/bin/cov-build --dir=/cov --append-log")
    set(cmd "${cmd} <${test_data_prefix}-stdin.txt")
    set(cmd "${cmd} | ${diffcmd} ${test_data_prefix}-stdout.txt -")
    add_test_wrap("cstrans-df-run-${tst}" "${cmd}")
endmacro()

# cstrans-df-run tests
tests_cstrans_df_run(0001)
tests_cstrans_df_run(0002)
tests_cstrans_df_run(0003)
tests_cstrans_df_run(0004)
tests_cstrans_df_run(0005)
tests_cstrans_df_run(0006)
tests_cstrans_df_run(0007)
tests_cstrans_df_run(0008)
tests_cstrans_df_run(0009)
tests_cstrans_df_run(0010)
tests_cstrans_df_run(0011)
