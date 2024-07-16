// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/TabBarPrivate.h>

#include <dtkUI/ButtonGroup.h>
#include <dtkUI/RowLayout.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        struct TabBar::Private
        {
            std::vector<std::string> tabs;
            int currentTab = -1;
            std::shared_ptr<ButtonGroup> buttonGroup;
            std::vector<std::shared_ptr<TabBarButton> > buttons;
            std::shared_ptr<HorizontalLayout> layout;
            int currentFocus = -1;
            std::function<void(int)> callback;
        };

        void TabBar::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::TabBar", parent);
            DTK_P();

            setAcceptsKeyFocus(true);

            p.buttonGroup = ButtonGroup::create(context, ButtonGroupType::Radio);

            p.layout = HorizontalLayout::create(context, shared_from_this());
            p.layout->setSpacingRole(SizeRole::None);

            p.buttonGroup->setCheckedCallback(
                [this](int index, bool value)
                {
                    if (value)
                    {
                        takeKeyFocus();
                        _p->currentTab = index;
                        _p->currentFocus = index;
                        if (_p->callback)
                        {
                            _p->callback(index);
                        }
                        _currentUpdate();
                    }
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
            return _p->tabs;
        }

        void TabBar::setTabs(const std::vector<std::string>& value)
        {
            DTK_P();
            if (value == p.tabs)
                return;
            p.tabs = value;
            p.currentTab = clamp(p.currentTab, 0, static_cast<int>(p.tabs.size()) - 1);
            p.currentFocus = clamp(p.currentFocus, 0, static_cast<int>(p.tabs.size()) - 1);
            _widgetUpdate();
            _currentUpdate();
        }

        void TabBar::addTab(const std::string& value)
        {
            DTK_P();
            p.tabs.push_back(value);
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

        void TabBar::clearTabs()
        {
            DTK_P();
            p.tabs.clear();
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
            const int tmp = clamp(value, 0, static_cast<int>(p.tabs.size()) - 1);
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

        void TabBar::setGeometry(const Box2I& value)
        {
            IWidget::setGeometry(value);
            _p->layout->setGeometry(value);
        }

        void TabBar::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            _setSizeHint(_p->layout->getSizeHint());
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
                    event.accept = true;
                    _setCurrent(p.currentFocus - 1);
                    break;
                case Key::Right:
                    event.accept = true;
                    _setCurrent(p.currentFocus + 1);
                    break;
                case Key::Home:
                    event.accept = true;
                    _setCurrent(0);
                    break;
                case Key::End:
                    event.accept = true;
                    _setCurrent(static_cast<int>(p.tabs.size()) - 1);
                    break;
                case Key::Enter:
                    if (p.currentFocus >= 0 && p.currentFocus < p.buttons.size())
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
                for (const auto& tab : p.tabs)
                {
                    auto button = TabBarButton::create(context, tab, p.layout);
                    button->setCheckedRole(ColorRole::Button);
                    p.buttonGroup->addButton(button);
                    p.buttons.push_back(button);
                }
            }
            p.buttonGroup->setChecked(p.currentTab, true);
        }

        void TabBar::_setCurrent(int value)
        {
            DTK_P();
            const int tmp = clamp(value, 0, static_cast<int>(p.tabs.size()) - 1);
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
}
