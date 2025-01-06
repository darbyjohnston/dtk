// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/MathTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Math.h>

namespace dtk
{
    namespace core_test
    {
        MathTest::MathTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::MathTest")
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
                DTK_ASSERT(rad2deg(r) == i);
            }
            {
                DTK_ASSERT(0 == clamp(-1, 0, 1));
                DTK_ASSERT(0 == clamp(0, 0, 1));
                DTK_ASSERT(1 == clamp(1, 0, 1));
                DTK_ASSERT(1 == clamp(2, 0, 1));
            }
            {
                DTK_ASSERT(0.F == lerp(0.F, 0.F, 9.F));
                DTK_ASSERT(9.F == lerp(1.F, 0.F, 9.F));
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
                DTK_ASSERT(1 == digits(0));
                DTK_ASSERT(2 == digits(10));
                DTK_ASSERT(3 == digits(100));
                DTK_ASSERT(4 == digits(1000));
                DTK_ASSERT(4 == digits(-1000));
            }
            {
                DTK_ASSERT(fuzzyCompare(1.0, 1.00000000001));
                DTK_ASSERT(fuzzyCompare(1.F, 1.00000001F));
            }
        }
    }
}

