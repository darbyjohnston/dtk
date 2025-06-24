// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/App.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/MainWindow.h>
#include <feather-tk/ui/ScrollWidget.h>
#include <feather-tk/ui/TabWidget.h>

#include <feather-tk/core/Format.h>
#include <feather-tk/core/String.h>

using namespace feather_tk;

FEATHER_TK_MAIN()
{
    try
    {
        // Create the context and application.
        auto context = Context::create();
        auto app = App::create(context, argc, argv, "tabs", "Tabs example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create a window.
        auto window = MainWindow::create(
            context,
            app,
            "tabs",
            Size2I(1280, 960));

        // Create a tab widget.
        auto tabWidget = TabWidget::create(context);
        //tabWidget->setTabsClosable(true);
        tabWidget->setVStretch(Stretch::Expanding);
        window->setWidget(tabWidget);

        // Add tabs.
        for (size_t i = 0; i < 10; ++i)
        {
            auto label = Label::create(context, getLoremIpsum(100));
            label->setMarginRole(SizeRole::MarginSmall);
            auto scrollWidget = ScrollWidget::create(context);
            scrollWidget->setBorder(false);
            scrollWidget->setWidget(label);
            tabWidget->addTab(Format("Tab {0}").arg(i), scrollWidget);
        }

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

