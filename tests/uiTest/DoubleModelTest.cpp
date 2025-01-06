// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleModelTest.h>

#include <dtk/ui/DoubleModel.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Math.h>

namespace dtk
{
    namespace ui_test
    {
        DoubleModelTest::DoubleModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::DoubleModelTest")
        {}

        DoubleModelTest::~DoubleModelTest()
        {}

        std::shared_ptr<DoubleModelTest> DoubleModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DoubleModelTest>(new DoubleModelTest(context));
        }
                
        void DoubleModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = DoubleModel::create(context);

                double value = 0.0;
                RangeD range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<double>::create(
                    model->observeValue(),
                    [&value](double v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeD>::create(
                    model->observeRange(),
                    [&range](const RangeD& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(0.9);
                DTK_ASSERT(0.9 == model->getValue());
                DTK_ASSERT(0.9 == value);

                model->setRange(RangeD(0.0, 0.5));
                DTK_ASSERT(RangeD(0.0, 0.5) == model->getRange());
                DTK_ASSERT(RangeD(0.0, 0.5) == range);
                DTK_ASSERT(0.5 == value);

                model->setStep(0.2);
                DTK_ASSERT(0.2 == model->getStep());
                model->decrementStep();
                DTK_ASSERT(fuzzyCompare(0.3, value));
                model->incrementStep();
                DTK_ASSERT(fuzzyCompare(0.5, value));

                model->setLargeStep(0.3);
                DTK_ASSERT(0.3 == model->getLargeStep());
                model->decrementLargeStep();
                DTK_ASSERT(fuzzyCompare(0.2, value));
                model->incrementLargeStep();
                DTK_ASSERT(fuzzyCompare(0.5, value));

                model->setDefaultValue(0.0);
                DTK_ASSERT(0.0 == model->getDefaultValue());
                DTK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                DTK_ASSERT(0.0 == value);
                model->clearDefaultValue();
                DTK_ASSERT(!hasDefaultValue);
            }
        }
    }
}

