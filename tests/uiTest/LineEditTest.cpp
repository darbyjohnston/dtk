// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/LineEditTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/IClipboard.h>
#include <dtk/ui/LineEdit.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        LineEditTest::LineEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::LineEditTest")
        {}

        LineEditTest::~LineEditTest()
        {}

        std::shared_ptr<LineEditTest> LineEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LineEditTest>(new LineEditTest(context));
        }
                
        void LineEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("LineEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "LineEditTest",
                    "Line edit test.");
                auto window = Window::create(context, app, "LineEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = LineEdit::create(context, layout);
                std::string text;
                edit->setTextCallback(
                    [&text](const std::string& value)
                    {
                        text = value;
                    });
                std::string textChanged;
                edit->setTextChangedCallback(
                    [&textChanged](const std::string& value)
                    {
                        textChanged = value;
                    });
                edit->setText("Test");
                edit->setText("Test");
                DTK_ASSERT("Test" == edit->getText());
                edit->clearText();
                DTK_ASSERT(edit->getText().empty());
                edit->setFormat("00.00");
                edit->setFormat("00.00");
                DTK_ASSERT("00.00" == edit->getFormat());
                edit->setFormat("");
                edit->setFontRole(FontRole::Mono);
                edit->setFontRole(FontRole::Mono);
                DTK_ASSERT(FontRole::Mono == edit->getFontRole());
                edit->setFontRole(FontRole::Label);

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setText("T");
                DTK_ASSERT("T" == textChanged);
                window->setText("e");
                DTK_ASSERT("Te" == textChanged);
                window->setText("s");
                DTK_ASSERT("Tes" == textChanged);
                window->setText("t");
                DTK_ASSERT("Test" == textChanged);
                window->setKey(Key::Enter);
                DTK_ASSERT("Test" == text);

                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::C, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT("Test" == window->getClipboard()->getText());
                window->setKey(Key::X, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT(textChanged.empty());
                window->setKey(Key::V, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT("Test" == textChanged);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::V, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT("Test" == textChanged);

                window->setKey(Key::Left, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Right, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Home, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Delete, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT("est" == textChanged);
                window->setKey(Key::End, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Backspace, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT("es" == textChanged);
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setKey(Key::Backspace, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT(textChanged.empty());
                window->setText("T");
                window->setKey(Key::A, static_cast<int>(KeyModifier::Control));
                window->setText("t");
                DTK_ASSERT("t" == textChanged);

                window->setKey(Key::Escape, static_cast<int>(KeyModifier::Control));
                DTK_ASSERT(!edit->hasKeyFocus());

                Box2I g = edit->getGeometry();
                const V2I c = center(g);
                window->setCursorPos(c);
                window->setButton(0, true);
                window->setCursorPos(V2I(g.max.x, c.y));
                window->setButton(0, false);

                edit->takeKeyFocus();
                app->tick();
                edit->hide();
                app->tick();
                edit->show();
                app->tick();
                DTK_ASSERT(!edit->hasKeyFocus());

                edit->takeKeyFocus();
                app->tick();
                edit->setEnabled(false);
                app->tick();
                edit->setEnabled(true);
                app->tick();
                DTK_ASSERT(!edit->hasKeyFocus());
            }
        }
    }
}

