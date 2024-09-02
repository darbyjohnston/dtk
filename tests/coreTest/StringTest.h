// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class StringTest : public test::ITest
        {
        protected:
            StringTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~StringTest();

            static std::shared_ptr<StringTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _split();
            void _format();
            void _compare();
            void _convert();
        };
    }
}

