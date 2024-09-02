// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ScrollWidgetTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/GridLayout.h>
#include <dtk/ui/Label.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        ScrollWidgetTest::ScrollWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ScrollWidgetTest")
        {}

        ScrollWidgetTest::~ScrollWidgetTest()
        {}

        std::shared_ptr<ScrollWidgetTest> ScrollWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ScrollWidgetTest>(new ScrollWidgetTest(context));
        }
                
        void ScrollWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ScrollWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ScrollWidgetTest",
                    "Scroll widget test.");
                auto window = Window::create(context, app, "ScrollWidgetTest");
                app->addWindow(window);
                window->show();
                app->tick();
                _test(context, app, window, ScrollType::Both);
                _test(context, app, window, ScrollType::Horizontal);
                _test(context, app, window, ScrollType::Vertical);
            }
        }

        void ScrollWidgetTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            ScrollType scrollType)
        {
            auto scrollWidget = ScrollWidget::create(context, scrollType, window);
            auto layout = GridLayout::create(context);
            layout->setMarginRole(SizeRole::MarginLarge);
            for (int row = 0; row < 20; ++row)
            {
                for (int column = 0; column < 20; ++column)
                {
                    auto label = Label::create(
                        context,
                        Format("Label {0} {1}").arg(row).arg(column),
                        layout);
                    label->setFontRole(FontRole::Title);
                    label->setMarginRole(SizeRole::MarginLarge);
                    layout->setGridPos(label, row, column);
                }
            }
            scrollWidget->setWidget(layout);
            scrollWidget->setWidget(layout);
            DTK_ASSERT(layout == scrollWidget->getWidget());
            app->tick();

            _print(Format("Scroll type: {0}").arg(scrollType));
            _print(Format("Viewport: {0}").arg(scrollWidget->getViewport()));
            _print(Format("Scroll size: {0}").arg(scrollWidget->getScrollSize()));
            _print(Format("Scroll pos: {0}").arg(scrollWidget->getScrollPos()));

            V2I scroll(100, 100);
            scrollWidget->setScrollPos(scroll);
            DTK_ASSERT(scrollWidget->getScrollPos() == scroll);
            scrollWidget->setScrollPosCallback(
                [&scroll](const V2I& value)
                {
                    scroll = value;
                });
            scrollWidget->setScrollBarsVisible(false);
            scrollWidget->setScrollBarsVisible(false);
            DTK_ASSERT(!scrollWidget->areScrollBarsVisible());
            scrollWidget->setScrollBarsVisible(true);
            scrollWidget->setScrollEventsEnabled(false);
            scrollWidget->setScrollEventsEnabled(false);
            DTK_ASSERT(!scrollWidget->areScrollEventsEnabled());
            scrollWidget->setScrollEventsEnabled(true);
            scrollWidget->setBorder(false);
            scrollWidget->setBorder(false);
            DTK_ASSERT(!scrollWidget->hasBorder());
            scrollWidget->setBorder(true);
            scrollWidget->setMarginRole(SizeRole::Margin);
            scrollWidget->setMarginRole(SizeRole::Margin);
            DTK_ASSERT(SizeRole::Margin == scrollWidget->getMarginRole());
            scrollWidget->setMarginRole(SizeRole::None);

            window->setCursorEnter(true);
            Box2I g = scrollWidget->getGeometry();
            V2I c = center(g);
            window->setCursorPos(c);
            window->setScroll(V2F(0, -1));
            window->setScroll(V2F(0, -1));
            window->setScroll(V2F(0, 1));
            window->setScroll(V2F(0, 1));
            window->setKey(Key::PageDown);
            window->setKey(Key::PageUp);

            Size2I size = scrollWidget->getScrollSize();
            scrollWidget->setScrollPos(V2I(size.w, size.h));
            app->tick();
            window->setSize(Size2I(size.w * 2, size.h * 2));
            app->tick();
            window->setSize(Size2I(1280, 960));

            scrollWidget->setParent(nullptr);
        }
    }
}

