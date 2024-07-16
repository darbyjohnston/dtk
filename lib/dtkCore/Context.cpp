// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/Context.h>

#include <dtkCore/ISystem.h>

namespace dtk
{
    namespace core
    {
        Context::~Context()
        {}

        std::shared_ptr<Context> Context::create()
        {
            return std::shared_ptr<Context>(new Context);
        }

        void Context::addSystem(const std::shared_ptr<ISystem>& system)
        {
            _systems.push_front(system);
            _systemTimes[system] = std::chrono::steady_clock::now();
        }

        const std::list<std::shared_ptr<ISystem> >& Context::getSystems() const
        {
            return _systems;
        }

        void Context::tick()
        {
            const auto now = std::chrono::steady_clock::now();
            for (auto& i : _systemTimes)
            {
                const auto tickTime = i.first->getTickTime();
                if (tickTime > std::chrono::milliseconds(0) &&
                    (i.second + i.first->getTickTime()) <= now)
                {
                    i.first->tick();
                    i.second = now;
                }
            }
        }
    }
}
