// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/SizeTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Size.h>

#include <sstream>

namespace dtk
{
    namespace core_test
    {
        SizeTest::SizeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::SizeTest")
        {}

        SizeTest::~SizeTest()
        {}

        std::shared_ptr<SizeTest> SizeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SizeTest>(new SizeTest(context));
        }
        
        void SizeTest::run()
        {
            _members();
            _functions();
            _operators();
            _serialize();
        }
        
        void SizeTest::_members()
        {
            {
                const Size2I s2;
                DTK_ASSERT(0 == s2[0]);
                DTK_ASSERT(0 == s2[1]);
                DTK_ASSERT(s2.data());
                DTK_ASSERT(!s2.isValid());
                const Size3F s3;
                DTK_ASSERT(0.F == s3[0]);
                DTK_ASSERT(0.F == s3[1]);
                DTK_ASSERT(0.F == s3[2]);
                DTK_ASSERT(s3.data());
                DTK_ASSERT(!s3.isValid());
            }
            {
                const Size2I s2(1, 2);
                DTK_ASSERT(1 == s2[0]);
                DTK_ASSERT(2 == s2[1]);
                const Size3F s3(1.F, 2.F, 3.F);
                DTK_ASSERT(1.F == s3[0]);
                DTK_ASSERT(2.F == s3[1]);
                DTK_ASSERT(3.F == s3[2]);
            }
            {
                Size2I s2;
                s2[0] = 1;
                s2[1] = 2;
                DTK_ASSERT(1 == s2[0]);
                DTK_ASSERT(2 == s2[1]);
                Size3F s3;
                s3[0] = 1.F;
                s3[1] = 2.F;
                s3[2] = 3.F;
                DTK_ASSERT(1.F == s3[0]);
                DTK_ASSERT(2.F == s3[1]);
                DTK_ASSERT(3.F == s3[2]);
            }
        }
        
        void SizeTest::_functions()
        {
            {
                const Size2I s(2, 1);
                DTK_ASSERT(2.F == aspectRatio(s));
            }
            {
                const Size2F s(2.F, 1.F);
                DTK_ASSERT(2.F == aspectRatio(s));
            }
            {
                const Size2F s(1.F, 2.F);
                DTK_ASSERT(2.F == area(s));
            }
            {
                const Size3F s(1.F, 2.F, 3.F);
                DTK_ASSERT(6.F == volume(s));
            }
            {
                const Size2I s(1, 2);
                DTK_ASSERT(margin(s, 2) == Size2I(5, 6));
            }
            {
                const Size2I s(5, 6);
                DTK_ASSERT(margin(s, -2, -1) == Size2I(1, 4));
            }
        }
        
        void SizeTest::_operators()
        {
            {
                const Size2I s(1, 2);
                const Size2I s2 = s + 1;
                const Size2I s3 = s - 1;
                DTK_ASSERT(Size2I(2, 3) == s2);
                DTK_ASSERT(Size2I(0, 1) == s3);
            }
            {
                const Size2I s(1, 2);
                DTK_ASSERT(s == Size2I(1, 2));
                DTK_ASSERT(s != Size2I(2, 1));
            }
        }
        
        void SizeTest::_serialize()
        {
            {
                const Size2I s(1, 2);
                std::stringstream ss;
                ss << s;
                Size2I s1;
                ss >> s1;
                DTK_ASSERT(s == s1);
            }
            {
                const Size2F s(1.F, 2.F);
                std::stringstream ss;
                ss << s;
                Size2F s1;
                ss >> s1;
                DTK_ASSERT(s == s1);
            }
            {
                const Size3F s(1.F, 2.F, 3.F);
                std::stringstream ss;
                ss << s;
                Size3F s1;
                ss >> s1;
                DTK_ASSERT(s == s1);
            }
        }
    }
}

