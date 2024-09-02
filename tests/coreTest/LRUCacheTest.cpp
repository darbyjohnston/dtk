// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/LRUCacheTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/LRUCache.h>

namespace dtk
{
    namespace core_test
    {
        LRUCacheTest::LRUCacheTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::LRUCacheTest")
        {}

        LRUCacheTest::~LRUCacheTest()
        {}

        std::shared_ptr<LRUCacheTest> LRUCacheTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LRUCacheTest>(new LRUCacheTest(context));
        }
        
        void LRUCacheTest::run()
        {
            LRUCache<int, bool> c;
            c.setMax(3);
            c.setMax(3);
            DTK_ASSERT(3 == c.getMax());
            DTK_ASSERT(0 == c.getSize());
            DTK_ASSERT(0 == c.getCount());
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            
            c.add(0, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(1, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(2, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(3, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            DTK_ASSERT(3 == c.getSize());

            DTK_ASSERT(c.contains(2));
            bool v = false;
            DTK_ASSERT(c.get(2, v));
            DTK_ASSERT(v);
            DTK_ASSERT(!c.get(0, v));
            c.remove(2);
            DTK_ASSERT(!c.contains(2));
            c.clear();
            DTK_ASSERT(0 == c.getSize());
            
            c.add(0, true);
            c.add(1, true);
            c.add(2, true);
            c.add(3, true);
            DTK_ASSERT(1 == c.getKeys()[0]);
            DTK_ASSERT(2 == c.getKeys()[1]);
            DTK_ASSERT(3 == c.getKeys()[2]);
            DTK_ASSERT(c.getValues()[0]);
            DTK_ASSERT(c.getValues()[1]);
            DTK_ASSERT(c.getValues()[2]);
            
            c.setMax(2);
            DTK_ASSERT(2 == c.getSize());
        }
    }
}

