// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/DoubleModelTest.h>

#include <feather-tk/ui/DoubleModel.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Math.h>

namespace feather_tk
{
    namespace ui_test
    {
        DoubleModelTest::DoubleModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::DoubleModelTest")
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
                FEATHER_TK_ASSERT(0.9 == model->getValue());
                FEATHER_TK_ASSERT(0.9 == value);

                model->setRange(RangeD(0.0, 0.5));
                FEATHER_TK_ASSERT(RangeD(0.0, 0.5) == model->getRange());
                FEATHER_TK_ASSERT(RangeD(0.0, 0.5) == range);
                FEATHER_TK_ASSERT(0.5 == value);

                model->setStep(0.2);
                FEATHER_TK_ASSERT(0.2 == model->getStep());
                model->decrementStep();
                FEATHER_TK_ASSERT(fuzzyCompare(0.3, value));
                model->incrementStep();
                FEATHER_TK_ASSERT(fuzzyCompare(0.5, value));

                model->setLargeStep(0.3);
                FEATHER_TK_ASSERT(0.3 == model->getLargeStep());
                model->decrementLargeStep();
                FEATHER_TK_ASSERT(fuzzyCompare(0.2, value));
                model->incrementLargeStep();
                FEATHER_TK_ASSERT(fuzzyCompare(0.5, value));

                model->setDefaultValue(0.0);
                FEATHER_TK_ASSERT(0.0 == model->getDefaultValue());
                FEATHER_TK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                FEATHER_TK_ASSERT(0.0 == value);
                model->clearDefaultValue();
                FEATHER_TK_ASSERT(!hasDefaultValue);
            }
        }
    }
}

