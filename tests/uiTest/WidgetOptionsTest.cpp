// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/WidgetOptionsTest.h>

#include <feather-tk/ui/WidgetOptions.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        WidgetOptionsTest::WidgetOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::WidgetOptionsTest")
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
            FEATHER_TK_TEST_ENUM(Orientation);
            FEATHER_TK_TEST_ENUM(Stretch);
            FEATHER_TK_TEST_ENUM(HAlign);
            FEATHER_TK_TEST_ENUM(VAlign);
        }
    }
}

