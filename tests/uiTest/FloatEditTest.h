// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class FloatEditTest : public test::ITest
        {
        protected:
            FloatEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FloatEditTest();

            static std::shared_ptr<FloatEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

