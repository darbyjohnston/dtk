// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FloatModelTest.h>

#include <feather-tk/ui/FloatModel.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Math.h>

namespace feather_tk
{
    namespace ui_test
    {
        FloatModelTest::FloatModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FloatModelTest")
        {}

        FloatModelTest::~FloatModelTest()
        {}

        std::shared_ptr<FloatModelTest> FloatModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FloatModelTest>(new FloatModelTest(context));
        }
                
        void FloatModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = FloatModel::create(context);

                float value = 0.F;
                RangeF range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<float>::create(
                    model->observeValue(),
                    [&value](float v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeF>::create(
                    model->observeRange(),
                    [&range](const RangeF& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(.9F);
                FEATHER_TK_ASSERT(.9F == model->getValue());
                FEATHER_TK_ASSERT(.9F == value);

                model->setRange(RangeF(0.F, .5F));
                FEATHER_TK_ASSERT(RangeF(0.F, .5F) == model->getRange());
                FEATHER_TK_ASSERT(RangeF(0.F, .5F) == range);
                FEATHER_TK_ASSERT(.5F == value);

                model->setStep(.2F);
                FEATHER_TK_ASSERT(.2F == model->getStep());
                model->decrementStep();
                FEATHER_TK_ASSERT(fuzzyCompare(.3F, value));
                model->incrementStep();
                FEATHER_TK_ASSERT(fuzzyCompare(.5F, value));

                model->setLargeStep(.3F);
                FEATHER_TK_ASSERT(.3F == model->getLargeStep());
                model->decrementLargeStep();
                FEATHER_TK_ASSERT(fuzzyCompare(.2F, value));
                model->incrementLargeStep();
                FEATHER_TK_ASSERT(fuzzyCompare(.5F, value));

                model->setDefaultValue(0.F);
                FEATHER_TK_ASSERT(0.F == model->getDefaultValue());
                FEATHER_TK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                FEATHER_TK_ASSERT(0.F == value);
                model->clearDefaultValue();
                FEATHER_TK_ASSERT(!hasDefaultValue);
            }
        }
    }
}
