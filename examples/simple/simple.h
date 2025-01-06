// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Window.h>

namespace dtk
{
    namespace examples
    {
        namespace simple
        {
            class Window : public dtk::Window
            {
            protected:
                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<Context>&,
                    const std::string& name,
                    const Size2I&);

                void drawEvent(const Box2I&, const DrawEvent&) override;
            };
        }
    }
}

