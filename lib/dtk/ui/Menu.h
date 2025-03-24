// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Action.h>
#include <dtk/ui/IMenuPopup.h>

namespace dtk
{
    class MenuButton;

    //! \name Menu Widgets
    ///@{

    //! Menu.
    class Menu : public IMenuPopup
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        Menu();

    public:
        virtual ~Menu();

        //! Create a new widget.
        static std::shared_ptr<Menu> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the items.
        const std::vector<std::shared_ptr<Action> >& getItems() const;

        //! Add a menu item.
        void addItem(const std::shared_ptr<Action>&);

        //! Set whether a menu item is checked.
        void setItemChecked(const std::shared_ptr<Action>&, bool);

        //! Set whether a menu item is enabled.
        void setItemEnabled(const std::shared_ptr<Action>&, bool);

        //! Get the sub menus.
        const std::vector<std::shared_ptr<Menu> >& getSubMenus() const;

        //! Add a sub menu.
        std::shared_ptr<Menu> addSubMenu(const std::string&);

        //! Set whether a sub menu is enabled.
        void setSubMenuEnabled(const std::shared_ptr<Menu>&, bool);

        //! Add a divider.
        void addDivider();

        //! Clear the menu.
        void clear();

        //! Get whether the menu is empty.
        bool isEmpty() const;

        //! Handle keyboard shortcuts.
        bool shortcut(Key, int);

        void close() override;

        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _setCurrent(const std::shared_ptr<MenuButton>&);
        void _currentUpdate();

        std::shared_ptr<Menu> _getOpenMenu() const;

        void _accept();

        DTK_PRIVATE();
    };

    ///@}
}
