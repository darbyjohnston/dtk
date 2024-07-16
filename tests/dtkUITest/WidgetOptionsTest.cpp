// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/WidgetOptionsTest.h>

#include <dtkUI/WidgetOptions.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

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

