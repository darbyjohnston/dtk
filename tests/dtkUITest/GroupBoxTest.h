// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class GroupBoxTest : public test::ITest
        {
        protected:
            GroupBoxTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~GroupBoxTest();

            static std::shared_ptr<GroupBoxTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

