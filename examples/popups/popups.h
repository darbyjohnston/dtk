// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUIApp/Window.h>

#include <dtkUI/MenuBar.h>

namespace dtk
{
    namespace examples
    {
        namespace popups
        {
            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

                void keyPressEvent(ui::KeyEvent&) override;
                void keyReleaseEvent(ui::KeyEvent&) override;

            private:
                std::shared_ptr<ui::MenuBar> _menuBar;
            };
        }
    }
}
