// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class DoubleEditTest : public test::ITest
        {
        protected:
            DoubleEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~DoubleEditTest();

            static std::shared_ptr<DoubleEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
