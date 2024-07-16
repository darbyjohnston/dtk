// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class ColorTest : public test::ITest
        {
        protected:
            ColorTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ColorTest();

            static std::shared_ptr<ColorTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _members();
            void _operators();
            void _serialize();
        };
    }
}

