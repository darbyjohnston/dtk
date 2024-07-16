// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/LabelTest.h>

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkUI/IClipboard.h>
#include <dtkUI/Label.h>
#include <dtkUI/RowLayout.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        LabelTest::LabelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::LabelTest")
        {}

        LabelTest::~LabelTest()
        {}

        std::shared_ptr<LabelTest> LabelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LabelTest>(new LabelTest(context));
        }
                
        void LabelTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LabelTest");
                auto app = App::create(
                    context,
                    argv,
                    "LabelTest",
                    "Label test.");
                auto window = Window::create(context, app, "LabelTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto label = Label::create(context, layout);
                label->setText("Test");
                label->setText("Test");
                DTK_ASSERT("Test" == label->getText());
                label->setTextRole(ColorRole::Red);
                label->setTextRole(ColorRole::Red);
                DTK_ASSERT(ColorRole::Red == label->getTextRole());
                label->setMarginRole(SizeRole::Margin);
                label->setMarginRole(SizeRole::Margin);
                DTK_ASSERT(SizeRole::Margin == label->getMarginRole());
                label->setFontRole(FontRole::Mono);
                label->setFontRole(FontRole::Mono);
                DTK_ASSERT(FontRole::Mono == label->getFontRole());

                label->setEnabled(false);
                app->tick();
                label->setEnabled(true);
                app->tick();

                label->hide();
                app->tick();
                label->show();
                app->tick();
            }
        }
    }
}

