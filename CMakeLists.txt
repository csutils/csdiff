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

cmake_minimum_required(VERSION 2.6)
project(csdiff CXX)
enable_testing()
add_definitions(-Wall -Wextra)

# we keep a local instance of FindFLEX.cmake (it was introduced in CMake 2.8)
include(cmake-modules-2.8/CMakeParseArguments.cmake)
include(cmake-modules-2.8/FindPackageHandleStandardArgs.cmake)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules-2.8)

# Flex
find_package(FLEX REQUIRED)
set(flex_scanner ${CMAKE_CURRENT_BINARY_DIR}/csparser.yy.cc)
flex_target(csparser csparser.lex ${flex_scanner})
add_definitions(-iquote ${CMAKE_CURRENT_SOURCE_DIR})

# Boost libraries
find_package(Boost 1.41 REQUIRED)
link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

# cslib.a
add_library(cs STATIC
    abstract-filter.cc
    csfilter.cc
    csparser.cc
    cstat-core.cc
    deflookup.cc
    instream.cc
    json-writer.cc
    ${flex_scanner}
)

# link cslib.a and boost libraries
link_libraries(cs boost_regex boost_program_options)

# the list of executables
add_executable(csannot csannot.cc)
add_executable(csdiff csdiff.cc)
add_executable(csgrep csgrep.cc)
add_executable(cstat cstat.cc)
add_executable(linkify linkify.cc)

# load regression tests
add_subdirectory(tests)
