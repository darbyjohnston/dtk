// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/SearchBoxTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/SearchBox.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        SearchBoxTest::SearchBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::SearchBoxTest")
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
                DTK_ASSERT("Search" == widget->getText());

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete);
                window->setText("Filter");
                DTK_ASSERT("Filter" == text);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                DTK_ASSERT(text.empty());
            }
        }
    }
}

