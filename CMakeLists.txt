# Copyright (C) 2011 - 2014 Red Hat, Inc.
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

cmake_minimum_required(VERSION 2.8)
project(csdiff CXX)
enable_testing()
add_definitions(-Wall -Wextra -fPIC)

# cslib.a
add_library(cs STATIC
    abstract-filter.cc
    abstract-parser.cc
    abstract-writer.cc
    color.cc
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
)

# link cslib.a and boost libraries
find_library(BOOST_REGEX                boost_regex                 REQUIRED)
find_library(BOOST_PROGRAM_OPTIONS      boost_program_options       REQUIRED)
link_libraries(cs
    boost_regex
    boost_program_options)

# the list of executables
add_executable(csdiff       csdiff.cc)
add_executable(csgrep       csgrep.cc)
add_executable(cshtml       cshtml.cc)
add_executable(cslinker     cslinker.cc)
add_executable(cssort       cssort.cc)

# load regression tests
add_subdirectory(tests)

# declare what 'make install' should install
install(TARGETS
    csdiff
    csgrep
    cshtml
    cslinker
    cssort
    DESTINATION bin)

# pycsdiff - python binding of csdiff
option(BUILD_PYCSDIFF "Set to ON to enable python binding" ON)
if (BUILD_PYCSDIFF)
    find_library(BOOST_PYTHON boost_python REQUIRED)

    # query PYTHON_INCLUDE_DIRS
    find_package(PythonInterp REQUIRED)
    find_package(PythonLibs   REQUIRED)
    message(STATUS "PYTHON_INCLUDE_DIRS: ${PYTHON_INCLUDE_DIRS}")
    if(NOT EXISTS "${PYTHON_INCLUDE_DIRS}/pyconfig.h")
        message(FATAL_ERROR "
${PYTHON_INCLUDE_DIRS}/pyconfig.h does not exits")
    endif()

    # query PYTHON_SITEARCH
    execute_process(COMMAND ${PYTHON_EXECUTABLE}
        -c "from distutils.sysconfig import get_python_lib
print(get_python_lib(1))"
        RESULT_VARIABLE PYTHON_SITEARCH_STATUS
        OUTPUT_VARIABLE PYTHON_SITEARCH
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if("${PYTHON_SITEARCH_STATUS}" EQUAL 0)
        message(STATUS "PYTHON_SITEARCH: ${PYTHON_SITEARCH}")
    else()
        message(FATAL_ERROR "
failed to query PYTHON_SITEARCH")
    endif()

    message(STATUS "python binding enabled, the pycsdiff module will be built!")
    add_library(pycsdiff SHARED pycsdiff.cc)
    set_target_properties(pycsdiff PROPERTIES
        COMPILE_FLAGS "-I${PYTHON_INCLUDE_DIRS}"
        PREFIX "")
    target_link_libraries(pycsdiff boost_python)
    install(TARGETS pycsdiff DESTINATION ${PYTHON_SITEARCH})
endif()

# macro to generate a man page from the corresponding binary
macro(create_manpage BINARY)
    add_custom_command(TARGET ${BINARY} POST_BUILD
        COMMAND ${HELP2MAN} --no-info --section 1
            ${CMAKE_CURRENT_BINARY_DIR}/${BINARY}
            > ${BINARY}.1
        COMMENT "Generating ${BINARY} man page"
        VERBATIM)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BINARY}.1
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
