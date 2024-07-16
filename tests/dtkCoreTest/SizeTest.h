// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class SizeTest : public test::ITest
        {
        protected:
            SizeTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~SizeTest();

            static std::shared_ptr<SizeTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _members();
            void _functions();
            void _operators();
            void _serialize();
        };
    }
}

