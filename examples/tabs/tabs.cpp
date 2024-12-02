// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/ScrollWidget.h>
#include <dtk/ui/TabWidget.h>
#include <dtk/ui/Window.h>

#include <dtk/core/Format.h>
#include <dtk/core/String.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "tabs", "Tabs example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "tabs",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the tab widget.
        auto tabWidget = TabWidget::create(context, window);
        //tabWidget->setTabsClosable(true);

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

