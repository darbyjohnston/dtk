// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class EventTest : public test::ITest
        {
        protected:
            EventTest(const std::shared_ptr<Context>&);

        public:
            virtual ~EventTest();

            static std::shared_ptr<EventTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _enums();
        };
    }
}

