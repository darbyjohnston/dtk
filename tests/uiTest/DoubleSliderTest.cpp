// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/DoubleSlider.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        DoubleSliderTest::DoubleSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::DoubleSliderTest")
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

                auto slider = DoubleSlider::create(context, layout);
                FEATHER_TK_ASSERT(slider->getModel());
                double value = 0.0;
                slider->setCallback([&value](double v) { value = v; });
                slider->setValue(0.9);
                app->tick();
                FEATHER_TK_ASSERT(0.9 == slider->getValue());
                FEATHER_TK_ASSERT(0.9 == value);
                slider->setRange(0.0, 0.5);
                app->tick();
                FEATHER_TK_ASSERT(RangeD(0.0, 0.5) == slider->getRange());
                FEATHER_TK_ASSERT(0.5 == value);
                slider->setStep(0.2);
                FEATHER_TK_ASSERT(0.2 == slider->getStep());
                slider->setLargeStep(0.3);
                FEATHER_TK_ASSERT(0.3 == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                FEATHER_TK_ASSERT(value == 0.0);
                window->setKey(Key::Right);
                FEATHER_TK_ASSERT(fuzzyCompare(value, 0.2));
                window->setKey(Key::PageUp);
                FEATHER_TK_ASSERT(fuzzyCompare(value, 0.5));
                window->setKey(Key::Left);
                FEATHER_TK_ASSERT(fuzzyCompare(value, 0.3));
                window->setKey(Key::PageDown);
                FEATHER_TK_ASSERT(fuzzyCompare(value, 0.0));
                window->setKey(Key::End);
                FEATHER_TK_ASSERT(value == 0.5);
                window->setKey(Key::Escape);
                FEATHER_TK_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

