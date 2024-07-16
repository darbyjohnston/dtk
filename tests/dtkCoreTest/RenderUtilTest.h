// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class RenderUtilTest : public test::ITest
        {
        protected:
            RenderUtilTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~RenderUtilTest();

            static std::shared_ptr<RenderUtilTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

