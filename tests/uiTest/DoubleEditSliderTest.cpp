// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleEditSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/DoubleEditSlider.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        DoubleEditSliderTest::DoubleEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::DoubleEditSliderTest")
        {}

        DoubleEditSliderTest::~DoubleEditSliderTest()
        {}

        std::shared_ptr<DoubleEditSliderTest> DoubleEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditSliderTest>(new DoubleEditSliderTest(context));
        }
                
        void DoubleEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleEditSliderTest",
                    "Double edit slider test.");
                auto window = Window::create(context, app, "DoubleEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = DoubleEditSlider::create(context, layout);
                DTK_ASSERT(slider->getModel());
                double value = 0.0;
                slider->setCallback([&value](double v) { value = v; });
                slider->setValue(0.9);
                app->tick();
                DTK_ASSERT(0.9 == slider->getValue());
                DTK_ASSERT(0.9 == value);
                slider->setRange(RangeD(0.0, 0.5));
                app->tick();
                DTK_ASSERT(RangeD(0.0, 0.5) == slider->getRange());
                DTK_ASSERT(0.5 == value);
                slider->setStep(0.2);
                DTK_ASSERT(0.2 == slider->getStep());
                slider->setLargeStep(0.3);
                DTK_ASSERT(0.3 == slider->getLargeStep());
                slider->setPrecision(3);
                DTK_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.0);
                DTK_ASSERT(0.0 == slider->getDefaultValue());
                slider->setFontRole(FontRole::Label);
                DTK_ASSERT(FontRole::Label == slider->getFontRole());
                slider->setFontRole(FontRole::Mono);

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);
            }
        }
    }
}

