// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/MenuBar.h>
#include <dtk/ui/Window.h>

namespace dtk
{
    namespace examples
    {
        namespace popups
        {
            class Window : public dtk::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::string& name,
                    const Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<Context>&,
                    const std::string& name,
                    const Size2I&);

                void keyPressEvent(KeyEvent&) override;
                void keyReleaseEvent(KeyEvent&) override;

            private:
                std::shared_ptr<MenuBar> _menuBar;
            };
        }
    }
}
