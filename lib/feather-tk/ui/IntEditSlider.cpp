// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IntEditSlider.h>

#include <feather-tk/ui/IntEdit.h>
#include <feather-tk/ui/IntSlider.h>
#include <feather-tk/ui/RowLayout.h>

namespace feather_tk
{
    struct IntEditSlider::Private
    {
        std::shared_ptr<IntModel> model;

        std::shared_ptr<IntEdit> edit;
        std::shared_ptr<IntSlider> slider;
        std::shared_ptr<IntResetButton> resetButton;
        std::shared_ptr<HorizontalLayout> layout;

        std::function<void(int)> callback;
        std::shared_ptr<ValueObserver<int> > valueObserver;
    };

    void IntEditSlider::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IntModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::IntEditSlider", parent);
        FEATHER_TK_P();

        setHStretch(Stretch::Expanding);

        p.model = model;

        p.edit = IntEdit::create(context, p.model);

        p.slider = IntSlider::create(context, p.model);

        p.resetButton = IntResetButton::create(context, p.model);

        p.layout = HorizontalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::SpacingTool);
        p.edit->setParent(p.layout);
        p.slider->setParent(p.layout);
        p.slider->setHStretch(Stretch::Expanding);
        p.resetButton->setParent(p.layout);

        p.valueObserver = ValueObserver<int>::create(
            p.model->observeValue(),
            [this](int value)
            {
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });
    }

    IntEditSlider::IntEditSlider() :
        _p(new Private)
    {}

    IntEditSlider::~IntEditSlider()
    {}

    std::shared_ptr<IntEditSlider> IntEditSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<IntEditSlider>(new IntEditSlider);
        out->_init(context, IntModel::create(context), parent);
        return out;
    }

    std::shared_ptr<IntEditSlider> IntEditSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IntModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<IntEditSlider>(new IntEditSlider);
        out->_init(context, model, parent);
        return out;
    }

    int IntEditSlider::getValue() const
    {
        return _p->model->getValue();
    }

    void IntEditSlider::setValue(int value)
    {
        _p->model->setValue(value);
    }

    void IntEditSlider::setCallback(const std::function<void(int)>& value)
    {
        _p->callback = value;
    }

    const RangeI& IntEditSlider::getRange() const
    {
        return _p->model->getRange();
    }

    void IntEditSlider::setRange(const RangeI& value)
    {
        _p->model->setRange(value);
    }

    void IntEditSlider::setRange(int min, int max)
    {
        _p->model->setRange(RangeI(min, max));
    }

    int IntEditSlider::getStep() const
    {
        return _p->model->getStep();
    }

    void IntEditSlider::setStep(int value)
    {
        _p->model->setStep(value);
    }

    int IntEditSlider::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void IntEditSlider::setLargeStep(int value)
    {
        _p->model->setLargeStep(value);
    }

    int IntEditSlider::getDefaultValue() const
    {
        return _p->model->getDefaultValue();
    }

    void IntEditSlider::setDefaultValue(int value)
    {
        _p->model->setDefaultValue(value);
    }

    const std::shared_ptr<IntModel>& IntEditSlider::getModel() const
    {
        return _p->model;
    }

    FontRole IntEditSlider::getFontRole() const
    {
        return _p->edit->getFontRole();
    }

    void IntEditSlider::setFontRole(FontRole value)
    {
        _p->edit->setFontRole(value);
    }

    void IntEditSlider::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void IntEditSlider::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }
}