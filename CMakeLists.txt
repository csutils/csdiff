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
add_definitions(-Wall -Wextra -fPIC)

# read PYTHON_INCLUDE_PATH (rnamed to PYTHON_INCLUDE_DIRS in CMake 2.8)
find_package(PythonLibs)
message(STATUS "PYTHON_INCLUDE_PATH: ${PYTHON_INCLUDE_PATH}")

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
find_package(Boost 1.41)
if(Boost_FOUND)
    # boost >= 1.41 ... use everything from system
    set(boost_incs_tmp ${Boost_INCLUDE_DIRS})
else()
    # boost < 1.41 ... use local overrides
    find_package(Boost 1.33 REQUIRED)
    message(STATUS "WARNING: System Boost libraries are tool old, using local!")
    set(boost_incs_tmp ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_34_1
        ${CMAKE_CURRENT_SOURCE_DIR}/boost_1_41_0)
endif()
set(BOOST_INCS ${boost_incs_tmp} CACHE STRING "boost include directories")
include_directories(SYSTEM ${BOOST_INCS})
link_directories(${Boost_LIBRARY_DIRS})

# cslib.a
add_library(cs STATIC
    abstract-filter.cc
    abstract-parser.cc
    abstract-writer.cc
    csdiff-core.cc
    csfilter.cc
    csparser.cc
    cswriter.cc
    cwe-mapper.cc
    deflookup.cc
    defqueue.cc
    gcc-parser.cc
    html-writer.cc
    instream.cc
    json-parser.cc
    json-writer.cc
    version.cc
    ${flex_scanner}
)

# link cslib.a and boost libraries
link_libraries(cs boost_regex boost_program_options)

# the list of executables
add_executable(csannot      csannot.cc)
add_executable(csdiff       csdiff.cc)
add_executable(csgrep       csgrep.cc)
add_executable(cshtml       cshtml.cc)
add_executable(cslinker     cslinker.cc)
add_executable(cssort       cssort.cc)

# load regression tests
add_subdirectory(tests)

# declare what 'make install' should install
install(TARGETS
    csannot
    csdiff
    csgrep
    cshtml
    cslinker
    cssort
    DESTINATION bin)

# pycsdiff - python binding of csdiff [experimental]
if (EXISTS "${PYTHON_INCLUDE_PATH}/pyconfig.h")
    find_library(BOOST_PYTHON boost_python PATHS /usr/lib /usr/lib64)
    if (BOOST_PYTHON)
        message(STATUS "WARNING: The python binding of csdiff is experimental!")
        add_library(pycsdiff SHARED pycsdiff.cc)
        set_target_properties(pycsdiff PROPERTIES
            COMPILE_FLAGS "-I${PYTHON_INCLUDE_PATH}")
        target_link_libraries(pycsdiff boost_python)
        install(TARGETS pycsdiff DESTINATION lib)
    endif()
endif()

# macro to generate a man page from the corresponding binary
macro(create_manpage BINARY)
    add_custom_command(TARGET ${BINARY} POST_BUILD
        COMMAND ${HELP2MAN} --no-info --section 1
            ${CMAKE_CURRENT_BINARY_DIR}/${BINARY}
            | gzip > ${BINARY}.1.gz
        COMMENT "Generating ${BINARY} man page"
        VERBATIM)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BINARY}.1.gz
        DESTINATION share/man/man1)
endmacro(create_manpage)

# generate man pages using help2man if available
find_program(HELP2MAN help2man)
if(HELP2MAN)
    create_manpage(csdiff)
    create_manpage(csgrep)
    create_manpage(cshtml)
    create_manpage(cslinker)
    create_manpage(cssort)
endif()
