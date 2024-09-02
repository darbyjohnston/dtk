// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/FormatTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        FormatTest::FormatTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::FormatTest")
        {}

        FormatTest::~FormatTest()
        {}

        std::shared_ptr<FormatTest> FormatTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FormatTest>(new FormatTest(context));
        }
        
        void FormatTest::run()
        {
            {
                DTK_ASSERT("abcABC" == Format("{0}{1}").arg("abc").arg("ABC").str());
                DTK_ASSERT("01" == Format("{0}{1}").arg(0).arg(1).str());
                DTK_ASSERT("01" == Format("{0}{1}").arg(int8_t(0)).arg(int8_t(1)).str());
                DTK_ASSERT("01" == Format("{0}{1}").arg(uint8_t(0)).arg(uint8_t(1)).str());
                DTK_ASSERT("01" == Format("{0}{1}").arg(int16_t(0)).arg(int16_t(1)).str());
                DTK_ASSERT("01" == Format("{0}{1}").arg(uint16_t(0)).arg(uint16_t(1)).str());
                DTK_ASSERT("00.12" == Format("{0}{1}").arg(0.F).arg(.123F, 2).str());
                DTK_ASSERT("00.12" == Format("{0}{1}").arg(0.0).arg(0.123, 2).str());
            }
            try
            {
                Format("{0}{0}").arg("abc").arg("ABC");
            }
            catch (const std::exception&)
            {}
            try
            {
                Format("{0}").arg("abc").arg("ABC");
            }
            catch (const std::exception&)
            {}
            {
                std::stringstream ss;
                ss << Format("{0}{1}").arg("abc").arg("ABC");
                _print(ss.str());
            }
        }
    }
}

