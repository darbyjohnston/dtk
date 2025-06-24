// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/ErrorTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Error.h>

namespace feather_tk
{
    namespace core_test
    {
        ErrorTest::ErrorTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::ErrorTest")
        {}

        ErrorTest::~ErrorTest()
        {}

        std::shared_ptr<ErrorTest> ErrorTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ErrorTest>(new ErrorTest(context));
        }
        
        void ErrorTest::run()
        {
            try
            {
                throw ParseError();
            }
            catch (const std::exception&)
            {}
        }
    }
}

