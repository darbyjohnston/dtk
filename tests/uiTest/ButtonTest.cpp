// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ButtonTest.h>

#include <dtk/ui/CheckBox.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/ToolButton.h>
#include <dtk/ui/Tooltip.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Time.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        ButtonTest::ButtonTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ButtonTest")
        {}

        ButtonTest::~ButtonTest()
        {}

        std::shared_ptr<ButtonTest> ButtonTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ButtonTest>(new ButtonTest(context));
        }

        void ButtonTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("ButtonTest");
                auto app = App::create(
                    context,
                    argv,
                    "ButtonTest",
                    "Button test.");
                auto window = Window::create(context, app, "ButtonTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                PushButton::create(context, "Push", layout);

                std::shared_ptr<IButton> button = PushButton::create(context, "Push", layout);
                button->setObjectName("PushButton");
                _print(button->getObjectName());
                _print(button->getObjectPath());
                _test(app, window, layout, button);
                button->setParent(nullptr);
                button.reset();

                button = ToolButton::create(context, "Tool", layout);
                _test(app, window, layout, button);
                button->setParent(nullptr);
                button.reset();

                button = CheckBox::create(context, "CheckBox", layout);
                _test(app, window, layout, button);
                window->setCursorEnter(true);
                std::string tooltip = "This is a tooltip";
                button->setTooltip(tooltip);
                DTK_ASSERT(tooltip == button->getTooltip());
                window->setCursorPos(center(button->getGeometry()));
                sleep(tooltipTimeout * 2);
                window->setCursorPos(center(button->getGeometry()));
                window->setCursorPos(V2I(0, 0));
                button->setParent(nullptr);
                button.reset();
            }
        }

        void ButtonTest::_test(
            const std::shared_ptr<App>& app,
            const std::shared_ptr<Window>& window,
            const std::shared_ptr<VerticalLayout>& layout,
            const std::shared_ptr<IButton>& button)
        {
            DTK_ASSERT(button->getParent().lock());
            DTK_ASSERT(button->getParentT<Window>());
            DTK_ASSERT(button->getWindow());

            std::string text = "Playback";
            button->setText(text);
            button->setText(text);
            DTK_ASSERT(text == button->getText());

            FontRole fontRole = FontRole::Mono;
            button->setFontRole(fontRole);
            button->setFontRole(fontRole);
            DTK_ASSERT(fontRole == button->getFontRole());

            button->setCheckable(true);
            button->setCheckable(true);
            DTK_ASSERT(button->isCheckable());
            button->setChecked(true);
            button->setChecked(true);
            DTK_ASSERT(button->isChecked());
            button->setCheckable(false);
            DTK_ASSERT(!button->isChecked());
            button->setCheckable(true);

            std::string icon = "PlaybackForward";
            button->setIcon(icon);
            button->setIcon(icon);
            DTK_ASSERT(icon == button->getIcon());
            icon = "PlaybackStop";
            button->setCheckedIcon(icon);
            button->setCheckedIcon(icon);
            DTK_ASSERT(icon == button->getCheckedIcon());

            ColorRole colorRole = ColorRole::Red;
            button->setBackgroundRole(colorRole);
            button->setBackgroundRole(colorRole);
            DTK_ASSERT(colorRole == button->getBackgroundRole());
            colorRole = ColorRole::Green;
            button->setButtonRole(colorRole);
            button->setButtonRole(colorRole);
            DTK_ASSERT(colorRole == button->getButtonRole());
            colorRole = ColorRole::Blue;
            button->setCheckedRole(colorRole);
            button->setCheckedRole(colorRole);
            DTK_ASSERT(colorRole == button->getCheckedRole());

            button->hide();
            button->hide();
            app->tick();
            button->show();
            app->tick();

            button->setEnabled(false);
            button->setEnabled(false);
            app->tick();
            button->setEnabled(true);
            app->tick();

            bool hovered = false;
            button->setHoveredCallback([&hovered](bool value) { hovered = value; });
            bool pressed = false;
            button->setPressedCallback([&pressed] { pressed = true; });
            int clicks = 0;
            button->setRepeatClick(true);
            DTK_ASSERT(button->hasRepeatClick());
            button->setClickedCallback([&clicks] { ++clicks; });
            bool checked = false;
            button->setCheckedCallback([&checked](bool value) { checked = value; });

            window->setCursorEnter(true);
            window->setCursorPos(center(button->getGeometry()));
            DTK_ASSERT(hovered);
            window->setButton(0, true);
            DTK_ASSERT(pressed);
            window->setButton(0, false);
            DTK_ASSERT(clicks);
            DTK_ASSERT(checked);
            if (button->acceptsKeyFocus())
            {
                DTK_ASSERT(button->hasKeyFocus());
            }
            window->setCursorPos(V2I(0, 0));
            DTK_ASSERT(!hovered);
            window->setCursorPos(center(button->getGeometry()));
            window->setCursorEnter(false);

            clicks = 0;

            window->setCursorEnter(true);
            window->setCursorPos(center(button->getGeometry()));
            window->setKey(Key::Enter);
            DTK_ASSERT(clicks);
            DTK_ASSERT(!checked);

            window->setKey(Key::Escape);
            if (button->acceptsKeyFocus())
            {
                DTK_ASSERT(!button->hasKeyFocus());
            }

            window->setKey(Key::Tab);
            window->setKey(Key::Tab);
            if (button->acceptsKeyFocus())
            {
                DTK_ASSERT(button->hasKeyFocus());
            }
            window->hide();
            window->show();
            if (button->acceptsKeyFocus())
            {
                DTK_ASSERT(!button->hasKeyFocus());
            }
            window->setCursorEnter(true);
            window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
            if (button->acceptsKeyFocus())
            {
                DTK_ASSERT(button->hasKeyFocus());
            }

            window->setCursorPos(center(button->getGeometry()));
            window->hide();
            window->show();
            window->setCursorPos(center(button->getGeometry()));
            window->setButton(0, true);
            app->tick();
            window->hide();
            window->show();
            window->setCursorPos(center(button->getGeometry()));
            app->tick();
            window->setKey(Key::Enter, true);
            app->tick();
            window->hide();
            window->show();

            app->setDisplayScale(2.F);
            app->tick(1000);
            app->setDisplayScale(1.F);
            app->tick(1000);
        }
    }
}

