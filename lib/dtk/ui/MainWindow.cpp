// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/MainWindow.h>

#include <dtk/ui/Action.h>
#include <dtk/ui/App.h>
#include <dtk/ui/Divider.h>
#include <dtk/ui/MenuBar.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    struct MainWindow::Private
    {
        std::weak_ptr<App> app;
        std::shared_ptr<MenuBar> menuBar;
        std::shared_ptr<Divider> menuBarDivider;
        std::shared_ptr<IWidget> centralWidget;
        std::shared_ptr<VerticalLayout> layout;
        std::shared_ptr<VerticalLayout> centralLayout;
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

        p.menuBarDivider = Divider::create(context, Orientation::Vertical);

        p.layout = VerticalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::None);
        p.menuBar->setParent(p.layout);
        p.menuBarDivider->setParent(p.layout);
        p.centralLayout = VerticalLayout::create(context, p.layout);
        p.centralLayout->setSpacingRole(SizeRole::None);
        p.centralLayout->setVStretch(Stretch::Expanding);
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