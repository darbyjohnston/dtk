// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class FileIOTest : public test::ITest
        {
        protected:
            FileIOTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~FileIOTest();

            static std::shared_ptr<FileIOTest> create(
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

