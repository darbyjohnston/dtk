// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/TabBar.h>

#include <feather-tk/ui/IButton.h>

namespace feather_tk
{
    class TabBarButton : public IButton
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string&,
            const std::shared_ptr<IWidget>& parent);

        TabBarButton();

    public:
        virtual ~TabBarButton();

        static std::shared_ptr<TabBarButton> create(
            const std::shared_ptr<Context>&,
            const std::string&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setCurrent(bool);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };
}