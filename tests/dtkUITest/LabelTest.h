// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class LabelTest : public test::ITest
        {
        protected:
            LabelTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~LabelTest();

            static std::shared_ptr<LabelTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

