// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/EventTest.h>

#include <feather-tk/ui/Event.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        EventTest::EventTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::EventTest")
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
            FEATHER_TK_TEST_ENUM(Key);
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::None)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Shift)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Control)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Alt)));
            _print(getKeyModifierLabel(static_cast<int>(KeyModifier::Super)));
            _print(getShortcutLabel(Key::O, static_cast<int>(KeyModifier::Control)));
        }
    }
}

