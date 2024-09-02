// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/StackLayoutTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/Divider.h>
#include <dtk/ui/StackLayout.h>
#include <dtk/ui/Spacer.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        StackLayoutTest::StackLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::StackLayoutTest")
        {}

        StackLayoutTest::~StackLayoutTest()
        {}

        std::shared_ptr<StackLayoutTest> StackLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StackLayoutTest>(new StackLayoutTest(context));
        }

        void StackLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("StackLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "StackLayoutTest",
                    "Stack layout test.");
                auto window = Window::create(context, app, "StackLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto layout = StackLayout::create(context, window);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                DTK_ASSERT(SizeRole::None == layout->getMarginRole());

                auto spacer0 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer1 = Spacer::create(context, Orientation::Horizontal, layout);
                auto spacer2 = Spacer::create(context, Orientation::Horizontal, layout);
                app->tick();
                DTK_ASSERT(0 == layout->getCurrentIndex());
                DTK_ASSERT(spacer0->isVisible());
                DTK_ASSERT(!spacer1->isVisible());
                DTK_ASSERT(!spacer2->isVisible());

                layout->setCurrentIndex(1);
                app->tick();
                DTK_ASSERT(!spacer0->isVisible());
                DTK_ASSERT(spacer1->isVisible());
                DTK_ASSERT(!spacer2->isVisible());

                layout->setCurrentWidget(spacer2);
                app->tick();
                DTK_ASSERT(2 == layout->getCurrentIndex());
                DTK_ASSERT(!spacer0->isVisible());
                DTK_ASSERT(!spacer1->isVisible());
                DTK_ASSERT(spacer2->isVisible());

                spacer2->setParent(nullptr);
                app->tick();
                DTK_ASSERT(1 == layout->getCurrentIndex());
                DTK_ASSERT(!spacer0->isVisible());
                DTK_ASSERT(spacer1->isVisible());
            }
        }
    }
}

