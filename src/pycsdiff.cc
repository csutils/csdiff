/*
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This file is part of csdiff.
 *
 * csdiff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * csdiff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with csdiff.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "csdiff-core.hh"
#include "csfilter.hh"
#include "version.hh"

#include <sstream>

// eliminate the following warning:
//   /usr/include/boost/bind.hpp:36:1: note: ‘#pragma message: The practice
//   of declaring the Bind placeholders (_1, _2, ...) in the global namespace
//   is deprecated. Please use <boost/bind/bind.hpp> + using namespace
//   boost::placeholders, or define BOOST_BIND_GLOBAL_PLACEHOLDERS to retain
//   the current behavior.’
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/python.hpp>

std::string diff_scans(
        const std::string          &oldScan,
        const std::string          &newScan)
{
    std::istringstream strOld(oldScan);
    std::istringstream strNew(newScan);
    std::ostringstream strDst;

    InStream inOld(strOld, /* silent */ true);
    InStream inNew(strNew, /* silent */ true);

    // FIXME: we need a better API to configure this
    MsgFilter::inst()->setIgnorePath(true);

    (void) diffScans(strDst, inOld, inNew);
    return strDst.str();
}

std::string get_version(void)
{
    return CS_VERSION;
}

BOOST_PYTHON_MODULE(pycsdiff)
{
    boost::python::def("diff_scans",        diff_scans);
    boost::python::def("get_version",       get_version);
}
