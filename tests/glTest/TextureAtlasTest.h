// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace gl_test
    {
        class TextureAtlasTest : public test::ITest
        {
        protected:
            TextureAtlasTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~TextureAtlasTest();

            static std::shared_ptr<TextureAtlasTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;
        };
    }
}

