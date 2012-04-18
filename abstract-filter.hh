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

#include "abstract-parser.hh"

class AbstractEngine {
    protected:
        virtual void handleDef(const Defect &def) = 0;
        virtual void notifyFile(const std::string &) { }
        friend class AbstractFilter;

    public:
        AbstractEngine() { }
        virtual ~AbstractEngine() { }

        bool handleFile(const std::string &fileName, bool silent);

        virtual void flush() { };

    private:
        AbstractEngine(const AbstractEngine &);
        AbstractEngine& operator=(const AbstractEngine &);
};

/// decorator
class AbstractFilter: public AbstractEngine {
    private:
        bool neg_;

    protected:
        AbstractEngine *slave_;
        virtual bool matchDef(const Defect &def) const = 0;

        virtual void notifyFile(const std::string &fileName) {
            slave_->notifyFile(fileName);
        }

    public:
        AbstractFilter(AbstractEngine *slave):
            neg_(false),
            slave_(slave)
        {
        }

        ~AbstractFilter() {
            delete slave_;
        }

        void setInvertMatch(bool enabled = true) {
            neg_ = enabled;
        }

        virtual void handleDef(const Defect &def) {
            if (neg_ == matchDef(def))
                return;

            slave_->handleDef(def);
        }

        virtual void flush() {
            slave_->flush();
        }
};

class IPredicate {
    public:
        virtual ~IPredicate() { }
        virtual bool matchDef(const Defect &def) const = 0;
};

class PredicateFilter: public AbstractFilter {
    public:
        PredicateFilter(AbstractEngine *slave);
        virtual ~PredicateFilter();

        /// takes ownership of pred and will call delete on it on destruction
        void append(IPredicate *);

        // cppcheck-suppress functionConst
        void setInvertEachMatch(bool enabled = true);

    protected:
        virtual bool matchDef(const Defect &def) const;

    private:
        struct Private;
        Private *d;
};

#endif /* H_GUARD_ABSTRACT_FILTER_H */
