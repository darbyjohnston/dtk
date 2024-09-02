// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class WidgetOptionsTest : public test::ITest
        {
        protected:
            WidgetOptionsTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~WidgetOptionsTest();

            static std::shared_ptr<WidgetOptionsTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
        };
    }
}

