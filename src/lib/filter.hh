/*
 * Copyright (C) 2011-2023 Red Hat, Inc.
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

#ifndef H_GUARD_FILTER_H
#define H_GUARD_FILTER_H

#include "abstract-filter.hh"

/// decorator
class EventPrunner: public GenericAbstractFilter {
    private:
        int thr_;

    public:
        EventPrunner(AbstractWriter *agent, int thr):
            GenericAbstractFilter(agent),
            thr_(thr)
        {
        }

        void handleDef(const Defect &defOrig) override;
};

/// decorator
class CtxEmbedder: public GenericAbstractFilter {
    private:
        int ctxLines_;

    public:
        CtxEmbedder(AbstractWriter *agent, const int ctxLines):
            GenericAbstractFilter(agent),
            ctxLines_(ctxLines)
        {
        }

        void handleDef(const Defect &defOrig) override;
};

#endif /* H_GUARD_FILTER_H */
