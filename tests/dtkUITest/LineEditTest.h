// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class LineEditTest : public test::ITest
        {
        protected:
            LineEditTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~LineEditTest();

            static std::shared_ptr<LineEditTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

