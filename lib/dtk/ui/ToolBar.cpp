// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ToolBar.h>

#include <dtk/ui/Action.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ToolButton.h>

namespace dtk
{
    struct ToolBar::Private
    {
        std::shared_ptr<RowLayout> layout;
    };

    void ToolBar::_init(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ToolBar", parent);
        DTK_P();
        switch (orientation)
        {
        case Orientation::Horizontal:
            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            break;
        case Orientation::Vertical:
            p.layout = VerticalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::SpacingTool);
            break;
        default: break;
        }
    }

    ToolBar::ToolBar() :
        _p(new Private)
    {}

    ToolBar::~ToolBar()
    {}

    std::shared_ptr<ToolBar> ToolBar::create(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolBar>(new ToolBar);
        out->_init(context, orientation, parent);
        return out;
    }

    void ToolBar::addAction(const std::shared_ptr<Action>& action)
    {
        DTK_P();
        if (auto context = getContext())
        {
            ToolButton::create(context, action, p.layout);
        }
    }

    void ToolBar::addWidget(const std::shared_ptr<IWidget>& widget)
    {
        widget->setParent(_p->layout);
    }

    void ToolBar::clear()
    {
        DTK_P();
        auto children = p.layout->getChildren();
        for (const auto& child : children)
        {
            child->setParent(nullptr);
        }
    }

    void ToolBar::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void ToolBar::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }
}