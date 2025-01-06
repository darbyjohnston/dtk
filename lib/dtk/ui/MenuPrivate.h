// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Menu.h>

#include <dtk/ui/IButton.h>

namespace dtk
{
    class MenuButton : public IButton
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        MenuButton();

    public:
        virtual ~MenuButton();

        static std::shared_ptr<MenuButton> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCurrent(bool);
        void setShortcut(Key, int modifiers = 0);
        void setSubMenuIcon(const std::string&);

        void setText(const std::string&) override;

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(
            const Box2I&,
            const DrawEvent&) override;

    private:
        DTK_PRIVATE();
    };
}