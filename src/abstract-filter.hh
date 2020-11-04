/*
 * Copyright (C) 2011 Red Hat, Inc.
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

#ifndef H_GUARD_ABSTRACT_FILTER_H
#define H_GUARD_ABSTRACT_FILTER_H

#include "abstract-writer.hh"

/// decorator
class GenericAbstractFilter: public AbstractWriter {
    protected:
        AbstractWriter *agent_;
        virtual void handleDef(const Defect &def) = 0;

    public:
        virtual void notifyFile(const std::string &fileName) {
            agent_->notifyFile(fileName);
        }

        GenericAbstractFilter(AbstractWriter *agent):
            agent_(agent)
        {
        }

        ~GenericAbstractFilter() {
            delete agent_;
        }

        virtual void flush() {
            agent_->flush();
        }

        virtual const TScanProps& getScanProps() const {
            return agent_->getScanProps();
        }

        virtual void setScanProps(const TScanProps &scanProps) {
            agent_->setScanProps(scanProps);
        }
};

/// decorator
class EventPrunner: public GenericAbstractFilter {
    private:
        int thr_;

    public:
        EventPrunner(AbstractWriter *agent, unsigned thr):
            GenericAbstractFilter(agent),
            thr_(thr)
        {
        }

        virtual void handleDef(const Defect &defOrig);
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

        virtual void handleDef(const Defect &defOrig);
};

/// decorator
class AbstractFilter: public GenericAbstractFilter {
    private:
        bool neg_;

    protected:
        virtual bool matchDef(const Defect &def) = 0;

    public:
        AbstractFilter(AbstractWriter *agent):
            GenericAbstractFilter(agent),
            neg_(false)
        {
        }

        void setInvertMatch(bool enabled = true) {
            neg_ = enabled;
        }

        virtual void handleDef(const Defect &def) {
            if (neg_ == matchDef(def))
                return;

            agent_->handleDef(def);
        }
};

class IPredicate {
    public:
        virtual ~IPredicate() { }
        virtual bool matchDef(const Defect &def) const = 0;
};

class PredicateFilter: public AbstractFilter {
    public:
        PredicateFilter(AbstractWriter *agent);
        virtual ~PredicateFilter();

        /// takes ownership of pred and will call delete on it on destruction
        void append(IPredicate *);

        void setInvertEachMatch(bool enabled = true);

    protected:
        virtual bool matchDef(const Defect &def);

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_ABSTRACT_FILTER_H */
