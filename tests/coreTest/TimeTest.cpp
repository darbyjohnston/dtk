// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/TimeTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Time.h>

namespace dtk
{
    namespace core_test
    {
        TimeTest::TimeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::TimeTest")
        {}

        TimeTest::~TimeTest()
        {}

        std::shared_ptr<TimeTest> TimeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TimeTest>(new TimeTest(context));
        }
        
        void TimeTest::run()
        {
            _sleep();
            _rational();
        }
        
        void TimeTest::_sleep()
        {
            const auto t0 = std::chrono::steady_clock::now();
            sleep(std::chrono::seconds(1));
            const auto t1 = std::chrono::steady_clock::now();
            sleep(std::chrono::seconds(2), t0, t1);
        }

        void TimeTest::_rational()
        {
            DTK_ASSERT(toRational(24.0) == std::make_pair(24, 1));
            DTK_ASSERT(toRational(24.5) == std::make_pair(24, 1));
            DTK_ASSERT(toRational(30.0) == std::make_pair(30, 1));
        }
    }
}

