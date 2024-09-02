// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/IApp.h>

#include <list>

namespace dtk
{
    class FontSystem;
    class IWidget;
    class IconLibrary;
    class Style;
    class TickEvent;

    namespace ui_test
    {
        class Window;

        class App : public IApp
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

            App();

        public:
            virtual ~App();

            static std::shared_ptr<App> create(
                const std::shared_ptr<Context>&,
                std::vector<std::string>&,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
                const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

            void addWindow(const std::shared_ptr<Window>&);
            void removeWindow(const std::shared_ptr<Window>&);
            const std::list<std::shared_ptr<Window> >& getWindows() const;

            const std::shared_ptr<FontSystem>& getFontSystem() const;
            const std::shared_ptr<Style>& getStyle() const;
            const std::shared_ptr<IconLibrary>& getIconLibrary() const;
            void setDisplayScale(float);

            void tick(size_t count = 1);
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
