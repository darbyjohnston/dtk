// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/ListItemsWidget.h>

#include <dtkUI/IButton.h>

namespace dtk
{
    namespace ui
    {
        class ListItemButton : public IButton
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>& parent);

            ListItemButton();

        public:
            virtual ~ListItemButton();

            static std::shared_ptr<ListItemButton> create(
                const std::shared_ptr<core::Context>&,
                const std::string&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void setCurrent(bool);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void clipEvent(const core::Box2I&, bool) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            DTK_PRIVATE();
        };
    }
}
