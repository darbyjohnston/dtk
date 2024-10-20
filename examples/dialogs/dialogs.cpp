// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/DialogSystem.h>
#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/FileEdit.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Window.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "buttons", "Buttons example");
        if (app->getExit() != 0)
            return app->getExit();

        // Disable the native file dialog.
        context->getSystem<dtk::FileBrowserSystem>()->setNativeFileDialog(false);

        // Create the window.
        auto window = Window::create(
            context,
            "buttons",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context, window);
        layout->setMarginRole(SizeRole::Margin);

        // Message dialog.
        auto button = PushButton::create(context, "Message Dialog", layout);
        button->setClickedCallback(
            [context, window]
            {
                context->getSystem<DialogSystem>()->message(
                    "Message",
                    "Hello world!",
                    window);
            });

        // Confirmation dialog.
        button = PushButton::create(context, "Confirmation Dialog", layout);
        button->setClickedCallback(
            [context, window]
            {
                context->getSystem<DialogSystem>()->confirm(
                    "Confirm",
                    "Hello world?",
                    window,
                    [](bool value)
                    {
                        std::cout << "Hello world: " << value << std::endl;
                    });
            });

        // File browser.
        auto fileEdit = FileEdit::create(context, layout);
        fileEdit->setPath("File Browser");

        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

