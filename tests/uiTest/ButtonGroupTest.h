// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace feather_tk
{
    namespace ui_test
    {
        class ButtonGroupTest : public test::ITest
        {
        protected:
            ButtonGroupTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ButtonGroupTest();

            static std::shared_ptr<ButtonGroupTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

