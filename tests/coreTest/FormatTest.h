// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class FormatTest : public test::ITest
        {
        protected:
            FormatTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FormatTest();

            static std::shared_ptr<FormatTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
