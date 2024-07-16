// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class FormatTest : public test::ITest
        {
        protected:
            FormatTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FormatTest();

            static std::shared_ptr<FormatTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

