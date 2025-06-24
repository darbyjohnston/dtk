// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/RenderOptionsTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/RenderOptions.h>

namespace feather_tk
{
    namespace core_test
    {
        RenderOptionsTest::RenderOptionsTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::RenderOptionsTest")
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
            FEATHER_TK_TEST_ENUM(InputVideoLevels);
            FEATHER_TK_TEST_ENUM(AlphaBlend);
            FEATHER_TK_TEST_ENUM(ImageFilter);
        }
        
        void RenderOptionsTest::_operators()
        {
            {
                const ImageFilters a;
                ImageFilters b;
                FEATHER_TK_ASSERT(a == b);
                b.minify = ImageFilter::Nearest;
                FEATHER_TK_ASSERT(a != b);
            }
            {
                const ImageOptions a;
                ImageOptions b;
                FEATHER_TK_ASSERT(a == b);
                b.cache = false;
                FEATHER_TK_ASSERT(a != b);
            }
        }
    }
}

