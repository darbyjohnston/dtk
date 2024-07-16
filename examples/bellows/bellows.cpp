// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIApp/App.h>
#include <dtkUIApp/Window.h>

#include <dtkUI/Bellows.h>
#include <dtkUI/CheckBox.h>
#include <dtkUI/PushButton.h>
#include <dtkUI/RowLayout.h>
#include <dtkUI/ScrollWidget.h>
#include <dtkUI/ToolButton.h>

#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = dtk::app::convert(argc, argv);
        auto app = App::create(context, args, "bellows", "Bellows example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = Window::create(
            context,
            "bellows",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setSpacingRole(SizeRole::None);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setWidget(layout);

        // Add a bellows.
        auto vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::SpacingSmall);
        for (size_t i = 0; i < 10; ++i)
        {
            PushButton::create(context, Format("Push Button {0}").arg(i), vLayout);
        }
        auto bellows = Bellows::create(context, "Push Buttons", layout);
        bellows->setWidget(vLayout);

        // Add a bellows.
        vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::None);
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
            auto button = ToolButton::create(context, Format("Tool Button {0}").arg(i), vLayout);
            if (i < icons.size())
            {
                button->setIcon(icons[i]);
            }
        }
        bellows = Bellows::create(context, "Tool Buttons", layout);
        bellows->setWidget(vLayout);

        // Add a bellows.
        vLayout = VerticalLayout::create(context);
        vLayout->setMarginRole(SizeRole::Margin);
        vLayout->setSpacingRole(SizeRole::None);
        for (size_t i = 0; i < 10; ++i)
        {
            CheckBox::create(context, Format("Check Box {0}").arg(i), vLayout);
        }
        bellows = Bellows::create(context, "Check Boxes", layout);
        bellows->setWidget(vLayout);

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

