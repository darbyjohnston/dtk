// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class IconTest : public test::ITest
        {
        protected:
            IconTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~IconTest();

            static std::shared_ptr<IconTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

