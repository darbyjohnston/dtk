// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class StyleTest : public test::ITest
        {
        protected:
            StyleTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~StyleTest();

            static std::shared_ptr<StyleTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _widget();
        };
    }
}

