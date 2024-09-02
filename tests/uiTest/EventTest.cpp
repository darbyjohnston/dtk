// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/EventTest.h>

#include <dtk/ui/Event.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        EventTest::EventTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::EventTest")
        {}

        EventTest::~EventTest()
        {}

        std::shared_ptr<EventTest> EventTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<EventTest>(new EventTest(context));
        }
                
        void EventTest::run()
        {
            _enums();
        }
        
        void EventTest::_enums()
        {
            DTK_TEST_ENUM(Key);
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::None)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Shift)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Control)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Alt)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Super)));
            _print(getShortcutLabel(Key::O, static_cast<int>(KeyModifier::Control)));
        }
    }
}

