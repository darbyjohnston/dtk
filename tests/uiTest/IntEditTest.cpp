// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/IntEditTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/IntEdit.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        IntEditTest::IntEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::IntEditTest")
        {}

        IntEditTest::~IntEditTest()
        {}

        std::shared_ptr<IntEditTest> IntEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntEditTest>(new IntEditTest(context));
        }
                
        void IntEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IntEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "IntEditTest",
                    "Integer edit test.");
                auto window = Window::create(context, app, "IntEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = IntEdit::create(context, nullptr, layout);
                DTK_ASSERT(edit->getModel());
                int value = 0;
                edit->setCallback([&value](int v) { value = v; });
                edit->setValue(11);
                app->tick();
                DTK_ASSERT(11 == edit->getValue());
                DTK_ASSERT(11 == value);
                edit->setRange(RangeI(0, 10));
                app->tick();
                DTK_ASSERT(RangeI(0, 10) == edit->getRange());
                DTK_ASSERT(10 == value);
                edit->setStep(2);
                DTK_ASSERT(2 == edit->getStep());
                edit->setLargeStep(3);
                DTK_ASSERT(3 == edit->getLargeStep());
                edit->setFontRole(FontRole::Label);
                DTK_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("1");
                window->setKey(Key::Enter);
                DTK_ASSERT(1 == value);

                window->setKey(Key::Up);
                DTK_ASSERT(3 == value);
                window->setKey(Key::PageUp);
                DTK_ASSERT(6 == value);
                window->setKey(Key::PageDown);
                DTK_ASSERT(3 == value);
                window->setKey(Key::Down);
                DTK_ASSERT(1 == value);
                window->setKey(Key::Escape);
            }
        }
    }
}

