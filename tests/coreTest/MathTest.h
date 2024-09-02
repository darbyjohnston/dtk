// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class MathTest : public test::ITest
        {
        protected:
            MathTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~MathTest();

            static std::shared_ptr<MathTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

