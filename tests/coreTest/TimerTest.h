// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class TimerTest : public test::ITest
        {
        protected:
            TimerTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~TimerTest();

            static std::shared_ptr<TimerTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

