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
set(Boost_VERBOSE TRUE)
find_package(Boost CONFIG REQUIRED
    COMPONENTS filesystem
               program_options
               regex
               system
    OPTIONAL_COMPONENTS json
                        nowide)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

if(Boost_VERSION_STRING VERSION_LESS 1.75)
    message(WARNING "System Boost libraries are too old (1.75+ recommended)."
        " Using local version of Boost.Nowide and Boost.JSON!")
    include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/boost_1_75_0)
endif()

# cslib.a
add_subdirectory(lib)
include_directories(lib)

# the list of executables
add_executable(csdiff       csdiff.cc)
add_executable(csgrep       csgrep.cc)
add_executable(cshtml       cshtml.cc)
add_executable(cslinker     cslinker.cc)
add_executable(cssort       cssort.cc)
add_executable(cstrans-df-run cstrans-df-run.cc)

# link cslib.a and boost libraries
foreach(tgt csdiff csgrep cshtml cslinker cssort cstrans-df-run)
    target_link_libraries(${tgt} cs
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_PROGRAM_OPTIONS_LIBRARY}
        ${Boost_REGEX_LIBRARY})
endforeach()

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

# install the csfilter-kfp script
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/csfilter-kfp
    ${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp
    @ONLY)
install(PROGRAMS
    ${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp
    DESTINATION ${CMAKE_INSTALL_BINDIR})

# optionally build statically linked csgrep-static
option(CSGREP_STATIC "Set to ON to build the csgrep-static executable" OFF)
if(CSGREP_STATIC)
    add_executable(csgrep-static csgrep.cc)
    target_link_options(csgrep-static PRIVATE "-static")

    # FIXME: do not hardcode paths to boost static libs
    target_link_libraries(csgrep-static cs
        /usr/lib64/libboost_filesystem.a
        /usr/lib64/libboost_program_options.a
        /usr/lib64/libboost_regex.a)

    install(TARGETS csgrep-static
        DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})
endif()

# pycsdiff - python binding of csdiff
option(PYCSDIFF_PYTHON2 "Set to ON to build pycsdiff for Python 2" OFF)
option(PYCSDIFF_PYTHON3 "Set to ON to build pycsdiff for Python 3" ON)

macro(build_pycsdiff version)
    # make FindPython use system Python version
    # https://gitlab.kitware.com/cmake/cmake/-/merge_requests/8287
    set(Python${version}_FIND_UNVERSIONED_NAMES FIRST)

    # check for Python libs (e.g. python${version}-devel on Fedora)
    # Interpreter is required for Python_SITEARCH
    find_package(Python${version} COMPONENTS Development Interpreter)
    if(NOT Python${version}_FOUND)
        message(FATAL_ERROR
            "The pycsdiff module for Python ${version} will NOT be built!")
    endif()

    # find boost_python${version}
    set(PYTHON_VERSION_SUFFIX "${version}${Python${version}_VERSION_MINOR}")
    find_package(Boost CONFIG REQUIRED COMPONENTS python${PYTHON_VERSION_SUFFIX})
    message(STATUS "Python ${version} binding enabled. "
        "The pycsdiff module will be built!")

    add_library(pycsdiff_py${version} MODULE pycsdiff.cc)
    target_link_libraries(pycsdiff_py${version}
        PRIVATE cs
                ${Boost_FILESYSTEM_LIBRARY}
                ${Boost_REGEX_LIBRARY}
                ${Boost_PYTHON${PYTHON_VERSION_SUFFIX}_LIBRARY}
                Python${version}::Module)

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
    build_pycsdiff(2)
endif()

if(PYCSDIFF_PYTHON3)
    build_pycsdiff(3)
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

    # create/install the csfilter-kfp.1 man page
    add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp.1"
        COMMAND env LC_ALL=C ${HELP2MAN} --no-info --section 1
            --include "${CMAKE_SOURCE_DIR}/doc/csfilter-kfp.h2m"
            ${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp
            > csfilter-kfp.1 || rm -f csfilter-kfp.1
        COMMENT "Generating csfilter-kfp man page"
        VERBATIM)
    add_custom_target(csfilter-kfp.1 ALL DEPENDS
        "${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp.1")
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/csfilter-kfp.1
            DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
else()
    message(STATUS "help2man not found - documentation will NOT be built")
endif()
