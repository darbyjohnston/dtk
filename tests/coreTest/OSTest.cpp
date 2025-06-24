// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/OSTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/OS.h>
#include <feather-tk/core/String.h>

namespace feather_tk
{
    namespace core_test
    {
        OSTest::OSTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::OSTest")
        {}

        OSTest::~OSTest()
        {}

        std::shared_ptr<OSTest> OSTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<OSTest>(new OSTest(context));
        }
        
        void OSTest::run()
        {
            _env();
        }
        
        void OSTest::_env()
        {
            setEnv("FEATHER_TK_OSTEST_ENV", "ABC");
            std::string s;
            FEATHER_TK_ASSERT(getEnv("FEATHER_TK_OSTEST_ENV", s));
            FEATHER_TK_ASSERT("ABC" == s);
            setEnv("FEATHER_TK_OSTEST_ENV", "123");
            int i = 0;
            FEATHER_TK_ASSERT(getEnv("FEATHER_TK_OSTEST_ENV", i));
            FEATHER_TK_ASSERT(123 == i);
            setEnv("FEATHER_TK_OSTEST_ENV", join({ "A", "B", "C" }, envListSeparator));
            std::vector<std::string> l;
            FEATHER_TK_ASSERT(getEnv("FEATHER_TK_OSTEST_ENV", l));
            FEATHER_TK_ASSERT(std::vector<std::string>({ "A", "B", "C" }) == l);
            delEnv("FEATHER_TK_OSTEST_ENV");
            FEATHER_TK_ASSERT(!getEnv("FEATHER_TK_OSTEST_ENV", s));
            FEATHER_TK_ASSERT(!getEnv("FEATHER_TK_OSTEST_ENV", i));
            FEATHER_TK_ASSERT(!getEnv("FEATHER_TK_OSTEST_ENV", l));
        }
    }
}

