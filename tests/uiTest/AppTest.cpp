// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/AppTest.h>

#include <dtk/ui/App.h>
#include <dtk/ui/Window.h>

#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }
                
        void AppTest::run()
        {
            int r = 0;
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "-exit" };
                try
                {
                    auto app = App::create(
                        context,
                        argv,
                        "dtk::ui_test::App",
                        "Test UI application");
                    r = app->getExit();
                    if (0 == r)
                    {
                        auto window = Window::create(
                            context,
                            "dtk::ui_test::App",
                            Size2I(1280, 960));
                        auto layout = VerticalLayout::create(context, window);
                        auto button = PushButton::create(context, "Button", layout);
                        app->addWindow(window);
                        DTK_ASSERT(app->getWindows().front() == window);
                        window->show();
                        window->setSize(Size2I(1920, 1080));

                        _print(Format("Window size: {0}").arg(window->getSize()));
                        _print(Format("Frame buffer size: {0}").
                            arg(window->getFrameBufferSize()));
                        _print(Format("Display scale: {0}").
                            arg(window->getDisplayScale()));

                        app->run();
                        app->exit();
                        window->hide();
                        app->removeWindow(window);
                    }
                }
                catch (const std::exception&)
                {}
            }
            DTK_ASSERT(0 == r);
        }
    }
}
