// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class IntSliderTest : public test::ITest
        {
        protected:
            IntSliderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~IntSliderTest();

            static std::shared_ptr<IntSliderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

