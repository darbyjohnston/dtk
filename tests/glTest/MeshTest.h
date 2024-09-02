// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace gl_test
    {
        class MeshTest : public test::ITest
        {
        protected:
            MeshTest(const std::shared_ptr<Context>&);

        public:
            virtual ~MeshTest();

            static std::shared_ptr<MeshTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
            void _members();
            void _functions();
        };
    }
}
