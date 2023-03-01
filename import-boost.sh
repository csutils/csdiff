#!/usr/bin/env bash
export MIRROR="http://sourceforge.net/projects/boost/files"

import_from()
{
    ver="$1"
    shift
    curl -L "${MIRROR}/boost/${ver}/boost_${ver//./_}.tar.bz2/download" \
        | bzip2 -cd                                                     \
        | tar -xv "$@"
}

import_from 1.75.0                                                      \
    boost_1_75_0/LICENSE_1_0.txt                                        \
    boost_1_75_0/boost/nowide/config.hpp                                \
    boost_1_75_0/boost/nowide/replacement.hpp                           \
    boost_1_75_0/boost/nowide/utf/convert.hpp                           \
    boost_1_75_0/boost/nowide/utf/utf.hpp                               \
    boost_1_75_0/boost/json                                             \
    boost_1_75_0/boost/json.hpp
