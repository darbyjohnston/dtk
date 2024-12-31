// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "dock.h"

#include <dtk/ui/App.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Splitter.h>
#include <dtk/ui/ToolButton.h>

#include <dtk/core/Format.h>

using namespace dtk;

int widgetCount = 0;

void createWidget(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto layout = VerticalLayout::create(context, parent);
    layout->setBackgroundRole(ColorRole::Blue);
    auto label = Label::create(context, Format("Widget {0}").arg(widgetCount), layout);
    label->setStretch(Stretch::Expanding);
    auto button = ToolButton::create(context, "Close", layout);
    auto layoutWeak = std::weak_ptr<IWidget>(layout);
    button->setClickedCallback(
        [layoutWeak]
        {
            if (auto layout = layoutWeak.lock())
            {
                layout->setParent(nullptr);
            }
        });
    ++widgetCount;
}

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "dock", "Dock layout example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "dock",
            Size2I(1280, 960));
        app->addWindow(window);

        auto layout = VerticalLayout::create(context);
        layout->setSpacingRole(SizeRole::None);
        layout->setVStretch(Stretch::Expanding);
        window->setWidget(layout);

        auto splitter = Splitter::create(context, Orientation::Horizontal, layout);
        createWidget(context, splitter);
        createWidget(context, splitter);
        createWidget(context, splitter);
        auto addButton = ToolButton::create(context, "Add", layout);
        addButton->setClickedCallback(
            [context, splitter]
            {
                createWidget(context, splitter);
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

