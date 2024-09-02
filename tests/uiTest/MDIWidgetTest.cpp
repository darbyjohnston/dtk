// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/MDIWidgetTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/Label.h>
#include <dtk/ui/MDICanvas.h>
#include <dtk/ui/MDIWidget.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        MDIWidgetTest::MDIWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::MDIWidgetTest")
        {}

        MDIWidgetTest::~MDIWidgetTest()
        {}

        std::shared_ptr<MDIWidgetTest> MDIWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MDIWidgetTest>(new MDIWidgetTest(context));
        }
                
        void MDIWidgetTest::run()
        {
            _enums();
            _widget();
        }

        void MDIWidgetTest::_enums()
        {
            DTK_TEST_ENUM(MDIResize);
        }

        void MDIWidgetTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("MDIWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "MDIWidgetTest",
                    "MDI widget test.");
                auto window = Window::create(context, app, "MDIWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto canvas = MDICanvas::create(context, window);
                canvas->setCanvasSize(Size2I(100, 100));
                canvas->setCanvasSize(Size2I(100, 100));
                DTK_ASSERT(Size2I(100, 100) == canvas->getCanvasSize());
                canvas->setCanvasSize(Size2I(1000, 1000));
                canvas->setGridSize(Size2I(2, 2));
                canvas->setGridSize(Size2I(2, 2));
                DTK_ASSERT(Size2I(2, 2) == canvas->getGridSize());
                canvas->setGridSize(Size2I(20, 20));

                auto label = Label::create(context, "Label");
                auto widget = canvas->addWidget("Widget 0", V2I(100, 100), label);
                DTK_ASSERT("Widget 0" == widget->getTitle());
                widget->setTitle("Widget");
                DTK_ASSERT("Widget" == widget->getTitle());
                app->tick();
                label.reset();
                widget->setParent(nullptr);
                widget.reset();
                label = Label::create(context, "Label 1");
                widget = canvas->addWidget("Widget 1", V2I(100, 100), label);
                label = Label::create(context, "Label 2");
                widget->setWidget(label);
                widget->setWidget(label);
                DTK_ASSERT(label == widget->getWidget());
                widget->setPos(V2I(200, 200));
                widget->setSize(Size2I(1000, 1000));

                window->setCursorEnter(true);
                Box2I g = widget->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(c + V2I(100, 100));
                window->setButton(0, false);
                window->setCursorPos(c);
                window->setButton(0);
            }
        }
    }
}

