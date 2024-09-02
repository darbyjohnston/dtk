// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleEditTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/DoubleEdit.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        DoubleEditTest::DoubleEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::DoubleEditTest")
        {}

        DoubleEditTest::~DoubleEditTest()
        {}

        std::shared_ptr<DoubleEditTest> DoubleEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleEditTest>(new DoubleEditTest(context));
        }
                
        void DoubleEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleEditTest",
                    "Double edit test.");
                auto window = Window::create(context, app, "DoubleEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = DoubleEdit::create(context, nullptr, layout);
                DTK_ASSERT(edit->getModel());
                double value = 0.0;
                edit->setCallback([&value](double v) { value = v; });
                edit->setValue(0.9);
                app->tick();
                DTK_ASSERT(0.9 == edit->getValue());
                DTK_ASSERT(0.9 == value);
                edit->setRange(RangeD(0.0, 0.5));
                app->tick();
                DTK_ASSERT(RangeD(0.0, 0.5) == edit->getRange());
                DTK_ASSERT(0.5 == value);
                edit->setStep(0.2);
                DTK_ASSERT(0.2 == edit->getStep());
                edit->setLargeStep(0.3);
                DTK_ASSERT(0.3 == edit->getLargeStep());
                edit->setPrecision(3);
                edit->setPrecision(3);
                DTK_ASSERT(3 == edit->getPrecision());
                edit->setPrecision(2);
                edit->setFontRole(FontRole::Label);
                DTK_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("0.1");
                window->setKey(Key::Enter);
                DTK_ASSERT(0.1 == value);

                window->setKey(Key::Up);
                DTK_ASSERT(fuzzyCompare(0.3, value));
                window->setKey(Key::PageUp);
                DTK_ASSERT(fuzzyCompare(0.5, value));
                window->setKey(Key::PageDown);
                DTK_ASSERT(fuzzyCompare(0.2, value));
                window->setKey(Key::Down);
                DTK_ASSERT(fuzzyCompare(0.0, value));
                window->setKey(Key::Escape);
            }
        }
    }
}

