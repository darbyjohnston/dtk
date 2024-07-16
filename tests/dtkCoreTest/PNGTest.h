// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class PNGTest : public test::ITest
        {
        protected:
            PNGTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~PNGTest();

            static std::shared_ptr<PNGTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

