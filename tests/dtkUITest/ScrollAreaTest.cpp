// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/ScrollAreaTest.h>

#include <dtkUI/ScrollArea.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        ScrollAreaTest::ScrollAreaTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::ScrollAreaTest")
        {}

        ScrollAreaTest::~ScrollAreaTest()
        {}

        std::shared_ptr<ScrollAreaTest> ScrollAreaTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ScrollAreaTest>(new ScrollAreaTest(context));
        }
                
        void ScrollAreaTest::run()
        {
            _enums();
        }
        
        void ScrollAreaTest::_enums()
        {
            DTK_TEST_ENUM(ScrollType);
        }
    }
}

