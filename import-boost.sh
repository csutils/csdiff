#!/bin/bash
export MIRROR="http://sourceforge.net/projects/boost/files"

import_from()
{
    ver="$1"
    shift
    curl -L "${MIRROR}/boost/${ver}/boost_${ver//./_}.tar.bz2/download" \
        | bzip2 -cd                                                     \
        | tar -xv "$@"
}

import_from 1.34.1                                                      \
    boost_1_34_1/LICENSE_1_0.txt                                        \
    boost_1_34_1/boost/algorithm/string/std/slist_traits.hpp            \
    boost_1_34_1/boost/foreach.hpp                                      \
    boost_1_34_1/boost/iostreams/filter/regex.hpp

import_from 1.41.0                                      \
    boost_1_41_0/LICENSE_1_0.txt                        \
    boost_1_41_0/boost/config/                          \
    boost_1_41_0/boost/optional/                        \
    boost_1_41_0/boost/property_tree/                   \
    boost_1_41_0/boost/spirit/include/classic.hpp       \
    boost_1_41_0/boost/spirit/home/classic.hpp          \
    boost_1_41_0/boost/spirit/home/classic/

sed 's/fmt_flags_(fmt_flags_)/fmt_flags_(fmt_flags)/'   \
    -i boost_1_34_1/boost/iostreams/filter/regex.hpp
