// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/FloatEditSliderTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/FloatEditSlider.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        FloatEditSliderTest::FloatEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FloatEditSliderTest")
        {}

        FloatEditSliderTest::~FloatEditSliderTest()
        {}

        std::shared_ptr<FloatEditSliderTest> FloatEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditSliderTest>(new FloatEditSliderTest(context));
        }

        void FloatEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditSliderTest",
                    "Float edit slider test.");
                auto window = Window::create(context, app, "FloatEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = FloatEditSlider::create(context, nullptr, layout);
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
                slider->setPrecision(3);
                DTK_ASSERT(3 == slider->getPrecision());
                slider->setPrecision(2);
                slider->setDefaultValue(0.F);
                DTK_ASSERT(0.F == slider->getDefaultValue());
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

