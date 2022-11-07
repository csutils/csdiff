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

# enable sanitizers
option(SANITIZERS "Compile with ASan and UBSan" OFF)
if(SANITIZERS)
    # enable ASan and UBSan
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
    # recommended for better error traces
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    # make UBSan reports fatal
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=all")
endif()

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
    abstract-writer.cc
    color.cc
    csdiff-core.cc
    csfilter.cc
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
    parser.cc
    parser-common.cc
    parser-cov.cc
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
include(GNUInstallDirs)
install(TARGETS
    csdiff
    csgrep
    cshtml
    cslinker
    cssort
    cstrans-df-run
    DESTINATION ${CMAKE_INSTALL_BINDIR})

# pycsdiff - python binding of csdiff
option(PYCSDIFF_PYTHON2 "Set to ON to build pycsdiff for Python 2" OFF)
option(PYCSDIFF_PYTHON3 "Set to ON to build pycsdiff for Python 3" ON)

macro(build_pycsdiff version boost_python_lib_names)
    # check for Python libs (e.g. python${version}-devel on Fedora)
    # Interpreter is required for Python_SITEARCH
    find_package(Python${version} COMPONENTS Development Interpreter)
    if(NOT Python${version}_FOUND)
        message(FATAL_ERROR
            "The pycsdiff module for Python ${version} will NOT be built!")
    endif()

    # find boost_python
    find_library(BOOST_PYTHON${version}
        NAMES ${boost_python_lib_names}
        HINTS ${Boost_LIBRARY_DIRS})
    if(BOOST_PYTHON${version})
        message(STATUS "Found libboost_python: ${BOOST_PYTHON${version}}")
    else()
        message(FATAL_ERROR "libboost_python for Python ${version} NOT FOUND!")
    endif()

    message(STATUS "Python ${version} binding enabled. "
        "The pycsdiff module will be built!")

    add_library(pycsdiff_py${version} SHARED pycsdiff.cc)
    target_include_directories(pycsdiff_py${version} SYSTEM
        PRIVATE ${Python${version}_INCLUDE_DIRS})
    target_link_libraries(pycsdiff_py${version} PRIVATE ${BOOST_PYTHON${version}})

    # set correct name so that `python -c 'import pycsdiff' works`
    set_target_properties(pycsdiff_py${version} PROPERTIES
        PREFIX ""
        OUTPUT_NAME "pycsdiff"
        # to avoid overwrites with multiple Python versions
        LIBRARY_OUTPUT_DIRECTORY "pycsdiff_py${version}")

    install(TARGETS pycsdiff_py${version}
            DESTINATION ${Python${version}_SITEARCH})

    # TODO: support running pycsdiff with sanitizers
    if(NOT SANITIZERS)
        # assert that the library is usable
        add_test(NAME "pycsdiff_py${version}"
            COMMAND ${Python${version}_EXECUTABLE} -c "import pycsdiff"
            WORKING_DIRECTORY $<TARGET_FILE_DIR:pycsdiff_py${version}>)
    endif()
endmacro()

if(PYCSDIFF_PYTHON2)
    # boost_python has no suffix
    set(BOOST_PYTHON_LIB_NAMES
        boost_python)

    build_pycsdiff(2 "${BOOST_PYTHON_LIB_NAMES}")
endif()

if(PYCSDIFF_PYTHON3)
    # boost_python3 is used on RHEL-8.
    # boost_python310 is used on Fedora 35.
    set(BOOST_PYTHON_LIB_NAMES
        boost_python311
        boost_python310
        boost_python39
        boost_python38
        boost_python37
        boost_python36
        boost_python3)

    build_pycsdiff(3 "${BOOST_PYTHON_LIB_NAMES}")
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
            DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
endmacro(create_manpage)

# generate man pages using help2man if available
find_program(HELP2MAN help2man)
if(HELP2MAN)
    message(STATUS "help2man found - ${HELP2MAN}")

    create_manpage(csdiff)
    create_manpage(csgrep)
    create_manpage(cshtml)
    create_manpage(cslinker)
    create_manpage(cssort)
    create_manpage(cstrans-df-run)
else()
    message(STATUS "help2man not found - documentation will NOT be built")
endif()
