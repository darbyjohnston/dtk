// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/Splitter.h>

#include <dtk/core/Format.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "splitters", "splitters example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "splitters",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the splitters.
        auto splitter = Splitter::create(context, Orientation::Vertical);
        auto splitter2 = Splitter::create(context, Orientation::Horizontal, splitter);
        auto label = Label::create(context, "Label 1", splitter2);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Label 2", splitter2);
        label->setAlign(HAlign::Center, VAlign::Center);
        label = Label::create(context, "Label 3", splitter);
        label->setAlign(HAlign::Center, VAlign::Center);
        window->setWidget(splitter);

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

