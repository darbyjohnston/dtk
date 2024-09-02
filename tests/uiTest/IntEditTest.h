// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class IntEditTest : public test::ITest
        {
        protected:
            IntEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~IntEditTest();

            static std::shared_ptr<IntEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
