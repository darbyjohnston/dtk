// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/IntModelTest.h>

#include <feather-tk/ui/IntModel.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace ui_test
    {
        IntModelTest::IntModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::IntModelTest")
        {}

        IntModelTest::~IntModelTest()
        {}

        std::shared_ptr<IntModelTest> IntModelTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<IntModelTest>(new IntModelTest(context));
        }
                
        void IntModelTest::run()
        {
            if (auto context = _context.lock())
            {
                auto model = IntModel::create(context);

                int value = 0;
                RangeI range;
                bool hasDefaultValue = false;
                auto valueObserver = ValueObserver<int>::create(
                    model->observeValue(),
                    [&value](int v)
                    {
                        value = v;
                    });
                auto rangeObserver = ValueObserver<RangeI>::create(
                    model->observeRange(),
                    [&range](const RangeI& r)
                    {
                        range = r;
                    });
                auto defaultValueObserver = ValueObserver<bool>::create(
                    model->observeHasDefaultValue(),
                    [&hasDefaultValue](bool value)
                    {
                        hasDefaultValue = value;
                    });

                model->setValue(11);
                FEATHER_TK_ASSERT(11 == model->getValue());
                FEATHER_TK_ASSERT(11 == value);

                model->setRange(RangeI(0, 10));
                FEATHER_TK_ASSERT(RangeI(0, 10) == model->getRange());
                FEATHER_TK_ASSERT(RangeI(0, 10) == range);
                FEATHER_TK_ASSERT(10 == value);

                model->setStep(2);
                FEATHER_TK_ASSERT(2 == model->getStep());
                model->decrementStep();
                FEATHER_TK_ASSERT(8 == value);
                model->incrementStep();
                FEATHER_TK_ASSERT(10 == value);

                model->setLargeStep(5);
                FEATHER_TK_ASSERT(5 == model->getLargeStep());
                model->decrementLargeStep();
                FEATHER_TK_ASSERT(5 == value);
                model->incrementLargeStep();
                FEATHER_TK_ASSERT(10 == value);

                model->setDefaultValue(0);
                FEATHER_TK_ASSERT(0 == model->getDefaultValue());
                FEATHER_TK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                FEATHER_TK_ASSERT(0 == value);
                model->clearDefaultValue();
                FEATHER_TK_ASSERT(!hasDefaultValue);
            }
        }
    }
}

