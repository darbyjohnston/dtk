// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/TimerTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/Time.h>
#include <feather-tk/core/Timer.h>

#include <iostream>

namespace feather_tk
{
    namespace core_test
    {
        TimerTest::TimerTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::TimerTest")
        {
            auto timer = Timer::create(context);
            FEATHER_TK_ASSERT(!timer->isRepeating());
            
            auto repeatTimer = Timer::create(context);
            repeatTimer->setRepeating(true);
            FEATHER_TK_ASSERT(repeatTimer->isRepeating());

            const std::chrono::milliseconds timeout(5);
            timer->start(timeout, [] {});
            FEATHER_TK_ASSERT(timer->isActive());
            FEATHER_TK_ASSERT(timeout == timer->getTimeout());
            timer->stop();
            FEATHER_TK_ASSERT(!timer->isActive());

            bool timedout = false;
            timer->start(
                timeout,
                [&timedout]
                {
                    timedout = true;
                });

            int repeatCount = 10;
            repeatTimer->start(
                timeout,
                [&repeatCount](
                    const std::chrono::steady_clock::time_point&,
                    const std::chrono::microseconds&)
                {
                    if (repeatCount > 0)
                    {
                        --repeatCount;
                    }
                });

            auto t0 = std::chrono::steady_clock::now();
            while (!timedout || repeatCount > 0)
            {
                context->tick();
                auto t1 = std::chrono::steady_clock::now();
                sleep(std::chrono::milliseconds(5), t0, t1);
                t0 = t1;
            }
        }

        TimerTest::~TimerTest()
        {}

        std::shared_ptr<TimerTest> TimerTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TimerTest>(new TimerTest(context));
        }
        
        void TimerTest::run()
        {}
    }
}

