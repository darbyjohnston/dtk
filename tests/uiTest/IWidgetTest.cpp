// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IWidgetTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        IWidgetTest::IWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::IWidgetTest")
        {}

        IWidgetTest::~IWidgetTest()
        {}

        std::shared_ptr<IWidgetTest> IWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IWidgetTest>(new IWidgetTest(context));
        }

        namespace
        {
            class Widget : public IWidget
            {
            protected:
                Widget()
                {}

            public:
                static std::shared_ptr<Widget> create(
                    const std::shared_ptr<Context>& context,
                    const std::shared_ptr<IWidget>& parent)
                {
                    auto out = std::shared_ptr<Widget>(new Widget);
                    out->_init(context, "Widget", parent);
                    return out;
                }
            };
        }

        void IWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("IWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "IWidgetTest",
                    "IWidget test.");
                auto window = Window::create(context, app, "IWidgetTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget0 = Widget::create(context, layout);
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget0));
                auto widget1 = Widget::create(context, layout);
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget1));
                auto widget2 = Widget::create(context, layout);
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget2));
                app->tick();

                layout->moveToBack(widget2);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget2));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget1));

                layout->moveToFront(widget2);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget1));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget2));

                layout->moveToIndex(widget2, 2);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget1));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget2));

                layout->moveToIndex(widget2, 3);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget1));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget2));

                layout->moveToIndex(widget2, 1);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget2));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget1));

                layout->moveToIndex(widget0, 1);
                app->tick();
                FEATHER_TK_ASSERT(0 == layout->getChildIndex(widget2));
                FEATHER_TK_ASSERT(1 == layout->getChildIndex(widget0));
                FEATHER_TK_ASSERT(2 == layout->getChildIndex(widget1));
            }
        }
    }
}

