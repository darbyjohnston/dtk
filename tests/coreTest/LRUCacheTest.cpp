// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/LRUCacheTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/LRUCache.h>

namespace feather_tk
{
    namespace core_test
    {
        LRUCacheTest::LRUCacheTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::LRUCacheTest")
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
            FEATHER_TK_ASSERT(3 == c.getMax());
            FEATHER_TK_ASSERT(0 == c.getSize());
            FEATHER_TK_ASSERT(0 == c.getCount());
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            
            c.add(0, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(1, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(2, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(3, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            FEATHER_TK_ASSERT(3 == c.getSize());

            FEATHER_TK_ASSERT(c.contains(2));
            bool v = false;
            FEATHER_TK_ASSERT(c.get(2, v));
            FEATHER_TK_ASSERT(v);
            FEATHER_TK_ASSERT(!c.get(0, v));
            c.remove(2);
            FEATHER_TK_ASSERT(!c.contains(2));
            c.clear();
            FEATHER_TK_ASSERT(0 == c.getSize());
            
            c.add(0, true);
            c.add(1, true);
            c.add(2, true);
            c.add(3, true);
            FEATHER_TK_ASSERT(1 == c.getKeys()[0]);
            FEATHER_TK_ASSERT(2 == c.getKeys()[1]);
            FEATHER_TK_ASSERT(3 == c.getKeys()[2]);
            FEATHER_TK_ASSERT(c.getValues()[0]);
            FEATHER_TK_ASSERT(c.getValues()[1]);
            FEATHER_TK_ASSERT(c.getValues()[2]);
            
            c.setMax(2);
            FEATHER_TK_ASSERT(2 == c.getSize());
        }
    }
}

