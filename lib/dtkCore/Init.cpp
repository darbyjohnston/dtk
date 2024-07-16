// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/Init.h>

#include <dtkCore/FontSystem.h>
#include <dtkCore/Format.h>
#include <dtkCore/ImageIO.h>
#include <dtkCore/LogSystem.h>
#include <dtkCore/OS.h>
#include <dtkCore/Timer.h>

#include <dtkCore/Context.h>

namespace dtk
{
    namespace core
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<LogSystem>())
            {
                auto logSystem = LogSystem::create(context);
                context->addSystem(logSystem);
                const auto systemInfo = getSystemInfo();
                logSystem->print(
                    "dtk::core::init",
                    Format(
                    "System information:\n"
                    "    Name:  {0}\n"
                    "    Cores: {1}\n"
                    "    RAM:   {2}GB").
                    arg(systemInfo.name).
                    arg(systemInfo.cores).
                    arg(systemInfo.ramGB));
            }
            if (!context->getSystem<FontSystem>())
            {
                context->addSystem(FontSystem::create(context));
            }
            if (!context->getSystem<ImageIO>())
            {
                context->addSystem(ImageIO::create(context));
            }
            if (!context->getSystem<TimerSystem>())
            {
                context->addSystem(TimerSystem::create(context));
            }
        }
    }
}

