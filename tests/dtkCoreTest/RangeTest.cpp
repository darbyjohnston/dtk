// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCoreTest/RangeTest.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Range.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        RangeTest::RangeTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::RangeTest")
        {}

        RangeTest::~RangeTest()
        {}

        std::shared_ptr<RangeTest> RangeTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RangeTest>(new RangeTest(context));
        }
        
        void RangeTest::run()
        {
            _members();
            _functions();
        }
        
        void RangeTest::_members()
        {
            {
                const RangeI r;
                DTK_ASSERT(0 == r.min());
                DTK_ASSERT(0 == r.max());
            }
            {
                const RangeI r(1, 2);
                DTK_ASSERT(1 == r.min());
                DTK_ASSERT(2 == r.max());
            }
            {
                const RangeI a;
                RangeI b;
                DTK_ASSERT(a == b);
                b = RangeI(1, 2);
                DTK_ASSERT(a != b);
                DTK_ASSERT(a < b);
            }
        }
        
        void RangeTest::_functions()
        {
            {
                DTK_ASSERT(contains(RangeI(0, 2), 1));
                DTK_ASSERT(!contains(RangeI(0, 2), 3));
            }
            {
                DTK_ASSERT(intersects(RangeI(0, 2), RangeI(1, 3)));
                DTK_ASSERT(!intersects(RangeI(0, 2), RangeI(3, 4)));
            }
            {
                DTK_ASSERT(expand(RangeI(), 2) == RangeI(0, 2));
                DTK_ASSERT(expand(RangeI(0, 2), RangeI(1, 3)) == RangeI(0, 3));
            }
        }
    }
}

