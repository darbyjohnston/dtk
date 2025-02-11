// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Format.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "windows", "Multiple windows example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "windows",
            Size2I(1280, 960));
        app->addWindow(window);
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::MarginLarge);
        window->setWidget(layout);

        // Create the secondary window.
        auto secondaryWindow = Window::create(context, "Secondary Window", Size2I(1280, 960));
        auto label = Label::create(context, "Secondary Window", secondaryWindow);
        label->setAlign(HAlign::Center, VAlign::Center);
        app->addWindow(secondaryWindow);

        // Create a button to open the secondary window.
        auto button = PushButton::create(context, "Secondary Window", layout);
        button->setCheckable(true);

        // Setup callbacks.
        window->setCloseCallback(
            [secondaryWindow]
            {
                secondaryWindow->hide();
            });
        secondaryWindow->setCloseCallback(
            [&button]
            {
                button->setChecked(false);
            });
        button->setCheckedCallback(
            [&secondaryWindow, &button](bool value)
            {
                secondaryWindow->setVisible(value);
            });

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

