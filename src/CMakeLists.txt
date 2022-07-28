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
message(STATUS "User-provided flags: ${CMAKE_CXX_FLAGS}")

# set standards
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find Boost
find_package(Boost REQUIRED
    COMPONENTS filesystem
               program_options
               regex
               system)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(Boost_VERSION_STRING VERSION_LESS 1.74)
    message(WARNING "System Boost libraries are too old (1.74+ recommended)."
        " Using local version of Boost.Nowide!")
    include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/boost_1_74_0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D'BOOST_LIKELY(x)=__builtin_expect(x, 1)'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D'BOOST_UNLIKELY(x)=__builtin_expect(x, 0)'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D'BOOST_FALLTHROUGH='")
endif()

# eliminate the following warning:
#   /usr/include/boost/bind.hpp:36:1: note: ‘#pragma message: The practice
#   of declaring the Bind placeholders (_1, _2, ...) in the global namespace
#   is deprecated. Please use <boost/bind/bind.hpp> + using namespace
#   boost::placeholders, or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain
#   the current behavior.’
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

# cslib.a
add_library(cs STATIC
    abstract-filter.cc
    abstract-parser.cc
    abstract-writer.cc
    color.cc
    csdiff-core.cc
    csfilter.cc
    csparser.cc
    csv-parser.cc
    cswriter.cc
    cwe-mapper.cc
    cwe-name-lookup.cc
    deflookup.cc
    gcc-parser.cc
    html-writer.cc
    instream.cc
    json-parser.cc
    json-writer.cc
    parser-common.cc
    shared-string.cc
    version.cc
    xml-parser.cc
)

# link cslib.a and boost libraries
link_libraries(cs
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_REGEX_LIBRARY})

# the list of executables
add_executable(csdiff       csdiff.cc)
add_executable(csgrep       csgrep.cc)
add_executable(cshtml       cshtml.cc)
add_executable(cslinker     cslinker.cc)
add_executable(cssort       cssort.cc)
target_link_libraries(cshtml
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})

# experimental
add_executable(cstrans-df-run cstrans-df-run.cc)
target_link_libraries(cstrans-df-run
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})

# declare what 'make install' should install
install(TARGETS
    csdiff
    csgrep
    cshtml
    cslinker
    cssort
    cstrans-df-run
    DESTINATION bin)

# check for python libs (e.g. python3-devel on Fedora)
find_package(PythonLibs)
if ("${PYTHON_LIBRARY}" STREQUAL "PYTHON_LIBRARY-NOTFOUND")
    set(BUILD_PYCSDIFF_DEFAULT OFF)
else()
    set(BUILD_PYCSDIFF_DEFAULT ON)
endif()

# pycsdiff - python binding of csdiff
option(BUILD_PYCSDIFF "Set to ON to enable python binding"
    ${BUILD_PYCSDIFF_DEFAULT})
if (BUILD_PYCSDIFF)
    set(BOOST_PYTHON_LIB_NAME "boost_python"
        CACHE STRING "Name of the boost_python library")

    # query PYTHON_SITEARCH
    find_package(PythonInterp REQUIRED)
    execute_process(COMMAND ${PYTHON_EXECUTABLE}
        -c "import sysconfig; print(sysconfig.get_paths()['platlib'])"
        RESULT_VARIABLE PYTHON_SITEARCH_STATUS
        OUTPUT_VARIABLE PYTHON_SITEARCH
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if("${PYTHON_SITEARCH_STATUS}" EQUAL 0)
        message(STATUS "PYTHON_SITEARCH: ${PYTHON_SITEARCH}")
    else()
        message(FATAL_ERROR "
failed to query PYTHON_SITEARCH")
    endif()

    # boost_python3 is used on RHEL-8.
    # boost_python310 is used on Fedora 35.
    find_library(BOOST_PYTHON NAMES ${BOOST_PYTHON_LIB_NAME}
        boost_python311
        boost_python310
        boost_python39
        boost_python38
        boost_python37
        boost_python36
        boost_python3
        HINTS ${Boost_LIBRARY_DIRS})

    message(STATUS "BOOST_PYTHON: ${BOOST_PYTHON}")

    # verify PYTHON_LIBRARY
    if ("${PYTHON_LIBRARY}" STREQUAL "PYTHON_LIBRARY-NOTFOUND")
        message(FATAL_ERROR "
python libraries not found, unable to build pycsdiff")
    endif()

    # verify PYTHON_INCLUDE_DIR
    message(STATUS "PYTHON_INCLUDE_DIR: ${PYTHON_INCLUDE_DIR}")
    if(NOT EXISTS "${PYTHON_INCLUDE_DIR}/pyconfig.h")
        message(FATAL_ERROR "
${PYTHON_INCLUDE_DIR}/pyconfig.h does not exits")
    endif()

    message(STATUS "python binding enabled, the pycsdiff module will be built!")
    add_library(pycsdiff SHARED pycsdiff.cc)
    set_target_properties(pycsdiff PROPERTIES
        COMPILE_FLAGS "-I${PYTHON_INCLUDE_DIR}"
        PREFIX "")
    target_link_libraries(pycsdiff ${BOOST_PYTHON})
    install(TARGETS pycsdiff
        DESTINATION ${PYTHON_SITEARCH}
        COMPONENT pycsdiff)
    add_custom_target(install-pycsdiff
        COMMAND ${CMAKE_COMMAND} -DCOMPONENT=pycsdiff
        -P ${CMAKE_BINARY_DIR}/cmake_install.cmake)
endif()

# macro to generate a man page from the corresponding binary
macro(create_manpage BINARY)
    set(H2M_INCLUDE "${CMAKE_SOURCE_DIR}/doc/${BINARY}.h2m")
    if(EXISTS "${H2M_INCLUDE}")
        set(H2M_ARGS --include ${H2M_INCLUDE})
    else()
        set(H2M_ARGS "")
    endif()
    add_custom_command(TARGET ${BINARY} POST_BUILD
        COMMAND env LC_ALL=C ${HELP2MAN} --no-info --section 1 ${H2M_ARGS}
            ${CMAKE_CURRENT_BINARY_DIR}/${BINARY}
            > ${BINARY}.1 || rm -f ${BINARY}.1
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
    create_manpage(cstrans-df-run)
endif()
