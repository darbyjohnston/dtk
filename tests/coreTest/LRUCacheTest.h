// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <testLib/ITest.h>

namespace dtk
{
    namespace core_test
    {
        class LRUCacheTest : public test::ITest
        {
        protected:
            LRUCacheTest(const std::shared_ptr<Context>&);

        public:
            virtual ~LRUCacheTest();

            static std::shared_ptr<LRUCacheTest> create(
                const std::shared_ptr<Context>&);

            void run() override;
        };
    }
}

