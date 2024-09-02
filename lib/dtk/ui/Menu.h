// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Action.h>
#include <dtk/ui/IMenuPopup.h>

namespace dtk
{
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

        //! Add a menu item.
        void addItem(const std::shared_ptr<Action>&);

        //! Set whether a menu item is checked.
        void setItemChecked(const std::shared_ptr<Action>&, bool);

        //! Set whether a menu item is enabled.
        void setItemEnabled(const std::shared_ptr<Action>&, bool);

        //! Add a sub menu.
        std::shared_ptr<Menu> addSubMenu(const std::string&);

        //! Add a divider.
        void addDivider();

        //! Clear the menu.
        void clear();

        //! Handle keyboard shortcuts.
        bool shortcut(Key, int);

        void close() override;

        void keyFocusEvent(bool) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _setCurrent(int);
        void _currentUpdate();

        std::shared_ptr<Menu> _getOpenMenu() const;

        void _accept();

        DTK_PRIVATE();
    };

    ///@}
}
