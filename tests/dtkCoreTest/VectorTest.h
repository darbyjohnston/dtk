// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class VectorTest : public test::ITest
        {
        protected:
            VectorTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~VectorTest();

            static std::shared_ptr<VectorTest> create(
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

