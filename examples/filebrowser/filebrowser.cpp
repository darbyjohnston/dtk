// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUIApp/App.h>
#include <dtkUIApp/Window.h>

#include <dtkUI/FileBrowser.h>
#include <dtkUI/FileEdit.h>
#include <dtkUI/RowLayout.h>
#include <dtkUI/ScrollWidget.h>

#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = dtk::app::convert(argc, argv);
        auto app = App::create(context, args, "filebrowser", "File browser example");
        if (app->getExit() != 0)
            return app->getExit();

        // Disable the native file dialog.
        context->getSystem<dtk::ui::FileBrowserSystem>()->setNativeFileDialog(false);

        // Create the window.
        auto window = Window::create(
            context,
            "filebrowser",
            Size2I(1280, 960));
        app->addWindow(window);

        // Create the layout.
        auto layout = VerticalLayout::create(context);
        layout->setMarginRole(SizeRole::Margin);
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both, window);
        scrollWidget->setWidget(layout);

        // Create the file widgets.
        for (size_t i = 0; i < 10; ++i)
        {
            FileEdit::create(context, layout);
        }

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

