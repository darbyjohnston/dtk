// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUIApp/App.h>

#include <dtkUI/Style.h>

#include <dtkCore/ObservableValue.h>

#include <filesystem>

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            class Window;

            class App : public ui::App
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App() = default;

                static std::shared_ptr<App> create(
                    const std::shared_ptr<core::Context>&,
                    std::vector<std::string>& argv);

                std::shared_ptr<core::IObservableValue<ui::FontRole> > observeFont() const;

                void setFont(ui::FontRole);

                std::shared_ptr<core::IObservableValue<std::string> > observeText() const;

                void open(const std::filesystem::path&);

            private:
                std::filesystem::path _path;
                std::shared_ptr<core::ObservableValue<ui::FontRole> > _font;
                std::shared_ptr<core::ObservableValue<std::string> > _text;
                std::shared_ptr<Window> _window;
            };
        }
    }
}
