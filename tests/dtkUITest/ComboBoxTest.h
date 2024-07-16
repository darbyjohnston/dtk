// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class ComboBoxTest : public test::ITest
        {
        protected:
            ComboBoxTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ComboBoxTest();

            static std::shared_ptr<ComboBoxTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

