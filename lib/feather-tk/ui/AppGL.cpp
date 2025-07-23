// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>

#include <feather-tk/ui/IconSystem.h>
#include <feather-tk/ui/Init.h>
#include <feather-tk/ui/Window.h>

#include <feather-tk/gl/Init.h>

#include <feather-tk/core/Context.h>
#include <feather-tk/core/Error.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LogSystem.h>
#include <feather-tk/core/String.h>
#include <feather-tk/core/Time.h>
#include <feather-tk/core/Timer.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

namespace feather_tk
{
    namespace
    {
        const std::chrono::milliseconds timeout(5);
    }

    FEATHER_TK_ENUM_IMPL(
        ColorStyle,
        "Dark",
        "Light",
        "Custom");

    std::map<ColorRole, Color4F> getCustomColorRoles()
    {
        std::map<ColorRole, Color4F> out = getDefaultColorRoles();
        out[ColorRole::Window] = Color4F(.15F, .15F, .2F);
        out[ColorRole::Button] = Color4F(.2F, .2F, .3F);
        return out;
    }

    struct App::Private
    {
        struct CmdLine
        {
            std::shared_ptr<CmdLineFlagOption> exit;
            std::shared_ptr<CmdLineValueOption<float> > displayScale;
            std::shared_ptr<CmdLineValueOption<ColorStyle> > colorStyle;
        };
        CmdLine cmdLine;

        std::shared_ptr<FontSystem> fontSystem;
        std::shared_ptr<IconSystem> iconSystem;
        std::shared_ptr<Style> style;
        std::shared_ptr<ObservableValue<ColorStyle> > colorStyle;
        std::shared_ptr<ObservableMap<ColorRole, Color4F> > customColorRoles;
        std::shared_ptr<ObservableValue<float> > displayScale;
        std::shared_ptr<ObservableValue<bool> > tooltipsEnabled;
        bool running = true;
        std::list<std::shared_ptr<Window> > windows;
        std::list<int> tickTimes;
        std::shared_ptr<Timer> logTimer;
    };

