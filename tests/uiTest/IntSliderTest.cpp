// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/IntSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/IntSlider.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        IntSliderTest::IntSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::IntSliderTest")
        {}

        IntSliderTest::~IntSliderTest()
        {}

        std::shared_ptr<IntSliderTest> IntSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntSliderTest>(new IntSliderTest(context));
        }
                
        void IntSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntSliderTest",
                    "Integer slider test.");
                auto window = Window::create(context, app, "IntSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = IntSlider::create(context, nullptr, layout);
                DTK_ASSERT(slider->getModel());
                int value = 0;
                slider->setCallback([&value](int v) { value = v; });
                slider->setValue(11);
                app->tick();
                DTK_ASSERT(11 == slider->getValue());
                DTK_ASSERT(11 == value);
                slider->setRange(RangeI(0, 10));
                app->tick();
                DTK_ASSERT(RangeI(0, 10) == slider->getRange());
                DTK_ASSERT(10 == value);
                slider->setStep(2);
                DTK_ASSERT(2 == slider->getStep());
                slider->setLargeStep(3);
                DTK_ASSERT(3 == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                DTK_ASSERT(value == 0);
                window->setKey(Key::Right);
                DTK_ASSERT(value == 2);
                window->setKey(Key::PageUp);
                DTK_ASSERT(value == 5);
                window->setKey(Key::Left);
                DTK_ASSERT(value == 3);
                window->setKey(Key::PageDown);
                DTK_ASSERT(value == 0);
                window->setKey(Key::End);
                DTK_ASSERT(value == 10);
                window->setKey(Key::Escape);
                DTK_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

