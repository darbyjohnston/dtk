// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/Init.h>

#include <dtk/core/FontSystem.h>
#include <dtk/core/Format.h>
#include <dtk/core/ImageIO.h>
#include <dtk/core/LogSystem.h>
#include <dtk/core/OS.h>
#include <dtk/core/Timer.h>

#include <dtk/core/Context.h>

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

