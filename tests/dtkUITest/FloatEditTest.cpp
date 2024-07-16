// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/FloatEditTest.h>

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkUI/FloatEdit.h>
#include <dtkUI/RowLayout.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        FloatEditTest::FloatEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FloatEditTest")
        {}

        FloatEditTest::~FloatEditTest()
        {}

        std::shared_ptr<FloatEditTest> FloatEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatEditTest>(new FloatEditTest(context));
        }

        void FloatEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FloatEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FloatEditTest",
                    "Float edit test.");
                auto window = Window::create(context, app, "FloatEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FloatEdit::create(context, nullptr, layout);
                DTK_ASSERT(edit->getModel());
                float value = 0.F;
                edit->setCallback([&value](float v) { value = v; });
                edit->setValue(.9F);
                app->tick();
                DTK_ASSERT(.9F == edit->getValue());
                DTK_ASSERT(.9F == value);
                edit->setRange(RangeF(0.F, .5F));
                app->tick();
                DTK_ASSERT(RangeF(0.F, .5F) == edit->getRange());
                DTK_ASSERT(.5F == value);
                edit->setStep(.2F);
                DTK_ASSERT(.2F == edit->getStep());
                edit->setLargeStep(.3F);
                DTK_ASSERT(.3F == edit->getLargeStep());
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
                DTK_ASSERT(.1F == value);

                window->setKey(Key::Up);
                DTK_ASSERT(fuzzyCompare(.3F, value));
                window->setKey(Key::PageUp);
                DTK_ASSERT(fuzzyCompare(.5F, value));
                window->setKey(Key::PageDown);
                DTK_ASSERT(fuzzyCompare(.2F, value));
                window->setKey(Key::Down);
                DTK_ASSERT(fuzzyCompare(.0F, value));
                window->setKey(Key::Escape);
            }
        }
    }
}

