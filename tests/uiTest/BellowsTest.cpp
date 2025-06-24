// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/BellowsTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/Bellows.h>
#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        BellowsTest::BellowsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::BellowsTest")
        {}

        BellowsTest::~BellowsTest()
        {}

        std::shared_ptr<BellowsTest> BellowsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<BellowsTest>(new BellowsTest(context));
        }
                
        void BellowsTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("BellowsTest");
                auto app = App::create(
                    context,
                    argv,
                    "BellowsTest",
                    "Bellows test.");
                auto window = Window::create(context, app, "BellowsTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto bellows = Bellows::create(context, "Bellows", layout);
                bellows->setText("Test");
                FEATHER_TK_ASSERT("Test" == bellows->getText());
                auto label = Label::create(context, "Label");
                bellows->setWidget(label);
                bellows->setWidget(label);
                FEATHER_TK_ASSERT(label == bellows->getWidget());
                bellows->setOpen(true);
                bellows->setOpen(true);
                FEATHER_TK_ASSERT(bellows->isOpen());
                bellows->setOpen(false);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(bellows->isOpen());
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(!bellows->isOpen());
                window->setKey(Key::Escape);
                window->setCursorPos(center(bellows->getGeometry()));
                window->setButton(0);
                FEATHER_TK_ASSERT(bellows->isOpen());
                window->setButton(0);
                FEATHER_TK_ASSERT(!bellows->isOpen());

                bellows->hide();
                app->tick();
                bellows->show();
                app->tick();
            }
        }
    }
}

