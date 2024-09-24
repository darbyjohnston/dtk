// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/CheckBox.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>
#include <dtk/ui/TabWidget.h>
#include <dtk/ui/ToolButton.h>
#include <dtk/ui/Window.h>

#include <dtk/core/Format.h>

using namespace dtk;

std::shared_ptr<IWidget> createPushButtonTab(
    const std::shared_ptr<Context>& context)
{
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    layout->setSpacingRole(SizeRole::SpacingSmall);
    for (size_t i = 0; i < 10; ++i)
    {
        PushButton::create(context, Format("Push Button {0}").arg(i), layout);
    }
    auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
    scrollWidget->setWidget(layout);
    return scrollWidget;
}

std::shared_ptr<IWidget> createToolButtonTab(
    const std::shared_ptr<Context>& context)
{
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    layout->setSpacingRole(SizeRole::None);
    const std::vector<std::string> icons =
    {
        "Audio",
        "Close",
        "Copy",
        "Directory",
        "File",
        "FrameNext",
        "FramePrev",
        "Mute",
        "Search",
        "Volume"
    };
    for (size_t i = 0; i < 10; ++i)
    {
        auto button = ToolButton::create(context, Format("Tool Button {0}").arg(i), layout);
        if (i < icons.size())
        {
            button->setIcon(icons[i]);
        }
    }
    auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
    scrollWidget->setWidget(layout);
    return scrollWidget;
}

std::shared_ptr<IWidget> createCheckBoxesTab(
    const std::shared_ptr<Context>& context)
{
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    layout->setSpacingRole(SizeRole::None);
    for (size_t i = 0; i < 10; ++i)
    {
        CheckBox::create(context, Format("Check Box {0}").arg(i), layout);
    }
    auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
    scrollWidget->setWidget(layout);
    return scrollWidget;
}

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
        tabWidget->setTabsClosable(true);

        // Create tabs.
        for (size_t i = 0; i < 5; ++i)
        {
            tabWidget->addTab(
                Format("Push Buttons {0}").arg(i),
                createPushButtonTab(context));
        }
        for (size_t i = 0; i < 5; ++i)
        {
            tabWidget->addTab(
                Format("Tool Buttons {0}").arg(i),
                createToolButtonTab(context));
        }
        for (size_t i = 0; i < 5; ++i)
        {
            tabWidget->addTab(
                Format("Check Boxes {0}").arg(i),
                createCheckBoxesTab(context));
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

