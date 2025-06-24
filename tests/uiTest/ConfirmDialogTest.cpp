// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ConfirmDialogTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/DialogSystem.h>
#include <feather-tk/ui/ConfirmDialog.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ConfirmDialogTest::ConfirmDialogTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ConfirmDialogTest")
        {}

        ConfirmDialogTest::~ConfirmDialogTest()
        {}

        std::shared_ptr<ConfirmDialogTest> ConfirmDialogTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ConfirmDialogTest>(new ConfirmDialogTest(context));
        }
                
        void ConfirmDialogTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ConfirmDialogTest");
                auto app = App::create(
                    context,
                    argv,
                    "ConfirmDialogTest",
                    "Confirmation dialog test.");
                auto window = Window::create(context, app, "ConfirmDialogTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto system = context->getSystem<DialogSystem>();
                bool confirmed = false;
                system->confirm(
                    "Confirm",
                    "This is a confirmation?",
                    window,
                    [&confirmed](bool value) { confirmed = value; });
                app->tick();
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(confirmed);
            }
        }
    }
}

