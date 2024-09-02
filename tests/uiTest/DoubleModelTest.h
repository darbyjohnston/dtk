// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class DoubleModelTest : public test::ITest
        {
        protected:
            DoubleModelTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~DoubleModelTest();

            static std::shared_ptr<DoubleModelTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

