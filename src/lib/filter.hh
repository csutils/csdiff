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

class PathStripper: public GenericAbstractFilter {
    public:
        PathStripper(AbstractWriter *agent, const std::string &prefix):
            GenericAbstractFilter(agent),
            prefStr_(prefix),
            prefSize_(prefix.size())
        {
        }

        void handleDef(const Defect &defOrig) override {
            Defect def(defOrig);

            // iterate through all events
            for (DefEvent &evt : def.events) {
                std::string &path = evt.fileName;
                if (path.size() < prefSize_)
                    continue;

                const std::string str(path, /* pos */ 0U, prefSize_);
                if (str != prefStr_)
                    continue;

                // strip path prefix in this event
                path.erase(/* pos */ 0U, prefSize_);
            }

            agent_->handleDef(def);
        }

    private:
        const std::string           prefStr_;
        const size_t                prefSize_;
};

class PathPrepender: public GenericAbstractFilter {
    public:
        PathPrepender(AbstractWriter *agent, const std::string &prefix):
            GenericAbstractFilter(agent),
            prefix_(prefix)
        {
        }

        void handleDef(const Defect &defOrig) override {
            Defect def(defOrig);

            // iterate through all events
            for (DefEvent &evt : def.events) {
                std::string &path = evt.fileName;
                if (path.empty() || path[0] == '/')
                    // not a relative path
                    continue;

                path.insert(0U, prefix_);
            }

            agent_->handleDef(def);
        }

    private:
        const std::string           prefix_;
};

class DropScanProps: public GenericAbstractFilter {
    public:
        DropScanProps(AbstractWriter *agent):
            GenericAbstractFilter(agent)
        {
        }

        /// ignore any given scan properties
        void setScanProps(const TScanProps &) override { }

        /// always return empty scan properties
        const TScanProps& getScanProps() const override {
            return emp_;
        }

    private:
        const TScanProps emp_;
};

class ScanPropSetter: public GenericAbstractFilter {
    public:
        using TStringList = std::vector<std::string>;

        ScanPropSetter(AbstractWriter *agent, const TStringList &propList);

        /// override specified scan properties
        void setScanProps(const TScanProps &origProps) override;

    private:
        // key/val pairs are stored in a vector
        using TItem = std::pair<std::string, std::string>;
        using TList = std::vector<TItem>;
        TList itemList_;
};

class DuplicateFilter: public AbstractFilter {
    public:
        DuplicateFilter(AbstractWriter *agent);
        ~DuplicateFilter() override = default;

    protected:
        bool matchDef(const Defect &def) override;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

/// collapses warnings if their count exceeds the specified limit
class RateLimitter: public AbstractFilter {
    public:
        RateLimitter(AbstractWriter *agent, int rateLimit);
        ~RateLimitter() override = default;
        void flush() override;

    protected:
        bool matchDef(const Defect &) override;

    private:
        struct Private;
        std::unique_ptr<Private> d;
};

/// Trim messages to avoid excessively long output
class MsgTrimmer: public GenericAbstractFilter {
    private:
        size_t maxMsgLen_;

    public:
        MsgTrimmer(AbstractWriter *agent, const size_t maxMsgLen):
            GenericAbstractFilter(agent),
            maxMsgLen_(maxMsgLen)
        {
        }

        void handleDef(const Defect &defOrig) override;
};

/// set importance level on all defects to the specified value
class ImpLevelSetter: public GenericAbstractFilter {
    private:
        const int impLevel_;

    public:
        ImpLevelSetter(AbstractWriter *agent, const int impLevel):
            GenericAbstractFilter(agent),
            impLevel_(impLevel)
        {
        }

        void handleDef(const Defect &defOrig) override;
};

#endif /* H_GUARD_FILTER_H */
