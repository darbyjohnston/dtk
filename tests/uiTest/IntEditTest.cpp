// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IntEditTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/IntEdit.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        IntEditTest::IntEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::IntEditTest")
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

                auto edit = IntEdit::create(context, layout);
                FEATHER_TK_ASSERT(edit->getModel());
                int value = 0;
                edit->setCallback([&value](int v) { value = v; });
                edit->setValue(11);
                app->tick();
                FEATHER_TK_ASSERT(11 == edit->getValue());
                FEATHER_TK_ASSERT(11 == value);
                edit->setRange(RangeI(0, 10));
                app->tick();
                FEATHER_TK_ASSERT(RangeI(0, 10) == edit->getRange());
                FEATHER_TK_ASSERT(10 == value);
                edit->setStep(2);
                FEATHER_TK_ASSERT(2 == edit->getStep());
                edit->setLargeStep(3);
                FEATHER_TK_ASSERT(3 == edit->getLargeStep());
                edit->setFontRole(FontRole::Label);
                FEATHER_TK_ASSERT(FontRole::Label == edit->getFontRole());
                edit->setFontRole(FontRole::Mono);

                window->setCursorEnter(true);
                window->setCursorPos(center(edit->getGeometry()));
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("1");
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(1 == value);

                window->setKey(Key::Up);
                FEATHER_TK_ASSERT(3 == value);
                window->setKey(Key::PageUp);
                FEATHER_TK_ASSERT(6 == value);
                window->setKey(Key::PageDown);
                FEATHER_TK_ASSERT(3 == value);
                window->setKey(Key::Down);
                FEATHER_TK_ASSERT(1 == value);
                window->setKey(Key::Escape);
            }
        }
    }
}

