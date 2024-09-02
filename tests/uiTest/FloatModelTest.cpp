// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <uiTest/FloatModelTest.h>

#include <dtk/ui/FloatModel.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Math.h>

using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        FloatModelTest::FloatModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FloatModelTest")
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
                DTK_ASSERT(.9F == model->getValue());
                DTK_ASSERT(.9F == value);

                model->setRange(RangeF(0.F, .5F));
                DTK_ASSERT(RangeF(0.F, .5F) == model->getRange());
                DTK_ASSERT(RangeF(0.F, .5F) == range);
                DTK_ASSERT(.5F == value);

                model->setStep(.2F);
                DTK_ASSERT(.2F == model->getStep());
                model->decrementStep();
                DTK_ASSERT(fuzzyCompare(.3F, value));
                model->incrementStep();
                DTK_ASSERT(fuzzyCompare(.5F, value));

                model->setLargeStep(.3F);
                DTK_ASSERT(.3F == model->getLargeStep());
                model->decrementLargeStep();
                DTK_ASSERT(fuzzyCompare(.2F, value));
                model->incrementLargeStep();
                DTK_ASSERT(fuzzyCompare(.5F, value));

                model->setDefaultValue(0.F);
                DTK_ASSERT(0.F == model->getDefaultValue());
                DTK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                DTK_ASSERT(0.F == value);
                model->clearDefaultValue();
                DTK_ASSERT(!hasDefaultValue);
            }
        }
    }
}
