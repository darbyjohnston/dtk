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
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "simple", "Simple example");
        if (app->getExit() != 0)
            return app->getExit();

        auto window = MainWindow::create(context, app, "simple", Size2I(1280, 960));
        app->addWindow(window);

        auto label = Label::create(context, "Hello world");
        label->setAlign(HAlign::Center, VAlign::Center);
        label->setStretch(Stretch::Expanding);
        window->setWidget(label);

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

