// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace ui_test
    {
        class StackLayoutTest : public test::ITest
        {
        protected:
            StackLayoutTest(const std::shared_ptr<Context>&);

        public:
            virtual ~StackLayoutTest();

            static std::shared_ptr<StackLayoutTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

