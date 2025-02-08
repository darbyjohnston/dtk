// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>

#include <dtk/ui/IconSystem.h>
#include <dtk/ui/Init.h>
#include <dtk/ui/Style.h>
#include <dtk/ui/Window.h>

#include <dtk/gl/Init.h>

#include <dtk/core/CmdLine.h>
#include <dtk/core/Context.h>
#include <dtk/core/Error.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>
#include <dtk/core/String.h>
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

    DTK_ENUM_IMPL(
        ColorStyle,
        "Dark",
        "Light");

    struct App::Private
    {
        bool exit = false;
        std::shared_ptr<FontSystem> fontSystem;
        std::shared_ptr<IconSystem> iconSystem;
        std::shared_ptr<Style> style;
        std::shared_ptr<ObservableValue<ColorStyle> > colorStyle;
        bool running = true;
        float displayScale = 0.F;
        std::list<std::shared_ptr<Window> > windows;
        std::shared_ptr<ObservableValue<std::shared_ptr<Window> > > windowClose;
        std::list<int> tickTimes;
        std::shared_ptr<Timer> logTimer;
    };

    void App::_init(
        const std::shared_ptr<Context>& context,
        std::vector<std::string>& argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions,
        const std::string& settingsPath)
    {
        std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptionsTmp;
        cmdLineOptionsTmp.push_back(CmdLineFlagOption::create(
            _p->exit,
            { "-exit" },
            "Start the user interface and then exit."));
        cmdLineOptionsTmp.push_back(CmdLineValueOption<float>::create(
            _p->displayScale,
            { "-displayScale", "-ds" },
            "Set the display scale. A value of 0.0 sets the scale automatically."));
        ColorStyle colorStyle = ColorStyle::Dark;
        cmdLineOptionsTmp.push_back(CmdLineValueOption<ColorStyle>::create(
            colorStyle,
            { "-colorStyle", "-cs" },
            "Set the color style.",
            getLabel(colorStyle),
            join(getColorStyleLabels(), ", ")));
        cmdLineOptionsTmp.insert(cmdLineOptionsTmp.end(), cmdLineOptions.begin(), cmdLineOptions.end());
        IApp::_init(
            context,
            argv,
            name,
            summary,
            cmdLineArgs,
            cmdLineOptionsTmp);
        DTK_P();
        uiInit(context, settingsPath);
        gl::init(context);

        p.fontSystem = context->getSystem<FontSystem>();
        p.iconSystem = context->getSystem<IconSystem>();
        p.style = Style::create(context);
        p.colorStyle = ObservableValue<ColorStyle>::create(colorStyle);
        p.windowClose = ObservableValue<std::shared_ptr<Window> >::create();

        _styleUpdate();

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
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions,
        const std::string& settingsPath)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, argv, name, summary, cmdLineArgs, cmdLineOptions, settingsPath);
        return out;
    }

    void App::addWindow(const std::shared_ptr<Window>& window)
    {
        DTK_P();
        window->setDisplayScale(p.displayScale);
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

    std::shared_ptr<IObservableValue<std::shared_ptr<Window>> > App::observeWindowClose() const
    {
        return _p->windowClose;
    }

    int App::getScreenCount() const
    {
        int glfwMonitorsCount = 0;
        glfwGetMonitors(&glfwMonitorsCount);
        return glfwMonitorsCount;
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

    ColorStyle App::getColorStyle() const
    {
        return _p->colorStyle->get();
    }

    std::shared_ptr<IObservableValue<ColorStyle> > App::observeColorStyle() const
    {
        return _p->colorStyle;
    }

    void App::setColorStyle(ColorStyle value)
    {
        DTK_P();
        if (p.colorStyle->setIfChanged(value))
        {
            _styleUpdate();
        }
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

            _tick();

            auto i = p.windows.begin();
            while (i != p.windows.end())
            {
                TickEvent tickEvent;
                _tickRecursive(
                    *i,
                    (*i)->isVisible(false),
                    (*i)->isEnabled(false),
                    tickEvent);

                (*i)->update(p.fontSystem, p.iconSystem, p.style);

                if ((*i)->shouldClose())
                {
                    p.windowClose->setAlways(*i);
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

    void App::_tick()
    {}

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

    void App::_styleUpdate()
    {
        DTK_P();
        std::map<ColorRole, Color4F> colorRoles;
        switch (p.colorStyle->get())
        {
        case ColorStyle::Dark: colorRoles = defaultColorRoles(); break;
        case ColorStyle::Light: colorRoles = lightColorRoles(); break;
        default: break;
        }
        p.style->setColorRoles(colorRoles);
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
