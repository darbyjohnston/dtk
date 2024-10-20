// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ProgressDialogTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ProgressDialog.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        ProgressDialogTest::ProgressDialogTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ProgressDialogTest")
        {}

        ProgressDialogTest::~ProgressDialogTest()
        {}

        std::shared_ptr<ProgressDialogTest> ProgressDialogTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ProgressDialogTest>(new ProgressDialogTest(context));
        }
                
        void ProgressDialogTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ProgressDialogTest");
                auto app = App::create(
                    context,
                    argv,
                    "ProgressDialogTest",
                    "Progress dialog test.");
                auto window = Window::create(context, app, "ProgressDialogTest");
                app->addWindow(window);
                window->show();
                app->tick();
            }
        }
    }
}

