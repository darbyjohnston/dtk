// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/DoubleSlider.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        DoubleSliderTest::DoubleSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::DoubleSliderTest")
        {}

        DoubleSliderTest::~DoubleSliderTest()
        {}

        std::shared_ptr<DoubleSliderTest> DoubleSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleSliderTest>(new DoubleSliderTest(context));
        }
                
        void DoubleSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleSliderTest",
                    "Double slider test.");
                auto window = Window::create(context, app, "DoubleSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = DoubleSlider::create(context, nullptr, layout);
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

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                DTK_ASSERT(value == 0.0);
                window->setKey(Key::Right);
                DTK_ASSERT(fuzzyCompare(value, 0.2));
                window->setKey(Key::PageUp);
                DTK_ASSERT(fuzzyCompare(value, 0.5));
                window->setKey(Key::Left);
                DTK_ASSERT(fuzzyCompare(value, 0.3));
                window->setKey(Key::PageDown);
                DTK_ASSERT(fuzzyCompare(value, 0.0));
                window->setKey(Key::End);
                DTK_ASSERT(value == 0.5);
                window->setKey(Key::Escape);
                DTK_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

