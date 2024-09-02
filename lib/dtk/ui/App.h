// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/IApp.h>

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
        class Window;

        //! Base class for user interface applications.
        class App : public core::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<core::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<core::ICmdLineOption> >& = {});

            App();

        public:
            virtual ~App();

            //! Create a new application.
            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<core::ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<core::ICmdLineOption> >& = {});

            //! Add a window.
            void addWindow(const std::shared_ptr<Window>&);

            //! Remove a window.
            void removeWindow(const std::shared_ptr<Window>&);

            //! Get the windows.
            const std::list<std::shared_ptr<Window> >& getWindows() const;

            //! Get the font system.
            const std::shared_ptr<core::FontSystem>& getFontSystem() const;

            //! Get the style.
            const std::shared_ptr<ui::Style>& getStyle() const;

            //! Get the icon library.
            const std::shared_ptr<ui::IconLibrary>& getIconLibrary() const;

            //! Exit the application.
            void exit();

            void run() override;

        private:
            void _tickRecursive(
                const std::shared_ptr<IWidget>&,
                bool visible,
                bool enabled,
                const TickEvent&);
            
            void _log();

            DTK_PRIVATE();
        };
    }
}

