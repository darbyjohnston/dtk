// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/ISystem.h>

#include <dtk/core/Context.h>
#include <dtk/core/LogSystem.h>

namespace dtk
{
    ISystem::ISystem(
        const std::shared_ptr<Context>& context,
        const std::string& name) :
        _context(context),
        _name(name)
    {
        if (auto logSystem = context->getSystem<LogSystem>())
        {
            logSystem->print(_name, "Create...");
        }
    }

    ISystem::~ISystem()
    {
        if (auto context = _context.lock())
        {
            if (auto logSystem = context->getSystem<LogSystem>())
            {
                logSystem->print(_name, "Destroy...");
            }
        }
    }

    void ISystem::tick()
    {}

    std::chrono::milliseconds ISystem::getTickTime() const
    {
        return std::chrono::milliseconds(0);
    }
}