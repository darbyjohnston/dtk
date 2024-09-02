// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Init.h>

#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/MessageDialog.h>

#include <dtk/core/Context.h>

namespace dtk
{
    void uiInit(const std::shared_ptr<Context>& context)
    {
        if (!context->getSystem<FileBrowserSystem>())
        {
            context->addSystem(FileBrowserSystem::create(context));
        }
        if (!context->getSystem<MessageDialogSystem>())
        {
            context->addSystem(MessageDialogSystem::create(context));
        }
    }
}
