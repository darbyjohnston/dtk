// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class FloatModelTest : public test::ITest
        {
        protected:
            FloatModelTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FloatModelTest();

            static std::shared_ptr<FloatModelTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
