// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FloatSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/FloatSlider.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        FloatSliderTest::FloatSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FloatSliderTest")
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

                auto slider = FloatSlider::create(context, layout);
                FEATHER_TK_ASSERT(slider->getModel());
                float value = 0.F;
                slider->setCallback([&value](float v) { value = v; });
                slider->setValue(.9F);
                app->tick();
                FEATHER_TK_ASSERT(.9F == slider->getValue());
                FEATHER_TK_ASSERT(.9F == value);
                slider->setRange(0.F, .5F);
                app->tick();
                FEATHER_TK_ASSERT(RangeF(0.F, .5F) == slider->getRange());
                FEATHER_TK_ASSERT(.5F == value);
                slider->setStep(.2F);
                FEATHER_TK_ASSERT(.2F == slider->getStep());
                slider->setLargeStep(.3F);
                FEATHER_TK_ASSERT(.3F == slider->getLargeStep());

                Box2I g = slider->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                window->setKey(Key::Home);
                FEATHER_TK_ASSERT(value == 0.F);
                window->setKey(Key::Right);
                FEATHER_TK_ASSERT(fuzzyCompare(value, .2F));
                window->setKey(Key::PageUp);
                FEATHER_TK_ASSERT(fuzzyCompare(value, .5F));
                window->setKey(Key::Left);
                FEATHER_TK_ASSERT(fuzzyCompare(value, .3F));
                window->setKey(Key::PageDown);
                FEATHER_TK_ASSERT(fuzzyCompare(value, 0.F));
                window->setKey(Key::End);
                FEATHER_TK_ASSERT(value == .5F);
                window->setKey(Key::Escape);
                FEATHER_TK_ASSERT(!slider->hasKeyFocus());
            }
        }
    }
}

