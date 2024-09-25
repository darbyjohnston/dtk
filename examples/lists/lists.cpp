// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/ListWidget.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>
#include <dtk/ui/Window.h>

#include <dtk/core/Format.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "lists", "Lists example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "lists",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);

        // Create a clickable list widget.
        auto listWidget = ListWidget::create(context, ButtonGroupType::Click, layout);
        std::vector<std::string> items;
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Click {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Click: " << index << std::endl;
            });

        // Create a checkable list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Check, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Check {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setChecked(1);
        listWidget->setChecked(2);
        listWidget->setChecked(4);
        listWidget->setCallback(
            [](int index, bool value)
            {
                std::cout << "Check: " << index << std::endl;
            });

        // Create a radio button list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Radio, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Radio {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Radio: " << index << std::endl;
            });

        // Create a toggle button list widget.
        listWidget = ListWidget::create(context, ButtonGroupType::Toggle, layout);
        items.clear();
        for (size_t i = 0; i < 100; ++i)
        {
            items.push_back(Format("Toggle {0}").arg(i));
        }
        listWidget->setItems(items);
        listWidget->setChecked(0);
        listWidget->setCallback(
            [](int index, bool)
            {
                std::cout << "Toggle: " << index << std::endl;
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

