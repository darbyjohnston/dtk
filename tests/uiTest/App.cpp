// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/App.h>

#include <uiTest/Window.h>

#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Init.h>
#include <feather-tk/ui/Style.h>

#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/Time.h>
#include <feather-tk/core/Timer.h>

namespace feather_tk
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
            std::shared_ptr<IconSystem> iconSystem;
            std::shared_ptr<Style> style;
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
            FEATHER_TK_P();
            uiInit(context);

            p.fontSystem = context->getSystem<FontSystem>();
            p.iconSystem = context->getSystem<IconSystem>();
            p.style = Style::create(context);

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
            FEATHER_TK_P();
            p.windows.push_back(window);
        }

        void App::removeWindow(const std::shared_ptr<Window>& window)
        {
            FEATHER_TK_P();
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

        const std::shared_ptr<IconSystem>& App::getIconSystem() const
        {
            return _p->iconSystem;
        }

        const std::shared_ptr<Style>& App::getStyle() const
        {
            return _p->style;
        }

        void App::setDisplayScale(float value)
        {
            FEATHER_TK_P();
            if (value == p.displayScale)
                return;
            p.displayScale = value;
            for (auto& window : p.windows)
            {
                window->setDisplayScale(p.displayScale);
            }
        }

        void App::tick(size_t count)
        {
            FEATHER_TK_P();
            for (size_t i = 0; i < count; ++i)
            {
                _context->tick();
                for (auto& window : p.windows)
                {
                    TickEvent tickEvent;
                    _tickRecursive(window, true, true, tickEvent);
                    window->update(p.fontSystem, p.iconSystem, p.style);
                }
            }
        }

        void App::exit()
        {
            _p->running = false;
        }

        void App::run()
        {
            FEATHER_TK_P();
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
            FEATHER_TK_P();
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

