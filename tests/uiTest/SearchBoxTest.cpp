// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/SearchBoxTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/SearchBox.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        SearchBoxTest::SearchBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::SearchBoxTest")
        {}

        SearchBoxTest::~SearchBoxTest()
        {}

        std::shared_ptr<SearchBoxTest> SearchBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SearchBoxTest>(new SearchBoxTest(context));
        }
                
        void SearchBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("SearchBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "SearchBoxTest",
                    "Search box test.");
                auto window = Window::create(context, app, "SearchBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = SearchBox::create(context, layout);
                std::string text;
                widget->setCallback(
                    [&text](const std::string& value)
                    {
                        text = value;
                    });
                widget->setText("Search");
                widget->setText("Search");
                FEATHER_TK_ASSERT("Search" == widget->getText());

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("Filter");
                FEATHER_TK_ASSERT("Filter" == text);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(text.empty());
            }
        }
    }
}

