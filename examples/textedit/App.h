// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/App.h>
#include <dtk/ui/Style.h>

#include <dtk/core/ObservableValue.h>

#include <filesystem>

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            class Window;

            class App : public dtk::App
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App() = default;

                static std::shared_ptr<App> create(
                    const std::shared_ptr<Context>&,
                    const std::vector<std::string>&);

                std::shared_ptr<IObservableValue<FontRole> > observeFont() const;

                void setFont(FontRole);

                std::shared_ptr<IObservableValue<std::string> > observeText() const;

                void open(const std::filesystem::path&);

            private:
                std::string _path;
                std::shared_ptr<ObservableValue<FontRole> > _font;
                std::shared_ptr<ObservableValue<std::string> > _text;
                std::shared_ptr<Window> _window;
            };
        }
    }
}
