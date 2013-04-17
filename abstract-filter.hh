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
    private:
        bool neg_;

    protected:
        AbstractWriter *slave_;
        virtual void handleDef(const Defect &def) = 0;

    public:
        virtual void notifyFile(const std::string &fileName) {
            slave_->notifyFile(fileName);
        }

        GenericAbstractFilter(AbstractWriter *slave):
            neg_(false),
            slave_(slave)
        {
        }

        ~GenericAbstractFilter() {
            delete slave_;
        }

        virtual void flush() {
            slave_->flush();
        }

        virtual const TScanProps& getScanProps() const {
            return slave_->getScanProps();
        }

        virtual void setScanProps(const TScanProps &scanProps) {
            slave_->setScanProps(scanProps);
        }
};

/// decorator
class AbstractFilter: public GenericAbstractFilter {
    private:
        bool neg_;

    protected:
        virtual bool matchDef(const Defect &def) const = 0;

    public:
        AbstractFilter(AbstractWriter *slave):
            GenericAbstractFilter(slave),
            neg_(false)
        {
        }

        void setInvertMatch(bool enabled = true) {
            neg_ = enabled;
        }

        virtual void handleDef(const Defect &def) {
            if (neg_ == matchDef(def))
                return;

            slave_->handleDef(def);
        }
};

class IPredicate {
    public:
        virtual ~IPredicate() { }
        virtual bool matchDef(const Defect &def) const = 0;
};

class PredicateFilter: public AbstractFilter {
    public:
        PredicateFilter(AbstractWriter *slave);
        virtual ~PredicateFilter();

        /// takes ownership of pred and will call delete on it on destruction
        void append(IPredicate *);

        void setInvertEachMatch(bool enabled = true);

    protected:
        virtual bool matchDef(const Defect &def) const;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_ABSTRACT_FILTER_H */
