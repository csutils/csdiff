/*
 * Copyright (C) 2011-2022 Red Hat, Inc.
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

#include "abstract-filter.hh"

#include <vector>

// /////////////////////////////////////////////////////////////////////////////
// implementation of PredicateFilter

struct PredicateFilter::Private {
    using IPredicatePtr = std::unique_ptr<IPredicate>;
    using TList         = std::vector<IPredicatePtr>;

    bool                invertEach_ = false;
    TList               preds_;

    Private() = default;
};

PredicateFilter::PredicateFilter(AbstractWriter *agent):
    AbstractFilter(agent),
    d(new Private)
{
}

PredicateFilter::~PredicateFilter() = default;

void PredicateFilter::append(IPredicate *pred)
{
    d->preds_.emplace_back(pred);
}

void PredicateFilter::setInvertEachMatch(bool enabled)
{
    d->invertEach_ = enabled;
}

bool PredicateFilter::matchDef(const Defect &def)
{
    const bool neg = d->invertEach_;

    for (const auto &pred : d->preds_) {
        if (neg == pred->matchDef(def))
            return false;
    }

    return true;
}
