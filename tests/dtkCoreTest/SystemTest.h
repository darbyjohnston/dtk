// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class SystemTest : public test::ITest
        {
        protected:
            SystemTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~SystemTest();

            static std::shared_ptr<SystemTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

