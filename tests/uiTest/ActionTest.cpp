// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/ActionTest.h>

#include <dtk/ui/Action.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

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
                const Action a;
                DTK_ASSERT(a.text.empty());
            }
            {
                const Action a(
                    "Test",
                    [] {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    [] {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT("Icon" == a.icon);
                DTK_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT(Key::T == a.shortcut);
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                DTK_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [] {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT("Icon" == a.icon);
                DTK_ASSERT(Key::T == a.shortcut);
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                DTK_ASSERT(a.callback);
            }
            {
                const Action a(
                    "Test",
                    [](bool) {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    [](bool) {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT("Icon" == a.icon);
                DTK_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT(Key::T == a.shortcut);
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                DTK_ASSERT(a.checkedCallback);
            }
            {
                const Action a(
                    "Test",
                    "Icon",
                    Key::T,
                    static_cast<int>(KeyModifier::Control),
                    [](bool) {});
                DTK_ASSERT("Test" == a.text);
                DTK_ASSERT("Icon" == a.icon);
                DTK_ASSERT(Key::T == a.shortcut);
                DTK_ASSERT(static_cast<int>(KeyModifier::Control) == a.shortcutModifiers);
                DTK_ASSERT(a.checkedCallback);
            }
        }
    }
}

