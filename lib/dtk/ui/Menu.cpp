// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/MenuPrivate.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    struct Menu::Private
    {
        std::vector<std::shared_ptr<Action> > items;
        std::vector<std::shared_ptr<MenuButton> > buttons;
        std::map< std::shared_ptr<Action>, std::shared_ptr<MenuButton> > itemToButton;
        std::shared_ptr<MenuButton> current;
        std::weak_ptr<Menu> parentMenu;
        std::vector<std::shared_ptr<Menu> > subMenus;
        std::map<std::shared_ptr<Menu>, std::shared_ptr<MenuButton> > subMenuToButton;
        std::map<std::shared_ptr<MenuButton>, std::shared_ptr<Menu> > buttonToSubMenu;
        std::shared_ptr<VerticalLayout> layout;
    };

    void Menu::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IMenuPopup::_init(context, "dtk::Menu", parent);
        DTK_P();
        setAcceptsKeyFocus(true);
        p.layout = VerticalLayout::create(context);
        p.layout->setSpacingRole(SizeRole::None);
        setWidget(p.layout);
    }

    Menu::Menu() :
        _p(new Private)
    {}

    Menu::~Menu()
    {}

    std::shared_ptr<Menu> Menu::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Menu>(new Menu);
        out->_init(context, parent);
        return out;
    }

    const std::vector<std::shared_ptr<Action> >& Menu::getItems() const
    {
        return _p->items;
    }

    void Menu::addItem(const std::shared_ptr<Action>& item)
    {
        DTK_P();
        if (auto context = getContext())
        {
            p.items.push_back(item);

            auto button = MenuButton::create(context, item, p.layout);
            p.buttons.push_back(button);
            p.itemToButton[item] = button;

            auto buttonWeak = std::weak_ptr<MenuButton>(button);
            button->setHoveredCallback(
                [this, buttonWeak](bool value)
                {
                    if (value)
                    {
                        if (auto menu = _getOpenMenu())
                        {
                            menu->close();
                        }
                        _setCurrent(buttonWeak.lock());
                    }
                });
            button->setClickedCallback(
                [this, item, buttonWeak]
                {
                    _setCurrent(buttonWeak.lock());
                    _accept();
                    item->doCallback();
                });
            button->setCheckedCallback(
                [this, item, buttonWeak](bool value)
                {
                    item->setChecked(value);
                    _setCurrent(buttonWeak.lock());
                    _accept();
                    item->doCheckedCallback(value);
                });

            if (!p.current)
            {
                p.current = button;
                _currentUpdate();
            }
        }
    }

    void Menu::setItemChecked(const std::shared_ptr<Action>& item, bool value)
    {
        DTK_P();
        const auto i = p.itemToButton.find(item);
        if (i != p.itemToButton.end())
        {
            i->first->setChecked(value);
            i->second->setChecked(value);
        }
    }

    void Menu::setItemEnabled(const std::shared_ptr<Action>& item, bool value)
    {
        DTK_P();
        const auto i = p.itemToButton.find(item);
        if (i != p.itemToButton.end())
        {
            i->second->setEnabled(value);
        }
    }

    const std::vector<std::shared_ptr<Menu> >& Menu::getSubMenus() const
    {
        return _p->subMenus;
    }

    std::shared_ptr<Menu> Menu::addSubMenu(const std::string& text)
    {
        DTK_P();
        std::shared_ptr<Menu> out;
        if (auto context = getContext())
        {
            out = Menu::create(context);
            out->setPopup(MenuPopup::SubMenu);
            out->_p->parentMenu = std::dynamic_pointer_cast<Menu>(shared_from_this());
            p.subMenus.push_back(out);

            auto button = MenuButton::create(context, nullptr, p.layout);
            button->setText(text);
            button->setIcon("Empty");
            button->setSubMenuIcon("SubMenuArrow");
            p.buttons.push_back(button);
            p.subMenuToButton[out] = button;
            p.buttonToSubMenu[button] = out;

            auto buttonWeak = std::weak_ptr<MenuButton>(button);
            button->setHoveredCallback(
                [this, out, buttonWeak](bool value)
                {
                    if (value)
                    {
                        if (!out->isOpen())
                        {
                            if (auto openMenu = _getOpenMenu())
                            {
                                openMenu->close();
                            }
                            if (auto button = buttonWeak.lock())
                            {
                                _setCurrent(button);
                                if (!out->getItems().empty())
                                {
                                    out->open(getWindow(), button->getGeometry());
                                }
                            }
                        }
                    }
                });
            button->setPressedCallback(
                [this, out, buttonWeak]
                {
                    _setCurrent(buttonWeak.lock());
                    if (!out->isOpen())
                    {
                        if (auto openMenu = _getOpenMenu())
                        {
                            openMenu->close();
                        }
                        if (auto button = buttonWeak.lock())
                        {
                            _setCurrent(button);
                            if (!out->getItems().empty())
                            {
                                out->open(getWindow(), button->getGeometry());
                            }
                        }
                    }
                });

            if (!p.current)
            {
                p.current = button;
                _currentUpdate();
            }
        }
        return out;
    }

    void Menu::setSubMenuEnabled(const std::shared_ptr<Menu>& menu, bool value)
    {
        DTK_P();
        const auto i = p.subMenuToButton.find(menu);
        if (i != p.subMenuToButton.end())
        {
            i->second->setEnabled(value);
        }
    }

    void Menu::addDivider()
    {
        DTK_P();
        if (auto context = getContext())
        {
            Divider::create(context, Orientation::Horizontal, p.layout);
        }
    }

    void Menu::clear()
    {
        DTK_P();
        p.items.clear();
        for (const auto& button : p.buttons)
        {
            button->setParent(nullptr);
        }
        p.buttons.clear();
        p.itemToButton.clear();
        p.current.reset();
        p.parentMenu.reset();
        p.subMenus.clear();
        p.subMenuToButton.clear();
        p.buttonToSubMenu.clear();
    }

    bool Menu::shortcut(Key shortcut, int modifiers)
    {
        DTK_P();
        bool out = false;
        if (shortcut != Key::Unknown)
        {
            for (const auto& i : p.itemToButton)
            {
                if (shortcut == i.first->getShortcut() &&
                    modifiers == i.first->getShortcutModifiers())
                {
                    if (i.first->isCheckable())
                    {
                        setItemChecked(i.first, !i.first->isChecked());
                        i.first->doCheckedCallback(i.first->isChecked());
                    }
                    else
                    {
                        i.first->doCallback();
                    }
                    out = true;
                }
            }
        }
        if (!out)
        {
            for (const auto& subMenu : p.subMenus)
            {
                out = subMenu->shortcut(shortcut, modifiers);
                if (out)
                {
                    break;
                }
            }
        }
        return out;
    }

    void Menu::close()
    {
        DTK_P();
        for (const auto& subMenu : p.subMenus)
        {
            subMenu->close();
        }
        IMenuPopup::close();
    }

    void Menu::keyFocusEvent(bool value)
    {
        IMenuPopup::keyFocusEvent(value);
        _currentUpdate();
    }

    void Menu::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Enter:
                event.accept = true;
                takeKeyFocus();
                if (p.current)
                {
                    auto button = p.current;
                    const auto i = p.buttonToSubMenu.find(button);
                    if (i != p.buttonToSubMenu.end())
                    {
                        _setCurrent(button);
                        if (!i->second->getItems().empty())
                        {
                            i->second->open(getWindow(), button->getGeometry());
                        }
                    }
                    else
                    {
                        button->click();
                    }
                }
                break;
            case Key::Up:
            {
                event.accept = true;
                takeKeyFocus();
                auto i = p.buttons.begin();
                for (; i != p.buttons.end() && *i != p.current; ++i)
                    ;
                if (i != p.buttons.begin())
                {
                    --i;
                }
                if (i != p.buttons.end())
                {
                    _setCurrent(*i);
                }
                break;
            }
            case Key::Down:
            {
                event.accept = true;
                takeKeyFocus();
                auto i = p.buttons.begin();
                for (; i != p.buttons.end() && *i != p.current; ++i)
                    ;
                if (i != p.buttons.end())
                {
                    ++i;
                }
                if (i != p.buttons.end())
                {
                    _setCurrent(*i);
                }
                break;
            }
            case Key::Home:
                event.accept = true;
                takeKeyFocus();
                if (!p.buttons.empty())
                {
                    _setCurrent(*p.buttons.begin());
                }
                break;
            case Key::End:
                event.accept = true;
                takeKeyFocus();
                if (!p.buttons.empty())
                {
                    _setCurrent(*(p.buttons.end() - 1));
                }
                break;
            default: break;
            }
        }
        if (!event.accept)
        {
            IMenuPopup::keyPressEvent(event);
        }
    }

    void Menu::keyReleaseEvent(KeyEvent& event)
    {
        IMenuPopup::keyReleaseEvent(event);
        event.accept = true;
    }

    void Menu::_setCurrent(const std::shared_ptr<MenuButton>& button)
    {
        DTK_P();
        if (button == p.current)
            return;
        p.current = button;
        _currentUpdate();
    }

    void Menu::_currentUpdate()
    {
        DTK_P();
        const bool focus = hasKeyFocus();
        for (const auto& button : p.buttons)
        {
            button->setCurrent(p.current == button && focus);
        }
    }

    std::shared_ptr<Menu> Menu::_getOpenMenu() const
    {
        DTK_P();
        std::shared_ptr<Menu> out;
        for (const auto& subMenu : p.subMenus)
        {
            if (subMenu->isOpen())
            {
                out = subMenu;
                break;
            }
        }
        return out;
    }

    void Menu::_accept()
    {
        DTK_P();
        if (auto parentMenu = p.parentMenu.lock())
        {
            parentMenu->_accept();
        }
        close();
    }
}
