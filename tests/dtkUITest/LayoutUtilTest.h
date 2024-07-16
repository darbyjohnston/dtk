// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class LayoutUtilTest : public test::ITest
        {
        protected:
            LayoutUtilTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~LayoutUtilTest();

            static std::shared_ptr<LayoutUtilTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

