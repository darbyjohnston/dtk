// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

DTK_MAIN()
{
    try
    {
        auto context = dtk::core::Context::create();
        auto args = dtk::app::convert(argc, argv);
        auto app = dtk::examples::textedit::App::create(context, args);
        if (app->getExit() != 0)
            return app->getExit();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
