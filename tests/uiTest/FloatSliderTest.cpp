// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/FloatSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/FloatSlider.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        FloatSliderTest::FloatSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FloatSliderTest")
        {}

        FloatSliderTest::~FloatSliderTest()
        {}

        std::shared_ptr<FloatSliderTest> FloatSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatSliderTest>(new FloatSliderTest(context));
        }

        void FloatSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatSliderTest",
                    "Float slider test.");
                auto window = Window::create(context, app, "FloatSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = FloatSlider::create(context, nullptr, layout);
                DTK_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                app->tick();
                DTK_ASSERT(.9F == slider->getValue());
                DTK_ASSERT(.9F == value);
                slider->setRange(RangeF(0.F, .5F));
                app->tick();
                DTK_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                DTK_ASSERT(.5F == value);
                slider->setStep(.2F);
                DTK_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                DTK_ASSERT(.3F == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                DTK_ASSERT(value == 0.F);
                window->setKey(Key::Right);
                DTK_ASSERT(fuzzyCompare(value, .2F));
                window->setKey(Key::PageUp);
                DTK_ASSERT(fuzzyCompare(value, .5F));
                window->setKey(Key::Left);
                DTK_ASSERT(fuzzyCompare(value, .3F));
                window->setKey(Key::PageDown);
                DTK_ASSERT(fuzzyCompare(value, 0.F));
                window->setKey(Key::End);
                DTK_ASSERT(value == .5F);
                window->setKey(Key::Escape);
                DTK_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

