// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "simple", "Simple example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(context, app, "simple", Size2I(1280, 960));

        // Create a label.
        auto label = Label::create(context, "Hello world");
        label->setFontRole(FontRole::Title);
        label->setAlign(HAlign::Center, VAlign::Center);
        label->setStretch(Stretch::Expanding);
        window->setWidget(label);

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

