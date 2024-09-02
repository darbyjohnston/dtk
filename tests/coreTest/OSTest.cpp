// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/OSTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/OS.h>
#include <dtk/core/String.h>

namespace dtk
{
    namespace core_test
    {
        OSTest::OSTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::OSTest")
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
            setEnv("DTK_OSTEST_ENV", "ABC");
            std::string s;
            DTK_ASSERT(getEnv("DTK_OSTEST_ENV", s));
            DTK_ASSERT("ABC" == s);
            setEnv("DTK_OSTEST_ENV", "123");
            int i = 0;
            DTK_ASSERT(getEnv("DTK_OSTEST_ENV", i));
            DTK_ASSERT(123 == i);
            setEnv("DTK_OSTEST_ENV", join({ "A", "B", "C" }, envListSeparator));
            std::vector<std::string> l;
            DTK_ASSERT(getEnv("DTK_OSTEST_ENV", l));
            DTK_ASSERT(std::vector<std::string>({ "A", "B", "C" }) == l);
            delEnv("DTK_OSTEST_ENV");
            DTK_ASSERT(!getEnv("DTK_OSTEST_ENV", s));
            DTK_ASSERT(!getEnv("DTK_OSTEST_ENV", i));
            DTK_ASSERT(!getEnv("DTK_OSTEST_ENV", l));
        }
    }
}

