// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/GroupBox.h>
#include <dtk/ui/DoubleEditSlider.h>
#include <dtk/ui/FloatEditSlider.h>
#include <dtk/ui/IntEditSlider.h>
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
        auto app = App::create(context, args, "sliders", "Sliders example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "sliders",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setVStretch(Stretch::Expanding);
        scrollWidget->setWidget(layout);
        window->setWidget(scrollWidget);

        // Create integer sliders.
        auto groupBox = GroupBox::create(context, "Integer Sliders", layout);
        auto vLayout = VerticalLayout::create(context, groupBox);
        auto intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setRange(RangeI(100, 200));
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });
        intEditSlider = IntEditSlider::create(context, vLayout);
        intEditSlider->setRange(RangeI(-100, 100));
        intEditSlider->setCallback(
            [](int value)
            {
                std::cout << Format("Int: {0}").arg(value) << std::endl;
            });

        // Create float sliders.
        groupBox = GroupBox::create(context, "Float Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setRange(RangeF(100.F, 200.F));
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });
        floatEditSlider = FloatEditSlider::create(context, vLayout);
        floatEditSlider->setRange(RangeF(-100.F, 100.F));
        floatEditSlider->setCallback(
            [](float value)
            {
                std::cout << Format("Float: {0}").arg(value) << std::endl;
            });

        // Create double sliders.
        groupBox = GroupBox::create(context, "Double Sliders", layout);
        vLayout = VerticalLayout::create(context, groupBox);
        auto doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setRange(RangeD(100.0, 200.0));
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
            });
        doubleEditSlider = DoubleEditSlider::create(context, vLayout);
        doubleEditSlider->setRange(RangeD(-100.0, 100.0));
        doubleEditSlider->setCallback(
            [](double value)
            {
                std::cout << Format("Double: {0}").arg(value) << std::endl;
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

