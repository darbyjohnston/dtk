// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace gl_test
    {
        class OffscreenBufferTest : public test::ITest
        {
        protected:
            OffscreenBufferTest(const std::shared_ptr<Context>&);

        public:
            virtual ~OffscreenBufferTest();

            static std::shared_ptr<OffscreenBufferTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _members();
            void _functions();
            void _operators();
        };
    }
}

