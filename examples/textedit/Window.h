// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/Menu.h>

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            class App;

            class Window : public dtk::MainWindow
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const Size2I&);

                Window() = default;

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<App>&,
                    const std::string& name,
                    const Size2I&);

            private:
                std::map<std::string, std::shared_ptr<Action> > _actions;
                std::map<std::string, std::shared_ptr<Menu> > _menus;
                std::shared_ptr<Label> _textWidget;
                std::shared_ptr<ValueObserver<FontRole> > _fontObserver;
                std::shared_ptr<ValueObserver<std::string> > _textObserver;
            };
        }
    }
}
