// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/App.h>
#include <dtk/ui/ColorWidget.h>
#include <dtk/ui/MDICanvas.h>
#include <dtk/ui/MDIWidget.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/ScrollWidget.h>

#include <dtk/core/Format.h>
#include <dtk/core/Random.h>

using namespace dtk;

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(context, args, "mdi", "MDI example");
        if (app->getExit() != 0)
            return app->getExit();

        // Create the window.
        const Size2I size(1280, 720);
        auto window = MainWindow::create(context, app, "mdi", size);
        app->addWindow(window);

        // Create the scroll widget.
        auto scrollWidget = ScrollWidget::create(context, ScrollType::Both);
        scrollWidget->setBorder(false);
        scrollWidget->setVStretch(Stretch::Expanding);
        window->setWidget(scrollWidget);

        // Create the MDI canvas.
        auto canvas = MDICanvas::create(context);
        scrollWidget->setWidget(canvas);

        // Create the MDI widgets.
        Random random;
        for (size_t i = 0; i < 10; ++i)
        {
            auto colorWidget = ColorWidget::create(context);
            colorWidget->setColor(Color4F(random.getF(), random.getF(), random.getF()));
            canvas->addWidget(
                Format("Color {0}").arg(i),
                V2I(random.getI(0, size.w), random.getI(0, size.h)),
                colorWidget);
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

