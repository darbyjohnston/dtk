// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ActionTest.h>

#include <feather-tk/ui/Action.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        ActionTest::ActionTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::ActionTest")
        {}

        ActionTest::~ActionTest()
        {}

        std::shared_ptr<ActionTest> ActionTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ActionTest>(new ActionTest(context));
        }
                
        void ActionTest::run()
        {
            {
                auto a = Action::create(
                    "Test",
                    [] {});
                FEATHER_TK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [] {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT(Key::T == a->getShortcut());
                FEATHER_TK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT("Icon" == a->getIcon());
                FEATHER_TK_ASSERT(Key::T == a->getShortcut());
                FEATHER_TK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    [](bool) {});
                FEATHER_TK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [](bool) {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT(Key::T == a->getShortcut());
                FEATHER_TK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                FEATHER_TK_ASSERT("Test" == a->getText());
                FEATHER_TK_ASSERT("Icon" == a->getIcon());
                FEATHER_TK_ASSERT(Key::T == a->getShortcut());
                FEATHER_TK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
        }
    }
}

