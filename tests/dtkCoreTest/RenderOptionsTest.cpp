// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCoreTest/RenderOptionsTest.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>
#include <dtkCore/RenderOptions.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        RenderOptionsTest::RenderOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::RenderOptionsTest")
        {}

        RenderOptionsTest::~RenderOptionsTest()
        {}

        std::shared_ptr<RenderOptionsTest> RenderOptionsTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RenderOptionsTest>(new RenderOptionsTest(context));
        }
        
        void RenderOptionsTest::run()
        {
            _enums();
            _operators();
        }
        
        void RenderOptionsTest::_enums()
        {
            DTK_TEST_ENUM(InputVideoLevels);
            DTK_TEST_ENUM(AlphaBlend);
            DTK_TEST_ENUM(ImageFilter);
        }
        
        void RenderOptionsTest::_operators()
        {
            {
                const ImageFilters a;
                ImageFilters b;
                DTK_ASSERT(a == b);
                b.minify = ImageFilter::Nearest;
                DTK_ASSERT(a != b);
            }
            {
                const ImageOptions a;
                ImageOptions b;
                DTK_ASSERT(a == b);
                b.cache = false;
                DTK_ASSERT(a != b);
            }
        }
    }
}

