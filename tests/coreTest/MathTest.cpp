// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/MathTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Math.h>

namespace feather_tk
{
    namespace core_test
    {
        MathTest::MathTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::MathTest")
        {}

        MathTest::~MathTest()
        {}

        std::shared_ptr<MathTest> MathTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MathTest>(new MathTest(context));
        }
        
        void MathTest::run()
        {
            for (float i = 0.F; i < 360.F; i += 90.F)
            {
                const float r = deg2rad(i);
                FEATHER_TK_ASSERT(rad2deg(r) == i);
            }
            {
                FEATHER_TK_ASSERT(0 == clamp(-1, 0, 1));
                FEATHER_TK_ASSERT(0 == clamp(0, 0, 1));
                FEATHER_TK_ASSERT(1 == clamp(1, 0, 1));
                FEATHER_TK_ASSERT(1 == clamp(2, 0, 1));
            }
            {
                FEATHER_TK_ASSERT(0.F == lerp(0.F, 0.F, 9.F));
                FEATHER_TK_ASSERT(9.F == lerp(1.F, 0.F, 9.F));
            }
            for (float i = 0.F; i < 1.F; i += .1F)
            {
                _print(Format("smoothstep {0}: {1}").arg(i).arg(smoothStep(i, 0.F, 1.F)));
            }
            for (double i = 0.0; i < 1.0; i += 0.1)
            {
                _print(Format("smoothstep {0}: {1}").arg(i).arg(smoothStep(i, 0.0, 1.0)));
            }
            {
                FEATHER_TK_ASSERT(1 == digits(0));
                FEATHER_TK_ASSERT(2 == digits(10));
                FEATHER_TK_ASSERT(3 == digits(100));
                FEATHER_TK_ASSERT(4 == digits(1000));
                FEATHER_TK_ASSERT(4 == digits(-1000));
            }
            {
                FEATHER_TK_ASSERT(fuzzyCompare(1.0, 1.00000000001));
                FEATHER_TK_ASSERT(fuzzyCompare(1.F, 1.00000001F));
            }
        }
    }
}

