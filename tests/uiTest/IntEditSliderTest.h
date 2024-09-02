// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class IntEditSliderTest : public test::ITest
        {
        protected:
            IntEditSliderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IntEditSliderTest();

            static std::shared_ptr<IntEditSliderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

