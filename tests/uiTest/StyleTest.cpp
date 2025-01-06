// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/StyleTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/PushButton.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Style.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        StyleTest::StyleTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::StyleTest")
        {}

        StyleTest::~StyleTest()
        {}

        std::shared_ptr<StyleTest> StyleTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StyleTest>(new StyleTest(context));
        }
                
        void StyleTest::run()
        {
            _enums();
            _widget();
        }
        
        void StyleTest::_enums()
        {
            DTK_TEST_ENUM(SizeRole);
            DTK_TEST_ENUM(ColorRole);
            DTK_TEST_ENUM(FontRole);
        }

        void StyleTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("StyleTest");
                auto app = App::create(
                    context,
                    argv,
                    "StyleTest",
                    "Style test.");
                auto window = Window::create(context, app, "StyleTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                auto button = PushButton::create(context, "Button", layout);
                app->addWindow(window);
                window->show();
                app->tick();

                auto style = app->getStyle();
                int changed = 0;
                auto observer = ValueObserver<bool>::create(
                    style->observeChanged(),
                    [&changed](bool)
                    {
                        ++changed;
                    });
                
                style->setSizeRole(SizeRole::Border, 10);
                style->setSizeRole(SizeRole::Border, 10);
                DTK_ASSERT(10 == style->getSizeRole(SizeRole::Border, 1.F));
                DTK_ASSERT(2 == changed);
                app->tick();
                std::map<SizeRole, int> sizeRoles =
                {
                    { SizeRole::Margin, 20 },
                    { SizeRole::Spacing, 20 },
                    { SizeRole::Border, 2 }
                };
                style->setSizeRoles(sizeRoles);
                style->setSizeRoles(sizeRoles);
                DTK_ASSERT(3 == changed);
                app->tick();

                Color4F color(1.F, 0.F, 0.F);
                style->setColorRole(ColorRole::Window, color);
                style->setColorRole(ColorRole::Window, color);
                DTK_ASSERT(color == style->getColorRole(ColorRole::Window));
                DTK_ASSERT(4 == changed);
                app->tick();
                std::map<ColorRole, Color4F> colorRoles =
                {
                    { ColorRole::Window, Color4F(0.F, 1.F, 0.F) },
                    { ColorRole::Text, Color4F(0.F, 0.F, 1.F) },
                    { ColorRole::Border, Color4F(1.F, 0.F, 0.F) }
                };
                style->setColorRoles(colorRoles);
                style->setColorRoles(colorRoles);
                DTK_ASSERT(5 == changed);
                app->tick();

                FontInfo fontInfo;
                fontInfo.size = 32;
                style->setFontRole(FontRole::Label, fontInfo);
                style->setFontRole(FontRole::Label, fontInfo);
                DTK_ASSERT(fontInfo == style->getFontRole(FontRole::Label, 1.F));
                DTK_ASSERT(6 == changed);
                app->tick();
                fontInfo.size = 16;
                std::map<FontRole, FontInfo> fontRoles =
                {
                    { FontRole::Label, fontInfo }
                };
                style->setFontRoles(fontRoles);
                style->setFontRoles(fontRoles);
                DTK_ASSERT(7 == changed);
                app->tick();
            }
        }
    }
}

