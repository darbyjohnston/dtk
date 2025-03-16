// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/FormLayout.h>
#include <dtk/ui/GridLayout.h>
#include <dtk/ui/GroupBox.h>
#include <dtk/ui/IntEdit.h>
#include <dtk/ui/IntEditSlider.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>

#include <dtk/core/Format.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "layouts", "Layouts example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "layouts",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the window layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create row layouts.
        auto groupBox = GroupBox::create(context, "Row Layouts", layout);
        auto groupLayout = HorizontalLayout::create(context, groupBox);
        auto hLayout = HorizontalLayout::create(context, groupLayout);
        auto label = Label::create(context, "One", hLayout);
        label = Label::create(context, "Two", hLayout);
        hLayout->addSpacer();
        label = Label::create(context, "Three", hLayout);
        auto vLayout = VerticalLayout::create(context, groupLayout);
        label = Label::create(context, "One", vLayout);
        label = Label::create(context, "Two", vLayout);
        vLayout->addSpacer();
        label = Label::create(context, "Three", vLayout);

        // Create grid layouts.
        groupBox = GroupBox::create(context, "Grid Layouts", layout);
        groupLayout = HorizontalLayout::create(context, groupBox);
        auto gridLayout = GridLayout::create(context, groupLayout);
        label = Label::create(context, "One", gridLayout);
        gridLayout->setGridPos(label, 0, 0);
        label = Label::create(context, "Two", gridLayout);
        gridLayout->setGridPos(label, 0, 1);
        label = Label::create(context, "Three", gridLayout);
        gridLayout->setGridPos(label, 1, 0);
        label = Label::create(context, "Four", gridLayout);
        gridLayout->setGridPos(label, 1, 1);

        // Create form layouts.
        groupBox = GroupBox::create(context, "Form Layouts", layout);
        groupLayout = HorizontalLayout::create(context, groupBox);
        auto formLayout = FormLayout::create(context, groupLayout);
        formLayout->setHStretch(Stretch::Expanding);
        formLayout->addRow("One:", IntEditSlider::create(context));
        formLayout->addRow("Two:", IntEditSlider::create(context));
        formLayout->addSpacer(SizeRole::Spacing);
        formLayout->addRow("Three:", IntEdit::create(context));

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

