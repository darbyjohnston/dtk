// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Label.h>
#include <dtk/ui/MenuBar.h>
#include <dtk/ui/Window.h>

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            class App;

            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const core::Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const core::Size2I&);

                void keyPressEvent(ui::KeyEvent&) override;
                void keyReleaseEvent(ui::KeyEvent&) override;

            private:
                std::map<std::string, std::shared_ptr<ui::Action> > _actions;
                std::map<std::string, std::shared_ptr<ui::Menu> > _menus;
                std::shared_ptr<ui::MenuBar> _menuBar;
                std::shared_ptr<ui::Label> _textWidget;
                std::shared_ptr<core::ValueObserver<ui::FontRole> > _fontObserver;
                std::shared_ptr<core::ValueObserver<std::string> > _textObserver;
            };
        }
    }
}
