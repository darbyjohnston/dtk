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
    class IconSystem;
    class Style;
    class TickEvent;
    class Window;

    //! Base class for user interface applications.
    class App : public IApp
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            std::vector<std::string>&,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {},
            const std::string& settingsPath = std::string());

        App();

    public:
        virtual ~App();

        //! Create a new application.
        static std::shared_ptr<App> create(
            const std::shared_ptr<Context>&,
            std::vector<std::string>&,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {},
            const std::string& settingsPath = std::string());

        //! Add a window.
        void addWindow(const std::shared_ptr<Window>&);

        //! Remove a window.
        void removeWindow(const std::shared_ptr<Window>&);

        //! Get the windows.
        const std::list<std::shared_ptr<Window> >& getWindows() const;

        //! Get the font system.
        const std::shared_ptr<FontSystem>& getFontSystem() const;

        //! Get the icon system.
        const std::shared_ptr<IconSystem>& getIconSystem() const;

        //! Get the style.
        const std::shared_ptr<Style>& getStyle() const;

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
