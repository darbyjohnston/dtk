// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class PNGTest : public test::ITest
        {
        protected:
            PNGTest(const std::shared_ptr<Context>&);

        public:
            virtual ~PNGTest();

            static std::shared_ptr<PNGTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

