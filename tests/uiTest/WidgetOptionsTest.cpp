// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/WidgetOptionsTest.h>

#include <dtk/ui/WidgetOptions.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace ui_test
    {
        WidgetOptionsTest::WidgetOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::WidgetOptionsTest")
        {}

        WidgetOptionsTest::~WidgetOptionsTest()
        {}

        std::shared_ptr<WidgetOptionsTest> WidgetOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<WidgetOptionsTest>(new WidgetOptionsTest(context));
        }
                
        void WidgetOptionsTest::run()
        {
            _enums();
        }
        
        void WidgetOptionsTest::_enums()
        {
            DTK_TEST_ENUM(Orientation);
            DTK_TEST_ENUM(Stretch);
            DTK_TEST_ENUM(HAlign);
            DTK_TEST_ENUM(VAlign);
        }
    }
}

