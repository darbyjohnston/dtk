// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/MessageDialogTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/MessageDialog.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        MessageDialogTest::MessageDialogTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::MessageDialogTest")
        {}

        MessageDialogTest::~MessageDialogTest()
        {}

        std::shared_ptr<MessageDialogTest> MessageDialogTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MessageDialogTest>(new MessageDialogTest(context));
        }
                
        void MessageDialogTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("MessageDialogTest");
                auto app = App::create(
                    context,
                    argv,
                    "MessageDialogTest",
                    "Message dialog test.");
                auto window = Window::create(context, app, "MessageDialogTest");
                app->addWindow(window);
                window->show();
                app->tick();

                window->setCursorEnter(true);
                auto system = context->getSystem<MessageDialogSystem>();
                system->message("Message", "This is a message.", window);
                app->tick();
                window->setKey(Key::Enter);

                bool confirmed = false;
                system->confirm(
                    "Confirm",
                    "This is a confirmation?",
                    window,
                    [&confirmed](bool value) { confirmed = value; });
                app->tick();
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                DTK_ASSERT(confirmed);
            }
        }
    }
}
