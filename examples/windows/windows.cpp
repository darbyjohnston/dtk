// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/PushButton.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Format.h>

using namespace feather_tk;

FEATHER_TK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "windows", "Multiple windows example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "windows",
            Size2I(1280, 960));
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::MarginLarge);
        window->setWidget(layout);

        // Create a secondary window.
        auto secondaryWindow = Window::create(context, "Secondary Window", Size2I(1280, 960));
        auto secondaryLayout = VerticalLayout::create(context, secondaryWindow);
        secondaryLayout->setAlign(HAlign::Center, VAlign::Center);
        auto label = Label::create(context, "Secondary Window", secondaryLayout);
        auto fullScreenButton = PushButton::create(context, "Full Screen", secondaryLayout);
        fullScreenButton->setCheckable(true);
        app->addWindow(secondaryWindow);

        // Create a button to open the secondary window.
        auto button = PushButton::create(context, "Secondary Window", layout);
        button->setCheckable(true);

        // Setup callbacks.
        window->setCloseCallback(
            [&secondaryWindow]
            {
                secondaryWindow->hide();
            });
        secondaryWindow->setCloseCallback(
            [&button]
            {
                button->setChecked(false);
            });
        fullScreenButton->setCheckedCallback(
            [&secondaryWindow](bool value)
            {
                secondaryWindow->setFullScreen(value);
            });
        button->setCheckedCallback(
            [&secondaryWindow, &button](bool value)
            {
                secondaryWindow->setVisible(value);
            });

        // Show the window and run the application.
        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

