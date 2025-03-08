// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/ActionTest.h>

#include <dtk/ui/Action.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        ActionTest::ActionTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ActionTest")
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
                DTK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [] {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT(Key::T == a->getShortcut());
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT("Icon" == a->getIcon());
                DTK_ASSERT(Key::T == a->getShortcut());
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    [](bool) {});
                DTK_ASSERT("Test" == a->getText());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    [](bool) {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT("Icon" == a->getIcon());
            }
            {
                auto a = Action::create(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT(Key::T == a->getShortcut());
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
            {
                auto a = Action::create(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                DTK_ASSERT("Test" == a->getText());
                DTK_ASSERT("Icon" == a->getIcon());
                DTK_ASSERT(Key::T == a->getShortcut());
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a->getShortcutModifiers());
            }
        }
    }
}

