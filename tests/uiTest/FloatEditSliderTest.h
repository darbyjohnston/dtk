// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class FloatEditSliderTest : public test::ITest
        {
        protected:
            FloatEditSliderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FloatEditSliderTest();

            static std::shared_ptr<FloatEditSliderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

