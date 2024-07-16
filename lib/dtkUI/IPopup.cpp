// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/IPopup.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        void IPopup::_init(
            const std::shared_ptr<Context>& context,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, objectName, parent);
        }

        IPopup::IPopup()
        {}

        IPopup::~IPopup()
        {}
    }
}
