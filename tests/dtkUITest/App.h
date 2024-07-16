// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkBaseApp/IApp.h>

#include <list>

namespace dtk
{
    namespace core
    {
        class FontSystem;
    }

    namespace ui
    {
        class IWidget;
        class IconLibrary;
        class Style;
        class TickEvent;
    }

    namespace ui_test
    {
        class Window;

        class App : public app::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            App();

        public:
            virtual ~App();

            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<app::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<app::ICmdLineOption> >& = {});

            void addWindow(const std::shared_ptr<Window>&);
            void removeWindow(const std::shared_ptr<Window>&);
            const std::list<std::shared_ptr<Window> >& getWindows() const;

            const std::shared_ptr<core::FontSystem>& getFontSystem() const;
            const std::shared_ptr<ui::Style>& getStyle() const;
            const std::shared_ptr<ui::IconLibrary>& getIconLibrary() const;
            void setDisplayScale(float);

            void tick(size_t count = 1);
            void exit();

            void run() override;

        private:
            void _tickRecursive(
                const std::shared_ptr<ui::IWidget>&,
                bool visible,
                bool enabled,
                const ui::TickEvent&);
            
            void _log();

            DTK_PRIVATE();
        };
    }
}
