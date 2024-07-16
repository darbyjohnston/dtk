// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class CommandTest : public test::ITest
        {
        protected:
            CommandTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~CommandTest();

            static std::shared_ptr<CommandTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