    void App::_init(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        FEATHER_TK_P();

        std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptionsTmp = cmdLineOptions;
        p.cmdLine.exit = CmdLineFlagOption::create(
            { "-exit" },
            "Start the user interface and then exit.",
            "Testing");
        cmdLineOptionsTmp.push_back(p.cmdLine.exit);
        p.cmdLine.displayScale = CmdLineValueOption<float>::create(
            { "-displayScale", "-ds" },
            "Set the display scale. A value of 0 sets the scale automatically.",
            "Style");
        cmdLineOptionsTmp.push_back(p.cmdLine.displayScale);
        p.cmdLine.colorStyle = CmdLineValueOption<ColorStyle>::create(
            { "-colorStyle", "-cs" },
            "Set the color style.",
            "Style",
            std::optional<ColorStyle>(),
            quotes(getColorStyleLabels()));
        cmdLineOptionsTmp.push_back(p.cmdLine.colorStyle);

        IApp::_init(
            context,
            argv,
            name,
            summary,
            cmdLineArgs,
            cmdLineOptionsTmp);
        uiInit(context);
        gl::init(context);

        p.fontSystem = context->getSystem<FontSystem>();
        p.iconSystem = context->getSystem<IconSystem>();
        p.style = Style::create(context);
        p.colorStyle = ObservableValue<ColorStyle>::create(ColorStyle::Dark);
        if (p.cmdLine.colorStyle->hasValue())
        {
            p.colorStyle->setIfChanged(p.cmdLine.colorStyle->getValue());
        }
        p.customColorRoles = ObservableMap<ColorRole, Color4F>::create(feather_tk::getCustomColorRoles());
        p.displayScale = ObservableValue<float>::create(0.F);
        if (p.cmdLine.displayScale->hasValue())
        {
            p.displayScale->setIfChanged(p.cmdLine.displayScale->getValue());
        }
        p.tooltipsEnabled = ObservableValue<bool>::create(true);

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
        int argc, char** argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, convert(argc, argv), name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    std::shared_ptr<App> App::create(
        const std::shared_ptr<Context>& context,
        int argc, wchar_t* argv[],
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, convert(argc, argv), name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    std::shared_ptr<App> App::create(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& args,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        auto out = std::shared_ptr<App>(new App);
        out->_init(context, args, name, summary, cmdLineArgs, cmdLineOptions);
        return out;
    }

    void App::addWindow(const std::shared_ptr<Window>& window)
    {
        FEATHER_TK_P();
        window->setDisplayScale(p.displayScale->get());
        window->setTooltipsEnabled(p.tooltipsEnabled->get());
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
        FEATHER_TK_P();
        if (p.colorStyle->setIfChanged(value))
        {
            _styleUpdate();
        }
    }

    const std::map<ColorRole, Color4F>& App::getCustomColorRoles() const
    {
        return _p->customColorRoles->get();
    }

    std::shared_ptr<IObservableMap<ColorRole, Color4F> > App::observeCustomColorRoles() const
    {
        return _p->customColorRoles;
    }

    void App::setCustomColorRoles(const std::map<ColorRole, Color4F>& value)
    {
        FEATHER_TK_P();
        if (p.customColorRoles->setIfChanged(value))
        {
            if (ColorStyle::Custom == p.colorStyle->get())
            {
                _styleUpdate();
            }
        }
    }

    const std::shared_ptr<CmdLineValueOption<ColorStyle> >& App::getColorStyleCmdLineOption() const
    {
        return _p->cmdLine.colorStyle;
    }

    float App::getDisplayScale() const
    {
        return _p->displayScale->get();
    }

    std::shared_ptr<IObservableValue<float> > App::observeDisplayScale() const
    {
        return _p->displayScale;
    }

    void App::setDisplayScale(float value)
    {
        FEATHER_TK_P();
        p.displayScale->setIfChanged(value);
        for (const auto& window : p.windows)
        {
            window->setDisplayScale(value);
        }
    }

    const std::shared_ptr<CmdLineValueOption<float> >& App::getDisplayScaleCmdLineOption() const
    {
        return _p->cmdLine.displayScale;
    }

    bool App::areTooltipsEnabled() const
    {
        return _p->tooltipsEnabled->get();
    }

    std::shared_ptr<IObservableValue<bool> > App::observeTooltipsEnabled() const
    {
        return _p->tooltipsEnabled;
    }

    void App::setTooltipsEnabled(bool value)
    {
        FEATHER_TK_P();
        p.tooltipsEnabled->setIfChanged(value);
        for (const auto& window : p.windows)
        {
            window->setTooltipsEnabled(value);
        }
    }

    void App::exit()
    {
        _p->running = false;
    }

    void App::run()
    {
        FEATHER_TK_P();
        auto t0 = std::chrono::steady_clock::now();
        while (p.running && !p.windows.empty())
        {
            glfwPollEvents();

            _context->tick();

            _tick();

            size_t visibleWindows = 0;
            for (const auto& window : p.windows)
            {
                TickEvent tickEvent;
                _tickRecursive(
                    window,
                    window->isVisible(false),
                    window->isEnabled(false),
                    tickEvent);

                if (window->isVisible(false))
                {
                    ++visibleWindows;
                    window->update(p.fontSystem, p.iconSystem, p.style);
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

            if (p.cmdLine.exit->found() || 0 == visibleWindows)
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

    void App::_styleUpdate()
    {
        FEATHER_TK_P();
        std::map<ColorRole, Color4F> colorRoles;
        switch (p.colorStyle->get())
        {
        case ColorStyle::Dark: colorRoles = getDefaultColorRoles(); break;
        case ColorStyle::Light: colorRoles = getLightColorRoles(); break;
        case ColorStyle::Custom: colorRoles = p.customColorRoles->get(); break;
        default: break;
        }
        p.style->setColorRoles(colorRoles);
    }

    void App::_log()
    {
        FEATHER_TK_P();
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
            "feather_tk::App",
            Format("Average tick time: {0}ms").arg(tickAverage));
    }
}
