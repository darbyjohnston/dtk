// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/DockLayout.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/RowLayout.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        struct IDockWidget::Private
        {
        };

        void IDockWidget::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::IDockWidget", parent);
            DTK_P();
        }

        IDockWidget::IDockWidget() :
            _p(new Private)
        {}

        IDockWidget::~IDockWidget()
        {}

        void IDockWidget::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
        }

        void IDockWidget::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
        }

        struct DockLayout::Private
        {
        };

        void DockLayout::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::DockLayout", parent);
            DTK_P();
        }

        DockLayout::DockLayout() :
            _p(new Private)
        {}

        DockLayout::~DockLayout()
        {}

        std::shared_ptr<DockLayout> DockLayout::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<DockLayout>(new DockLayout);
            out->_init(context, parent);
            return out;
        }

        void DockLayout::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
        }

        void DockLayout::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
        }
    }
}
