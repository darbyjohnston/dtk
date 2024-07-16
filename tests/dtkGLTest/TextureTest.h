// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace gl_test
    {
        class TextureTest : public test::ITest
        {
        protected:
            TextureTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~TextureTest();

            static std::shared_ptr<TextureTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _enums();
            void _members();
            void _functions();
            void _operators();
        };
    }
}

