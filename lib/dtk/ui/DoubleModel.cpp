// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/DoubleModel.h>

#include <dtk/core/Math.h>

namespace dtk
{
    struct DoubleModel::Private
    {
        std::shared_ptr<ObservableValue<double> > value;
        std::shared_ptr<ObservableValue<RangeD> > range;
        double step = 0.1;
        double largeStep = 1.0;
        std::shared_ptr<ObservableValue<bool> > hasDefaultValue;
        double defaultValue = 0.0;
    };

    void DoubleModel::_init(const std::shared_ptr<Context>&)
    {
        DTK_P();
        p.value = ObservableValue<double>::create(0.0);
        p.range = ObservableValue<RangeD>::create(RangeD(0.0, 1.0));
        p.hasDefaultValue = ObservableValue<bool>::create(false);
    }

    DoubleModel::DoubleModel() :
        _p(new Private)
    {}

    DoubleModel::~DoubleModel()
    {}

    std::shared_ptr<DoubleModel> DoubleModel::create(
        const std::shared_ptr<Context>& context)
    {
        auto out = std::shared_ptr<DoubleModel>(new DoubleModel);
        out->_init(context);
        return out;
    }

    double DoubleModel::getValue() const
    {
        return _p->value->get();
    }

    void DoubleModel::setValue(double value)
    {
        DTK_P();
        const RangeD& range = p.range->get();
        const double tmp = clamp(value, range.min(), range.max());
        _p->value->setIfChanged(tmp);
    }

    std::shared_ptr<IObservableValue<double> > DoubleModel::observeValue() const
    {
        return _p->value;
    }

    const RangeD& DoubleModel::getRange() const
    {
        return _p->range->get();
    }

    void DoubleModel::setRange(const RangeD& range)
    {
        DTK_P();
        if (p.range->setIfChanged(range))
        {
            setValue(p.value->get());
        }
    }

    std::shared_ptr<IObservableValue<RangeD> > DoubleModel::observeRange() const
    {
        return _p->range;
    }

    double DoubleModel::getStep() const
    {
        return _p->step;
    }

    void DoubleModel::setStep(double value)
    {
        _p->step = value;
    }

    void DoubleModel::incrementStep()
    {
        DTK_P();
        setValue(p.value->get() + p.step);
    }

    void DoubleModel::decrementStep()
    {
        DTK_P();
        setValue(p.value->get() - p.step);
    }

    double DoubleModel::getLargeStep() const
    {
        return _p->largeStep;
    }

    void DoubleModel::setLargeStep(double value)
    {
        _p->largeStep = value;
    }

    void DoubleModel::incrementLargeStep()
    {
        DTK_P();
        setValue(p.value->get() + p.largeStep);
    }

    void DoubleModel::decrementLargeStep()
    {
        DTK_P();
        setValue(p.value->get() - p.largeStep);
    }

    bool DoubleModel::hasDefaultValue() const
    {
        return _p->hasDefaultValue->get();
    }

    std::shared_ptr<IObservableValue<bool> > DoubleModel::observeHasDefaultValue() const
    {
        return _p->hasDefaultValue;
    }

    double DoubleModel::getDefaultValue() const
    {
        return _p->defaultValue;
    }

    void DoubleModel::setDefaultValue(double value)
    {
        _p->hasDefaultValue->setIfChanged(true);
        _p->defaultValue = value;
    }

    void DoubleModel::setDefaultValue()
    {
        setValue(_p->defaultValue);
    }

    void DoubleModel::clearDefaultValue()
    {
        _p->hasDefaultValue->setIfChanged(false);
    }
}