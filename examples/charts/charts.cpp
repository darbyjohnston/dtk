// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/PieChart.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/ScrollWidget.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "charts", "Charts example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        auto window = MainWindow::create(
            context,
            app,
            "charts",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setWidget(layout);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create pie charts.
        auto hLayout = HorizontalLayout::create(context, layout);
        auto pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(100.F, Color4F(.8F, .2F, 0.F))
            });
        pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(50.F, Color4F(.8F, .2F, 0.F)),
                PieChartData(50.F, Color4F(.9F, .7F, .1F))
            });
        pieChart = PieChart::create(context, hLayout);
        pieChart->setData(
            {
                PieChartData(40.F, Color4F(.8F, .2F, 0.F)),
                PieChartData(30.F, Color4F(.9F, .7F, .1F)),
                PieChartData(15.F, Color4F(0.F, .8F, .3F)),
                PieChartData(10.F, Color4F(.2F, .2F, .9F)),
                PieChartData(5.F, Color4F(.5F, .1F, .8F))
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

