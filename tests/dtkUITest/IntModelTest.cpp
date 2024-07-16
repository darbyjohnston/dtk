// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/IntModelTest.h>

#include <dtkUI/IntModel.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        IntModelTest::IntModelTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::IntModelTest")
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
                DTK_ASSERT(11 == model->getValue());
                DTK_ASSERT(11 == value);

                model->setRange(RangeI(0, 10));
                DTK_ASSERT(RangeI(0, 10) == model->getRange());
                DTK_ASSERT(RangeI(0, 10) == range);
                DTK_ASSERT(10 == value);

                model->setStep(2);
                DTK_ASSERT(2 == model->getStep());
                model->decrementStep();
                DTK_ASSERT(8 == value);
                model->incrementStep();
                DTK_ASSERT(10 == value);

                model->setLargeStep(5);
                DTK_ASSERT(5 == model->getLargeStep());
                model->decrementLargeStep();
                DTK_ASSERT(5 == value);
                model->incrementLargeStep();
                DTK_ASSERT(10 == value);

                model->setDefaultValue(0);
                DTK_ASSERT(0 == model->getDefaultValue());
                DTK_ASSERT(hasDefaultValue);
                model->setDefaultValue();
                DTK_ASSERT(0 == value);
                model->clearDefaultValue();
                DTK_ASSERT(!hasDefaultValue);
            }
        }
    }
}

