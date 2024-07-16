// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace app_test
    {
        class AppTest : public test::ITest
        {
        protected:
            AppTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~AppTest();

            static std::shared_ptr<AppTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

