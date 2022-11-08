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

#ifndef H_GUARD_ABSTRACT_FILTER_H
#define H_GUARD_ABSTRACT_FILTER_H

#include "writer.hh"

#include <memory>

/// decorator
class GenericAbstractFilter: public AbstractWriter {
    protected:
        std::unique_ptr<AbstractWriter> agent_;

    public:
        void notifyFile(const std::string &fileName) override {
            agent_->notifyFile(fileName);
        }

        GenericAbstractFilter(AbstractWriter *agent):
            agent_(agent)
        {
        }

        ~GenericAbstractFilter() override = default;

        void handleDef(const Defect &def) override {
            agent_->handleDef(def);
        }

        void flush() override {
            agent_->flush();
        }

        const TScanProps& getScanProps() const override {
            return agent_->getScanProps();
        }

        void setScanProps(const TScanProps &scanProps) override {
            agent_->setScanProps(scanProps);
        }
};

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

/// decorator
class AbstractFilter: public GenericAbstractFilter {
    private:
        bool neg_ = false;

    protected:
        virtual bool matchDef(const Defect &def) = 0;

    public:
        AbstractFilter(AbstractWriter *agent):
            GenericAbstractFilter(agent)
        {
        }

        void setInvertMatch(bool enabled = true) {
            neg_ = enabled;
        }

        void handleDef(const Defect &def) override {
            if (neg_ == matchDef(def))
                return;

            agent_->handleDef(def);
        }
};

class IPredicate {
    public:
        virtual ~IPredicate() = default;
        virtual bool matchDef(const Defect &def) const = 0;
};

class PredicateFilter: public AbstractFilter {
    public:
        PredicateFilter(AbstractWriter *agent);
        ~PredicateFilter() override;

        /// takes ownership of pred and will call delete on it on destruction
        void append(IPredicate *);

        void setInvertEachMatch(bool enabled = true);

    protected:
        bool matchDef(const Defect &def) override;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

#endif /* H_GUARD_ABSTRACT_FILTER_H */
