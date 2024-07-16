// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class FloatSliderTest : public test::ITest
        {
        protected:
            FloatSliderTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FloatSliderTest();

            static std::shared_ptr<FloatSliderTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

