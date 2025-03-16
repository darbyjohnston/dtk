// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/StackLayout.h>

namespace dtk
{
    struct StackLayout::Private
    {
        int currentIndex = 0;
        SizeRole marginRole = SizeRole::None;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int margin = 0;
        };
        SizeData size;
    };

    void StackLayout::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::StackLayout", parent);
    }

    StackLayout::StackLayout() :
        _p(new Private)
    {}

    StackLayout::~StackLayout()
    {}

    std::shared_ptr<StackLayout> StackLayout::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<StackLayout>(new StackLayout);
        out->_init(context, parent);
        return out;
    }

    int StackLayout::getCurrentIndex() const
    {
        return _p->currentIndex;
    }

    void StackLayout::setCurrentIndex(int value)
    {
        DTK_P();
        if (value == p.currentIndex)
            return;
        p.currentIndex = value;
        _widgetUpdate();
    }

    void StackLayout::setCurrentWidget(const std::shared_ptr<IWidget>& value)
    {
        int index = -1;
        const auto& children = getChildren();
        int j = 0;
        for (auto i = children.begin(); i != children.end(); ++i, ++j)
        {
            if (value == *i)
            {
                index = j;
                break;
            }
        }
        setCurrentIndex(index);
    }

    SizeRole StackLayout::getMarginRole() const
    {
        return _p->marginRole;
    }

    void StackLayout::setMarginRole(SizeRole value)
    {
        DTK_P();
        if (value == p.marginRole)
            return;
        p.marginRole = value;
        p.size.init = true;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void StackLayout::clear()
    {
        auto children = getChildren();
        for (auto child : children)
        {
            child->setParent(nullptr);
        }
    }

    void StackLayout::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        const Box2I g = margin(getGeometry(), -p.size.margin);
        for (const auto& child : getChildren())
        {
            child->setGeometry(g);
        }
    }

    Box2I StackLayout::getChildrenClipRect() const
    {
        return margin(getGeometry(), -_p->size.margin);
    }

    void StackLayout::childAddEvent(const ChildAddEvent& event)
    {
        IWidget::childAddEvent(event);
        _widgetUpdate();
    }

    void StackLayout::childRemoveEvent(const ChildRemoveEvent& event)
    {
        IWidget::childRemoveEvent(event);
        DTK_P();
        p.currentIndex = clamp(
            p.currentIndex,
            0,
            static_cast<int>(getChildren().size()) - 1);
        _widgetUpdate();
    }

    void StackLayout::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (p.size.init || displayScaleChanged)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(p.marginRole, p.size.displayScale);
        }

        Size2I sizeHint;
        for (const auto& child : getChildren())
        {
            const Size2I& childSizeHint = child->getSizeHint();
            sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
            sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
        }
        sizeHint.w += p.size.margin * 2;
        sizeHint.h += p.size.margin * 2;
        _setSizeHint(sizeHint);
    }

    void StackLayout::_widgetUpdate()
    {
        DTK_P();
        const auto& children = getChildren();
        int j = 0;
        for (auto i = children.begin(); i != children.end(); ++i, ++j)
        {
            (*i)->setVisible(j == p.currentIndex);
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }
}