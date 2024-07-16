// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class ScrollAreaTest : public test::ITest
        {
        protected:
            ScrollAreaTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ScrollAreaTest();

            static std::shared_ptr<ScrollAreaTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
        };
    }
}

