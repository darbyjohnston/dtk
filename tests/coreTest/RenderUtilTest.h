// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace core_test
    {
        class RenderUtilTest : public test::ITest
        {
        protected:
            RenderUtilTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RenderUtilTest();

            static std::shared_ptr<RenderUtilTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

