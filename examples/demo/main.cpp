// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "DemoWindow.h"

#include <dtk/ui/App.h>

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "bellows", "Bellows example");
        if (app->getExit() != 0)
            return app->getExit();
        auto window = DemoWindow::create(context, app);
        app->addWindow(window);
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

