// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "App.h"

FEATHER_TK_MAIN()
{
    try
    {
        auto context = feather_tk::Context::create();
        auto app = feather_tk::examples::textedit::App::create(context, feather_tk::convert(argc, argv));
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
