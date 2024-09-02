// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class FileEditTest : public test::ITest
        {
        protected:
            FileEditTest(const std::shared_ptr<Context>&);

        public:
            virtual ~FileEditTest();

            static std::shared_ptr<FileEditTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

