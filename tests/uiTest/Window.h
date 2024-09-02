// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWindow.h>

namespace dtk
{
    namespace ui_test
    {
        class App;

        class Window : public ui::IWindow
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::string& name,
                const Size2I&);

            Window();

        public:
            virtual ~Window();

            static std::shared_ptr<Window> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::string& name,
                const Size2I& = Size2I(1280, 960));

            void setDisplayScale(float);
            void setCursorEnter(bool);
            void setCursorPos(const V2I&);
            void setButton(int button, int modifiers = 0);
            void setButton(int button, bool press, int modifiers = 0);
            void setScroll(const V2F&);
            void setKey(ui::Key, int modifiers = 0);
            void setKey(ui::Key, bool press, int modifiers = 0);
            void setText(const std::string&);
            void setDrop(const std::vector<std::string>&);

            void update(
                const std::shared_ptr<FontSystem>&,
                const std::shared_ptr<ui::Style>&,
                const std::shared_ptr<ui::IconLibrary>&);

            void setGeometry(const Box2I&) override;
            void sizeHintEvent(const ui::SizeHintEvent&) override;

        private:
            DTK_PRIVATE();
        };
    }
}

