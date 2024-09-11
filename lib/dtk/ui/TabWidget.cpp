// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/TabWidget.h>

#include <dtk/ui/RowLayout.h>
#include <dtk/ui/StackLayout.h>
#include <dtk/ui/TabBar.h>

namespace dtk
{
    struct TabWidget::Private
    {
        std::shared_ptr<TabBar> tabs;
        std::shared_ptr<StackLayout> stack;
        std::shared_ptr<RowLayout> layout;
        std::function<void(int)> callback;
    };

    void TabWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::TabWidget", parent);
        DTK_P();

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
            
        p.tabs = TabBar::create(context, p.layout);
            
        p.stack = StackLayout::create(context, p.layout);
        p.stack->setVStretch(Stretch::Expanding);

        _widgetUpdate();

        p.tabs->setCallback(
            [this](int value)
            {
                if (_p->callback)
                {
                    _p->callback(value);
                }
                _widgetUpdate();
            });
    }

    TabWidget::TabWidget() :
        _p(new Private)
    {}

    TabWidget::~TabWidget()
    {}

    std::shared_ptr<TabWidget> TabWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TabWidget>(new TabWidget);
        out->_init(context, parent);
        return out;
    }

    const std::vector<std::string>& TabWidget::getTabs() const
    {
        return _p->tabs->getTabs();
    }

    void TabWidget::addTab(
        const std::string& value,
        const std::shared_ptr<IWidget>& widget,
        const std::string& tooltip)
    {
        DTK_P();
        p.tabs->addTab(value, tooltip);
        widget->setParent(p.stack);
        _widgetUpdate();
    }

    void TabWidget::removeTab(int index)
    {
        DTK_P();
        p.tabs->removeTab(index);
        auto children = p.stack->getChildren();
        int i = 0;
        for (auto j = children.begin(); j != children.end(); ++j, ++i)
        {
            if (i == index)
            {
                (*j)->setParent(nullptr);
                break;
            }
        }
    }

    void TabWidget::removeTab(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        auto children = p.stack->getChildren();
        int i = 0;
        for (auto j = children.begin(); j != children.end(); ++j, ++i)
        {
            if (*j == value)
            {
                (*j)->setParent(nullptr);
                break;
            }
        }
        p.tabs->removeTab(i);
    }

    void TabWidget::clearTabs()
    {
        DTK_P();
        p.tabs->clearTabs();
        auto children = p.stack->getChildren();
        for (const auto& child : children)
        {
            child->setParent(nullptr);
        }
    }

    int TabWidget::getCurrentTab() const
    {
        return _p->tabs->getCurrentTab();
    }

    void TabWidget::setCurrentTab(int value)
    {
        DTK_P();
        p.tabs->setCurrentTab(value);
        _widgetUpdate();
    }

    void TabWidget::setCallback(const std::function<void(int)>& value)
    {
        _p->callback = value;
    }

    bool TabWidget::areTabsClosable() const
    {
        return _p->tabs->areTabsClosable();
    }

    void TabWidget::setTabsClosable(bool value)
    {
        _p->tabs->setTabsClosable(value);
    }

    void TabWidget::setTabCloseCallback(const std::function<void(int)>& value)
    {
        _p->tabs->setTabCloseCallback(value);
    }

    void TabWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void TabWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void TabWidget::_widgetUpdate()
    {
        DTK_P();
        const int index = p.tabs->getCurrentTab();
        p.stack->setCurrentIndex(index);
    }
}
