// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/App.h>

#include <uiTest/Window.h>

#include <dtk/ui/IconLibrary.h>
#include <dtk/ui/Init.h>
#include <dtk/ui/Style.h>

#include <dtk/core/LogSystem.h>
#include <dtk/core/Time.h>
#include <dtk/core/Timer.h>

namespace dtk
{
    namespace ui_test
    {
        namespace
        {
            const std::chrono::milliseconds timeout(5);
        }

        struct App::Private
        {
            float displayScale = 1.F;
            std::shared_ptr<FontSystem> fontSystem;
            std::shared_ptr<Style> style;
            std::shared_ptr<IconLibrary> iconLibrary;
            bool running = true;
            std::list<std::shared_ptr<Window> > windows;
            std::shared_ptr<Timer> logTimer;
        };

        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
        {
            IApp::_init(
                context,
                argv,
                name,
                summary,
                cmdLineArgs,
                cmdLineOptions);
            DTK_P();
            uiInit(context);

            p.fontSystem = context->getSystem<FontSystem>();
            p.style = Style::create(context);
            p.iconLibrary = IconLibrary::create(context);

            p.logTimer = Timer::create(context);
            p.logTimer->setRepeating(true);
            auto weak = std::weak_ptr<App>(std::dynamic_pointer_cast<App>(shared_from_this()));
            p.logTimer->start(
                std::chrono::seconds(10),
                [weak]
                {
                    if (auto app = weak.lock())
                    {
                        app->_log();
                    }
                });
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}

        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
            const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions);
            return out;
        }

        void App::addWindow(const std::shared_ptr<Window>& window)
        {
            DTK_P();
            p.windows.push_back(window);
        }

        void App::removeWindow(const std::shared_ptr<Window>& window)
        {
            DTK_P();
            const auto i = std::find(p.windows.begin(), p.windows.end(), window);
            if (i != p.windows.end())
            {
                p.windows.erase(i);
            }
        }

        const std::list<std::shared_ptr<Window> >& App::getWindows() const
        {
            return _p->windows;
        }

        const std::shared_ptr<FontSystem>& App::getFontSystem() const
        {
            return _p->fontSystem;
        }

        const std::shared_ptr<Style>& App::getStyle() const
        {
            return _p->style;
        }

        const std::shared_ptr<IconLibrary>& App::getIconLibrary() const
        {
            return _p->iconLibrary;
        }

        void App::setDisplayScale(float value)
        {
            DTK_P();
            if (value == p.displayScale)
                return;
            p.displayScale = value;
            for (auto& window : p.windows)
            {
                window->setDisplayScale(p.displayScale);
            }
            run();
        }

        void App::tick(size_t count)
        {
            DTK_P();
            for (size_t i = 0; i < count; ++i)
            {
                _context->tick();
                for (auto& window : p.windows)
                {
                    TickEvent tickEvent;
                    _tickRecursive(window, true, true, tickEvent);
                    window->update(p.fontSystem, p.style, p.iconLibrary);
                }
            }
        }

        void App::exit()
        {
            _p->running = false;
        }

        void App::run()
        {
            DTK_P();
            if (p.running && !p.windows.empty())
            {
                tick();
            }
        }

        void App::_tickRecursive(
            const std::shared_ptr<IWidget>& widget,
            bool visible,
            bool enabled,
            const TickEvent& event)
        {
            DTK_P();
            const bool parentsVisible = visible && widget->isVisible(false);
            const bool parentsEnabled = enabled && widget->isEnabled(false);
            for (const auto& child : widget->getChildren())
            {
                _tickRecursive(
                    child,
                    parentsVisible,
                    parentsEnabled,
                    event);
            }
            widget->tickEvent(visible, enabled, event);
        }

        void App::_log()
        {}
    }
}

