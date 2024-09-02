// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace app_test
    {
        class CmdLineTest : public test::ITest
        {
        protected:
            CmdLineTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~CmdLineTest();

            static std::shared_ptr<CmdLineTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

