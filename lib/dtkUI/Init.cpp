// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/Init.h>

#include <dtkUI/FileBrowser.h>
#include <dtkUI/MessageDialog.h>

#include <dtkCore/Context.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        void init(const std::shared_ptr<Context>& context)
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
}
