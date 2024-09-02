// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/PieChartTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/PieChart.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        PieChartTest::PieChartTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::PieChartTest")
        {}

        PieChartTest::~PieChartTest()
        {}

        std::shared_ptr<PieChartTest> PieChartTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<PieChartTest>(new PieChartTest(context));
        }
                
        void PieChartTest::run()
        {
            {
                PieChartData a;
                PieChartData b;
                b.percentage = 50.F;
                DTK_ASSERT(a == a);
                DTK_ASSERT(a != b);
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("PieChartTest");
                auto app = App::create(
                    context,
                    argv,
                    "PieChartTest",
                    "Pie chart test.");
                auto window = Window::create(context, app, "PieChartTest");
                auto layout = HorizontalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = PieChart::create(context, layout);
                std::vector<PieChartData> data;
                data.push_back(PieChartData(60.F, Color4F(1.F, 0.F, 0.F)));
                data.push_back(PieChartData(30.F, Color4F(1.F, .8F, 0.F)));
                data.push_back(PieChartData(10.F, Color4F(.8F, 1.F, 0.F)));
                widget->setData(data);
                widget->setData(data);
                DTK_ASSERT(data == widget->getData());
                app->tick();
                widget->setSizeMult(2);
                widget->setSizeMult(2);
                DTK_ASSERT(2 == widget->getSizeMult());
                app->tick();
            }
        }
    }
}

