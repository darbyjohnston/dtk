// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/RowLayoutTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/Label.h>
#include <feather-tk/ui/Spacer.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        RowLayoutTest::RowLayoutTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::RowLayoutTest")
        {}

        RowLayoutTest::~RowLayoutTest()
        {}

        std::shared_ptr<RowLayoutTest> RowLayoutTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RowLayoutTest>(new RowLayoutTest(context));
        }

        void RowLayoutTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("RowLayoutTest");
                auto app = App::create(
                    context,
                    argv,
                    "RowLayoutTest",
                    "Row layout test.");
                auto window = Window::create(context, app, "RowLayoutTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::shared_ptr<RowLayout> layout = VerticalLayout::create(context, window);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::None);
                layout->setSpacingRole(SizeRole::Spacing);
                FEATHER_TK_ASSERT(SizeRole::Spacing == layout->getSpacingRole());
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::Margin);
                layout->setMarginRole(SizeRole::None);
                FEATHER_TK_ASSERT(SizeRole::None == layout->getMarginRole());
                _test(context, app, window, layout, Orientation::Horizontal);
                layout->setParent(nullptr);
                layout.reset();

                layout = HorizontalLayout::create(context, window);
                _test(context, app, window, layout, Orientation::Vertical);
                layout->setParent(nullptr);
                layout.reset();
            }
        }

        void RowLayoutTest::_test(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<RowLayout>& layout,
            Orientation orientation)
        {
            auto label0 = Label::create(context, "Label 0", layout);
            auto spacer = Spacer::create(context, orientation, layout);
            spacer->setSpacingRole(SizeRole::SpacingLarge);
            spacer->setSpacingRole(SizeRole::SpacingLarge);
            FEATHER_TK_ASSERT(SizeRole::SpacingLarge == spacer->getSpacingRole());
            auto label1 = Label::create(context, "Label 1", layout);
            app->tick();

            switch (orientation)
            {
            case Orientation::Horizontal:
                label0->setHStretch(Stretch::Expanding);
                label0->setHStretch(Stretch::Expanding);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Expanding);
                FEATHER_TK_ASSERT(Stretch::Expanding == label0->getHStretch());
                app->tick();
                label0->setHAlign(HAlign::Right);
                label0->setHAlign(HAlign::Right);
                label0->setAlign(HAlign::Center, VAlign::Center);
                label0->setAlign(HAlign::Center, VAlign::Center);
                FEATHER_TK_ASSERT(HAlign::Center == label0->getHAlign());
                app->tick();
                label0->setHAlign(HAlign::Left);
                label1->setHAlign(HAlign::Right);
                break;
            case Orientation::Vertical:
                label0->setVStretch(Stretch::Expanding);
                label0->setVStretch(Stretch::Expanding);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Fixed, Stretch::Fixed);
                label0->setStretch(Stretch::Expanding);
                FEATHER_TK_ASSERT(Stretch::Expanding == label0->getVStretch());
                app->tick();
                label0->setVAlign(VAlign::Bottom);
                label0->setVAlign(VAlign::Bottom);
                label0->setAlign(HAlign::Center, VAlign::Center);
                label0->setAlign(HAlign::Center, VAlign::Center);
                FEATHER_TK_ASSERT(VAlign::Center == label0->getVAlign());
                app->tick();
                label0->setVAlign(VAlign::Top);
                label1->setVAlign(VAlign::Bottom);
                break;
            default: break;
            }
            app->tick();

            label0->hide();
            label0->hide();
            app->tick();
            FEATHER_TK_ASSERT(!label0->isVisible());
            FEATHER_TK_ASSERT(!label0->isVisible(false));
            FEATHER_TK_ASSERT(label0->isClipped());
            label0->show();
            app->tick();

            label0->setParent(nullptr);
            app->tick();
            auto children = layout->getChildren();
            FEATHER_TK_ASSERT(2 == children.size());
            FEATHER_TK_ASSERT(spacer == children.front());
            label0->setParent(layout);
            app->tick();
            children = layout->getChildren();
            FEATHER_TK_ASSERT(3 == children.size());
            FEATHER_TK_ASSERT(spacer == children.front());
            FEATHER_TK_ASSERT(label0 == children.back());
            label0->setParent(nullptr);
            app->tick();

            label1->setParent(nullptr);
            spacer->setParent(nullptr);
            app->tick();
            children = layout->getChildren();
            FEATHER_TK_ASSERT(children.empty());
        }
    }
}

