// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>

#include <dtk/ui/IconLibrary.h>
#include <dtk/ui/Init.h>
#include <dtk/ui/Style.h>
#include <dtk/ui/Window.h>

#include <dtk/gl/Init.h>

#include <dtk/core/CmdLine.h>
#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>
#include <dtk/core/Time.h>
#include <dtk/core/Timer.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

namespace dtk
{
    namespace
    {
        const std::chrono::milliseconds timeout(5);
    }

    struct App::Private
    {
        bool exit = false;
        std::shared_ptr<FontSystem> fontSystem;
        std::shared_ptr<Style> style;
        std::shared_ptr<IconLibrary> iconLibrary;
        bool running = true;
        std::list<std::shared_ptr<Window> > windows;
        std::list<int> tickTimes;
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
        std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptionsTmp;
        cmdLineOptionsTmp.push_back(CmdLineFlagOption::create(
            _p->exit,
            { "-exit" },
            "Start the user interface and then exit."));
        cmdLineOptionsTmp.insert(cmdLineOptionsTmp.end(), cmdLineOptions.begin(), cmdLineOptions.end());
        IApp::_init(
            context,
            argv,
            name,
            summary,
            cmdLineArgs,
            cmdLineOptionsTmp);
        DTK_P();
        uiInit(context);
        gl::init(context);

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

    void App::exit()
    {
        _p->running = false;
    }

    void App::run()
    {
        DTK_P();
        auto t0 = std::chrono::steady_clock::now();
        while (p.running && !p.windows.empty())
        {
            glfwPollEvents();

            _context->tick();

            auto i = p.windows.begin();
            while (i != p.windows.end())
            {
                TickEvent tickEvent;
                _tickRecursive(
                    *i,
                    (*i)->isVisible(false),
                    (*i)->isEnabled(false),
                    tickEvent);

                (*i)->update(p.fontSystem, p.style, p.iconLibrary);

                if ((*i)->shouldClose())
                {
                    i = p.windows.erase(i);
                }
                else
                {
                    ++i;
                }
            }

            auto t1 = std::chrono::steady_clock::now();
            sleep(timeout, t0, t1);
            t1 = std::chrono::steady_clock::now();
            const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
            p.tickTimes.push_back(diff.count());
            while (p.tickTimes.size() > 10)
            {
                p.tickTimes.pop_front();
            }
            t0 = t1;

            if (p.exit)
            {
                break;
            }
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
    {
        DTK_P();
        double tickAverage = 0.0;
        if (!p.tickTimes.empty())
        {
            for (auto t : p.tickTimes)
            {
                tickAverage += t;
            }
            tickAverage /= static_cast<double>(p.tickTimes.size());
        }
        auto logSystem = _context->getSystem<LogSystem>();
        logSystem->print(
            "dtk::App",
            Format("Average tick time: {0}ms").arg(tickAverage));
    }
}