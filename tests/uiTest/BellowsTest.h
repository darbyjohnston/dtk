// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class BellowsTest : public test::ITest
        {
        protected:
            BellowsTest(const std::shared_ptr<Context>&);

        public:
            virtual ~BellowsTest();

            static std::shared_ptr<BellowsTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
