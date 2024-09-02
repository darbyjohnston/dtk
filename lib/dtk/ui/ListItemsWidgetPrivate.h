// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/ListItemsWidget.h>

#include <dtk/ui/IButton.h>

namespace dtk
{
    namespace ui
    {
        class ListItemButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>& parent);

            ListItemButton();

        public:
            virtual ~ListItemButton();

            static std::shared_ptr<ListItemButton> create(
                const std::shared_ptr<Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCurrent(bool);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const Box2I&, bool) override;
            void drawEvent(const Box2I&, const DrawEvent&) override;

        private:
            DTK_PRIVATE();
        };
    }
}
