// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/MainWindow.h>

#include <dtk/ui/Action.h>
#include <dtk/ui/App.h>
#include <dtk/ui/Divider.h>
#include <dtk/ui/MenuBar.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/core/Format.h>

namespace dtk
{
    struct MainWindow::Private
    {
        std::weak_ptr<App> app;
        std::shared_ptr<MenuBar> menuBar;
        std::map<std::string, std::shared_ptr<Menu> > menus;
        std::vector<float> displayScales = { 1.F, 1.5F, 2.F, 2.5F, 3.F, 3.5F, 4.F };
        std::map<float, std::shared_ptr<Action> > displayScaleActions;
        std::map<ColorStyle, std::shared_ptr<Action> > colorStyleActions;
        std::shared_ptr<Divider> menuBarDivider;
        std::shared_ptr<IWidget> centralWidget;
        std::shared_ptr<VerticalLayout> layout;
        std::shared_ptr<VerticalLayout> centralLayout;

        std::shared_ptr<ValueObserver<float> > displayScaleObserver;
        std::shared_ptr<ValueObserver<ColorStyle> > colorStyleObserver;
    };

    void MainWindow::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::string& name,
        const Size2I& size)
    {
        Window::_init(context, name, size);
        DTK_P();

        p.app = app;

        p.menuBar = MenuBar::create(context);
        auto fileMenu = Menu::create(context);
        fileMenu->addItem(std::make_shared<Action>(
            "Exit",
            Key::Q,
            static_cast<int>(commandKeyModifier),
            [this]
            {
                if (auto app = _p->app.lock())
                {
                    app->exit();
                }
            }));
        p.menuBar->addMenu("File", fileMenu);

        auto windowMenu = Menu::create(context);
        windowMenu->addItem(std::make_shared<Action>(
            "Full Screen",
            Key::U,
            static_cast<int>(commandKeyModifier),
            [this](bool value)
            {
                setFullScreen(value);
            }));

        p.menus["DisplayScale"] = windowMenu->addSubMenu("Display Scale");
        p.displayScaleActions[0.F] = std::make_shared<Action>(
            "Automatic",
            [this](bool)
            {
                setDisplayScale(0.F);
            });
        p.menus["DisplayScale"]->addItem(p.displayScaleActions[0.F]);
        for (auto displayScale : p.displayScales)
        {
            p.displayScaleActions[displayScale] = std::make_shared<Action>(
                Format("{0}").arg(displayScale),
                [this, displayScale](bool)
                {
                    setDisplayScale(displayScale);
                });
            p.menus["DisplayScale"]->addItem(p.displayScaleActions[displayScale]);
        }

        p.menus["ColorStyle"] = windowMenu->addSubMenu("Color Style");
        p.colorStyleActions[ColorStyle::Dark] = std::make_shared<Action>(
            "Dark",
            [this]
            {
                if (auto app = _p->app.lock())
                {
                    app->setColorStyle(ColorStyle::Dark);
                }
            });
        p.menus["ColorStyle"]->addItem(p.colorStyleActions[ColorStyle::Dark]);
        p.colorStyleActions[ColorStyle::Light] = std::make_shared<Action>(
            "Light",
            [this]
            {
                if (auto app = _p->app.lock())
                {
                    app->setColorStyle(ColorStyle::Light);
                }
            });
        p.menus["ColorStyle"]->addItem(p.colorStyleActions[ColorStyle::Light]);

        p.menuBar->addMenu("Window", windowMenu);

        p.menuBarDivider = Divider::create(context, Orientation::Vertical);

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
        p.menuBar->setParent(p.layout);
        p.menuBarDivider->setParent(p.layout);
        p.centralLayout = VerticalLayout::create(context, p.layout);
        p.centralLayout->setSpacingRole(SizeRole::None);
        p.centralLayout->setVStretch(Stretch::Expanding);

        p.displayScaleObserver = ValueObserver<float>::create(
            observeDisplayScale(),
            [this](float value)
            {
                for (auto displayScale : _p->displayScales)
                {
                    _p->menus["DisplayScale"]->setItemChecked(
                        _p->displayScaleActions[displayScale],
                        displayScale == value);
                }
            });

        p.colorStyleObserver = ValueObserver<ColorStyle>::create(
            app->observeColorStyle(),
            [this](ColorStyle value)
            {
                _p->menus["ColorStyle"]->setItemChecked(_p->colorStyleActions[ColorStyle::Dark], ColorStyle::Dark == value);
                _p->menus["ColorStyle"]->setItemChecked(_p->colorStyleActions[ColorStyle::Light], ColorStyle::Light == value);
            });
    }

    MainWindow::MainWindow() :
        _p(new Private)
    {}

    MainWindow::~MainWindow()
    {}

    std::shared_ptr<MainWindow> MainWindow::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<App>& app,
        const std::string& name,
        const Size2I& size)
    {
        auto out = std::shared_ptr<MainWindow>(new MainWindow);
        out->_init(context, app, name, size);
        return out;
    }

    const std::shared_ptr<MenuBar>& MainWindow::getMenuBar() const
    {
        return _p->menuBar;
    }

    void MainWindow::setWidget(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        if (p.centralWidget)
        {
            p.centralWidget->setParent(nullptr);
        }
        p.centralWidget = value;
        if (p.centralWidget)
        {
            p.centralWidget->setParent(p.centralLayout);
        }
    }

    void MainWindow::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        event.accept = p.menuBar->shortcut(event.key, event.modifiers);
    }

    void MainWindow::keyReleaseEvent(KeyEvent& event)
    {
        event.accept = true;
    }

    const std::shared_ptr<App> MainWindow::_getApp() const
    {
        return _p->app.lock();
    }
}