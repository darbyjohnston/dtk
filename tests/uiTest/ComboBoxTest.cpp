// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ComboBoxTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ComboBoxPrivate.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        ComboBoxTest::ComboBoxTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ComboBoxTest")
        {}

        ComboBoxTest::~ComboBoxTest()
        {}

        std::shared_ptr<ComboBoxTest> ComboBoxTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ComboBoxTest>(new ComboBoxTest(context));
        }
                
        void ComboBoxTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ComboBoxTest");
                auto app = App::create(
                    context,
                    argv,
                    "ComboBoxTest",
                    "Combo box test.");
                auto window = Window::create(context, app, "ComboBoxTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                std::vector<ComboBoxItem> items =
                {
                    ComboBoxItem("Stop", "PlaybackStop"),
                    ComboBoxItem("Forward", "PlaybackForward"),
                    ComboBoxItem("Reverse", "PlaybackReverse")
                };
                auto widget = ComboBox::create(context, items, layout);
                DTK_ASSERT(items[0] != ComboBoxItem());
                widget->setItems(items);
                widget->setItems(items);
                DTK_ASSERT(items == widget->getItems());
                DTK_ASSERT(0 == widget->getCurrentIndex());
                widget->setCurrentIndex(1);
                widget->setCurrentIndex(1);
                DTK_ASSERT(1 == widget->getCurrentIndex());
                int index = -1;
                widget->setIndexCallback(
                    [&index](int value)
                    {
                        index = value;
                    });
                ComboBoxItem item;
                widget->setItemCallback(
                    [&item](const ComboBoxItem& value)
                    {
                        item = value;
                    });
                widget->setFontRole(FontRole::Mono);
                widget->setFontRole(FontRole::Mono);
                DTK_ASSERT(FontRole::Mono == widget->getFontRole());
                widget->setFontRole(FontRole::Label);

                auto button = ComboBoxButton::create(
                    context,
                    ComboBoxItem("Item"),
                    layout);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Home);
                window->setKey(Key::Enter);
                DTK_ASSERT(0 == index);
                DTK_ASSERT(items[0] == item);
                window->setKey(Key::Enter);
                window->setKey(Key::Down);
                window->setKey(Key::Up);
                window->setKey(Key::End);
                window->setKey(Key::Home);
                window->setKey(Key::Escape);

                Box2I g = widget->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0);
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                window->setCursorPos(V2I(0, 0));

                window->setKey(Key::Tab);
                window->setKey(Key::Down);
                DTK_ASSERT(1 == index);
                window->setKey(Key::Up);
                DTK_ASSERT(0 == index);
                window->setKey(Key::End);
                DTK_ASSERT(items.size() - 1 == index);
                window->setKey(Key::Home);
                DTK_ASSERT(0 == index);
                window->setKey(Key::Escape);
                DTK_ASSERT(!widget->hasKeyFocus());

                g = button->getGeometry();
                c = center(g);
                window->setCursorPos(c);
                window->setButton(0);
                window->setKey(Key::Escape);
                window->setCursorPos(V2I(0, 0));

                app->setDisplayScale(2.F);
                app->tick();
                app->setDisplayScale(1.F);
                app->tick();
            }
        }
    }
}

