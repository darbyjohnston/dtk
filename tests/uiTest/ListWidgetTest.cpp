// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ListWidgetTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ListWidget.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        ListWidgetTest::ListWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ListWidgetTest")
        {}

        ListWidgetTest::~ListWidgetTest()
        {}

        std::shared_ptr<ListWidgetTest> ListWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ListWidgetTest>(new ListWidgetTest(context));
        }
                
        void ListWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ListWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ListWidgetTest",
                    "List widget test.");
                auto window = Window::create(context, app, "ListWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, ButtonGroupType::Click);
                _test(context, app, window, ButtonGroupType::Check);
                _test(context, app, window, ButtonGroupType::Radio);
                _test(context, app, window, ButtonGroupType::Toggle);
            }
        }

        void ListWidgetTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            ButtonGroupType type)
        {
            auto widget = ListWidget::create(context, type, window);
            std::vector<ListItem> items =
            {
                ListItem("Item 0"),
                ListItem("Item 1"),
                ListItem("Item 2"),
                ListItem("Item 3")
            };
            widget->setItems(items);
            widget->setItems(items);
            DTK_ASSERT(items == widget->getItems());
            app->tick();
            items.push_back(ListItem("Item 4"));
            widget->setItems(items);
            app->tick();
            widget->setSearch("4");
            widget->setSearch("4");
            DTK_ASSERT("4" == widget->getSearch());
            app->tick();
            widget->clearSearch();
            DTK_ASSERT(widget->getSearch().empty());
            app->tick();

            window->setCursorEnter(true);
            window->setKey(Key::Tab);
            window->setKey(Key::Enter);
            switch (type)
            {
            case ButtonGroupType::Check:
            case ButtonGroupType::Radio:
            case ButtonGroupType::Toggle:
                DTK_ASSERT(widget->getChecked(0));
                break;
            }
            window->setKey(Key::Down);
            window->setKey(Key::Up);
            window->setKey(Key::End);
            window->setKey(Key::Home);
            window->setKey(Key::Escape);
        }
    }
}

