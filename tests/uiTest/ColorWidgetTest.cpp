// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ColorWidgetTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ColorPopup.h>
#include <dtk/ui/ColorSwatch.h>
#include <dtk/ui/ColorWidget.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        ColorWidgetTest::ColorWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ColorWidgetTest")
        {}

        ColorWidgetTest::~ColorWidgetTest()
        {}

        std::shared_ptr<ColorWidgetTest> ColorWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ColorWidgetTest>(new ColorWidgetTest(context));
        }
                
        void ColorWidgetTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ColorWidgetTest");
                auto app = App::create(
                    context,
                    argv,
                    "ColorWidgetTest",
                    "Color widget test.");
                auto window = Window::create(context, app, "ColorWidgetTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto widget = ColorSwatch::create(context, layout);
                Color4F color(1.F, 1.F, 1.F, 1.F);
                widget->setColor(color);
                widget->setColor(color);
                DTK_ASSERT(color == widget->getColor());
                DTK_ASSERT(!widget->isEditable());
                widget->setEditable(true);
                widget->setEditable(true);
                DTK_ASSERT(widget->isEditable());
                widget->setCallback(
                    [&color](const Color4F& value)
                    {
                        color = value;
                    });
                widget->setSizeRole(SizeRole::Margin);
                widget->setSizeRole(SizeRole::Margin);
                DTK_ASSERT(SizeRole::Margin == widget->getSizeRole());
                widget->setSizeRole(SizeRole::Swatch);

                window->setCursorEnter(true);
                Box2I g = widget->getGeometry();
                V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Home);
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                DTK_ASSERT(Color4F(0.F, 0.F, 0.F, 0.F) == color);

                auto popup = ColorPopup::create(context, color);
                popup->setPopupRole(ColorRole::Red);
                popup->setPopupRole(ColorRole::Red);
                DTK_ASSERT(ColorRole::Red == popup->getPopupRole());
                popup->open(window, widget->getGeometry());
                app->tick();
                DTK_ASSERT(popup->isOpen());
                popup->close();
                app->tick();
                DTK_ASSERT(!popup->isOpen());

                popup->open(window, widget->getGeometry());
                app->tick();
                DTK_ASSERT(popup->isOpen());
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                DTK_ASSERT(!popup->isOpen());

                popup->open(window, widget->getGeometry());
                app->tick();
                DTK_ASSERT(popup->isOpen());
                g = window->getGeometry();
                window->setCursorPos(V2I(g.w() - 1, g.h() - 1));
                window->setButton(0);
                popup->open(window, widget->getGeometry());
                app->tick();
                DTK_ASSERT(popup->isOpen());
            }
        }
    }
}

