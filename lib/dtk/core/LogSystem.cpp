// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/LogSystem.h>

#include <dtk/core/Context.h>

#include <mutex>
#include <sstream>

namespace dtk
{
    bool LogItem::operator == (const LogItem& other) const
    {
        return
            time == other.time &&
            prefix == other.prefix &&
            message == other.message &&
            type == other.type;
    }

    bool LogItem::operator != (const LogItem& other) const
    {
        return !(*this == other);
    }

    std::string toString(const LogItem& item)
    {
        std::stringstream ss;
        ss.precision(2);
        ss << std::fixed << item.time << " ";
        ss << item.prefix << ": ";
        switch (item.type)
        {
        case LogType::Message:
            ss << item.message;
            break;
        case LogType::Warning:
            ss << "Warning: " << item.message;
            break;
        case LogType::Error:
            ss << "ERROR: " << item.message;
            break;
        }
        return ss.str();
    }

    struct LogSystem::Private
    {
        std::chrono::steady_clock::time_point startTime;
        std::shared_ptr<ObservableList<LogItem> > observableItems;
        std::vector<LogItem> items;
        std::mutex mutex;
    };

    LogSystem::LogSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::LogSystem"),
        _p(new Private)
    {
        DTK_P();
        p.startTime = std::chrono::steady_clock::now();
        p.observableItems = ObservableList<LogItem>::create();
    }

    LogSystem::~LogSystem()
    {}

    std::shared_ptr<LogSystem> LogSystem::create(const std::shared_ptr<Context>& context)
    {
        auto out = context->getSystem<LogSystem>();
        if (!out)
        {
            out = std::shared_ptr<LogSystem>(new LogSystem(context));
        }
        return out;
    }

    void LogSystem::print(
        const std::string& prefix,
        const std::string& value,
        LogType type)
    {
        DTK_P();
        const auto now = std::chrono::steady_clock::now();
        const std::chrono::duration<float> time = now - p.startTime;
        std::unique_lock<std::mutex> lock(p.mutex);
        p.items.push_back({ time.count(), prefix, value, type });
    }

    std::shared_ptr<IObservableList<LogItem> > LogSystem::observeLogItems() const
    {
        return _p->observableItems;
    }

    void LogSystem::tick()
    {
        DTK_P();
        std::vector<LogItem> items;
        {
            std::unique_lock<std::mutex> lock(p.mutex);
            p.items.swap(items);
        }
        p.observableItems->setIfChanged(items);
    }

    std::chrono::milliseconds LogSystem::getTickTime() const
    {
        return std::chrono::milliseconds(100);
    }
}