// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class TabWidgetTest : public test::ITest
        {
        protected:
            TabWidgetTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~TabWidgetTest();

            static std::shared_ptr<TabWidgetTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _bar();
            void _widget();
        };
    }
}

