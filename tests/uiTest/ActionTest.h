// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class ActionTest : public test::ITest
        {
        protected:
            ActionTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ActionTest();

            static std::shared_ptr<ActionTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

