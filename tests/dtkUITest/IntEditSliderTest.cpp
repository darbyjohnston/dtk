// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/IntEditSliderTest.h>

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkUI/IntEditSlider.h>
#include <dtkUI/RowLayout.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        IntEditSliderTest::IntEditSliderTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::IntEditSliderTest")
        {}

        IntEditSliderTest::~IntEditSliderTest()
        {}

        std::shared_ptr<IntEditSliderTest> IntEditSliderTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntEditSliderTest>(new IntEditSliderTest(context));
        }
                
        void IntEditSliderTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntEditSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntEditSliderTest",
                    "Integer edit slider test.");
                auto window = Window::create(context, app, "IntEditSliderTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto slider = IntEditSlider::create(context, nullptr, layout);
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
                slider->setDefaultValue(0);
                DTK_ASSERT(0 == slider->getDefaultValue());
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

