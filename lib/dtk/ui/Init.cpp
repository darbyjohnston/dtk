// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Init.h>

#include <dtk/ui/DialogSystem.h>
#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/IconSystem.h>
#include <dtk/ui/Settings.h>

#include <dtk/core/Context.h>

namespace dtk
{
    void uiInit(
        const std::shared_ptr<Context>& context,
        const std::string& settingsPath)
    {
        if (!context->getSystem<Settings>())
        {
            context->addSystem(Settings::create(context, settingsPath));
        }
        if (!context->getSystem<DialogSystem>())
        {
            context->addSystem(DialogSystem::create(context));
        }
        if (!context->getSystem<FileBrowserSystem>())
        {
            context->addSystem(FileBrowserSystem::create(context));
        }
        if (!context->getSystem<IconSystem>())
        {
            context->addSystem(IconSystem::create(context));
        }
    }
}
