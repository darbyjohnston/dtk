// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace gl_test
    {
        class RenderTest : public test::ITest
        {
        protected:
            RenderTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RenderTest();

            static std::shared_ptr<RenderTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}
