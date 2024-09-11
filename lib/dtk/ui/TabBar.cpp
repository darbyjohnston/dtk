// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/TabBarPrivate.h>

#include <dtk/ui/ButtonGroup.h>
#include <dtk/ui/Divider.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>

namespace dtk
{
    struct TabBar::Private
    {
        std::vector<std::string> text;
        std::vector<std::string> tooltips;
        int currentTab = -1;
        bool closable = false;
        std::shared_ptr<ButtonGroup> buttonGroup;
        std::vector<std::shared_ptr<TabBarButton> > buttons;
        std::shared_ptr<HorizontalLayout> layout;
        std::shared_ptr<ScrollWidget> scrollWidget;
        int currentFocus = -1;
        std::function<void(int)> callback;
        std::function<void(int)> closeCallback;
    };

    void TabBar::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::TabBar", parent);
        DTK_P();

        setAcceptsKeyFocus(true);

        p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);

        p.layout = HorizontalLayout::create(context);
        p.layout->setSpacingRole(SizeRole::None);

        p.scrollWidget = ScrollWidget::create(context, ScrollType::Horizontal, shared_from_this());
        p.scrollWidget->setBorder(false);
        p.scrollWidget->setWidget(p.layout);

        p.buttonGroup->setClickedCallback(
            [this](int index)
            {
                takeKeyFocus();
                _p->currentTab = index;
                _p->currentFocus = index;
                if (_p->callback)
                {
                    _p->callback(index);
                }
                _currentUpdate();
            });
    }

    TabBar::TabBar() :
        _p(new Private)
    {}

    TabBar::~TabBar()
    {}

    std::shared_ptr<TabBar> TabBar::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<TabBar>(new TabBar);
        out->_init(context, parent);
        return out;
    }

    const std::vector<std::string>& TabBar::getTabs() const
    {
        return _p->text;
    }

    void TabBar::setTabs(
        const std::vector<std::string>& value,
        const std::vector<std::string>& tooltips)
    {
        DTK_P();
        if (value == p.text && tooltips == p.tooltips)
            return;
        p.text = value;
        p.tooltips = tooltips;
        p.tooltips.resize(p.text.size());
        p.currentTab = clamp(p.currentTab, 0, static_cast<int>(p.text.size()) - 1);
        p.currentFocus = clamp(p.currentFocus, 0, static_cast<int>(p.text.size()) - 1);
        _widgetUpdate();
        _currentUpdate();
    }

    void TabBar::addTab(
        const std::string& value,
        const std::string& tooltip)
    {
        DTK_P();
        p.text.push_back(value);
        p.tooltips.push_back(tooltip);
        if (-1 == p.currentTab)
        {
            p.currentTab = 0;
        }
        if (-1 == p.currentFocus)
        {
            p.currentFocus = 0;
        }
        _widgetUpdate();
        _currentUpdate();
    }

    void TabBar::removeTab(int index)
    {
        DTK_P();
        if (index >= 0 && index < p.text.size())
        {
            p.text.erase(p.text.begin() + index);
            p.tooltips.erase(p.tooltips.begin() + index);
            if (p.currentTab >= p.text.size())
            {
                p.currentTab = p.currentTab - 1;
            }
            if (p.currentFocus >= p.text.size())
            {
                p.currentFocus = p.currentFocus - 1;
            }
            _widgetUpdate();
            _currentUpdate();
        }
    }

    void TabBar::clearTabs()
    {
        DTK_P();
        p.text.clear();
        p.tooltips.clear();
        p.currentTab = -1;
        p.currentFocus = -1;
        _widgetUpdate();
        _currentUpdate();
    }

    int TabBar::getCurrentTab() const
    {
        return _p->currentTab;
    }

    void TabBar::setCurrentTab(int value)
    {
        DTK_P();
        const int tmp = clamp(value, 0, static_cast<int>(p.text.size()) - 1);
        if (tmp == _p->currentTab)
            return;
        _p->currentTab = tmp;
        _p->buttonGroup->setChecked(_p->currentTab, true);
        _p->currentFocus = tmp;
        _currentUpdate();
    }

    void TabBar::setCallback(const std::function<void(int)>& value)
    {
        _p->callback = value;
    }

    bool TabBar::areTabsClosable() const
    {
        return _p->closable;
    }

    void TabBar::setTabsClosable(bool value)
    {
        DTK_P();
        if (value == p.closable)
            return;
        p.closable = value;
        _widgetUpdate();
    }

    void TabBar::setTabCloseCallback(const std::function<void(int)>& value)
    {
        _p->closeCallback = value;
    }

    void TabBar::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->scrollWidget->setGeometry(value);
    }

    void TabBar::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->scrollWidget->getSizeHint());
    }

    void TabBar::keyFocusEvent(bool value)
    {
        IWidget::keyFocusEvent(value);
        _currentUpdate();
    }

    void TabBar::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Left:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    _setCurrent(p.currentFocus - 1);
                }
                break;
            case Key::Right:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    _setCurrent(p.currentFocus + 1);
                }
                break;
            case Key::Home:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    _setCurrent(0);
                }
                break;
            case Key::End:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    _setCurrent(static_cast<int>(p.text.size()) - 1);
                }
                break;
            case Key::Enter:
                if (hasKeyFocus() && p.currentFocus >= 0 && p.currentFocus < p.buttons.size())
                {
                    event.accept = true;
                    p.buttons[p.currentFocus]->click();
                }
                break;
            case Key::Escape:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    releaseKeyFocus();
                }
                break;
            default: break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void TabBar::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    void TabBar::_widgetUpdate()
    {
        DTK_P();
        p.buttonGroup->clearButtons();
        p.buttons.clear();
        auto children = p.layout->getChildren();
        for (const auto& child : children)
        {
            child->setParent(nullptr);
        }
        if (auto context = _getContext().lock())
        {
            for (size_t i = 0; i < p.text.size(); ++i)
            {
                std::shared_ptr<TabBarButton> button;
                if (p.closable)
                {
                    button = TabBarButton::create(
                        context,
                        p.text[i],
                        p.closable,
                        [this, i]
                        {
                            if (_p->closeCallback)
                            {
                                _p->closeCallback(i);
                            }
                        },
                        p.layout);
                }
                else
                {
                    button = TabBarButton::create(context, p.text[i], p.layout);
                }
                button->setCheckedRole(ColorRole::Button);
                button->setTooltip(p.tooltips[i]);

                p.buttonGroup->addButton(button);
                p.buttons.push_back(button);

                if (p.text.size() > 1 && i < p.text.size() - 1)
                {
                    Divider::create(context, Orientation::Vertical, p.layout);
                }
            }
        }
        p.buttonGroup->setChecked(p.currentTab, true);
    }

    void TabBar::_setCurrent(int value)
    {
        DTK_P();
        const int tmp = clamp(value, 0, static_cast<int>(p.text.size()) - 1);
        if (tmp == p.currentFocus)
            return;
        p.currentFocus = tmp;
        _currentUpdate();
    }

    void TabBar::_currentUpdate()
    {
        DTK_P();
        const bool focus = hasKeyFocus();
        for (size_t i = 0; i < p.buttons.size(); ++i)
        {
            p.buttons[i]->setCurrent(p.currentFocus == i && focus);
        }
    }
}