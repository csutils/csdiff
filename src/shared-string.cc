/*
 * Copyright (C) 2018 Red Hat, Inc.
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

#include "shared-string.hh"

#include <sstream>

SharedStr::TStor SharedStr::stor_;

SharedStr::SharedStr():
    iter_(stor_.end())
{
}

void SharedStr::swap(SharedStr &ref)
{
    std::swap(iter_, ref.iter_);
}

void SharedStr::hashStr(const std::string &str)
{
    iter_ = stor_.insert(str).first;
}

SharedStr::SharedStr(const int i)
{
    std::ostringstream ss;
    ss << i;
    this->hashStr(ss.str());
}

SharedStr::SharedStr(const std::string &str)
{
    this->hashStr(str);
}

void SharedStr::writeOut(std::string *pDst) const
{
    if (stor_.end() == iter_)
        pDst->clear();
    else
        *pDst = *iter_;
}
