// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/FloatEdit.h>

#include <dtk/ui/IncButtons.h>
#include <dtk/ui/LineEdit.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Format.h>

namespace dtk
{
    struct FloatEdit::Private
    {
        std::shared_ptr<FloatModel> model;
        int digits = 3;
        int precision = 2;
        std::shared_ptr<LineEdit> lineEdit;
        std::shared_ptr<IncButtons> incButtons;
        std::shared_ptr<HorizontalLayout> layout;
        std::function<void(float)> callback;
        std::shared_ptr<ValueObserver<float> > valueObserver;
        std::shared_ptr<ValueObserver<RangeF> > rangeObserver;
    };

    void FloatEdit::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<FloatModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::FloatEdit", parent);
        DTK_P();

        p.model = model;

        p.lineEdit = LineEdit::create(context, shared_from_this());
        p.lineEdit->setFontRole(FontRole::Mono);

        p.incButtons = IncButtons::create(context);

        p.layout = HorizontalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::SpacingTool);
        p.lineEdit->setParent(p.layout);
        p.incButtons->setParent(p.layout);

        p.lineEdit->setTextCallback(
            [this](const std::string& value)
            {
                _p->model->setValue(std::atof(value.c_str()));
                _textUpdate();
            });
        p.lineEdit->setFocusCallback(
            [this](bool value)
            {
                if (!value)
                {
                    _textUpdate();
                }
            });

        p.incButtons->setIncCallback(
            [this]
            {
                _p->model->incrementStep();
            });
        p.incButtons->setDecCallback(
            [this]
            {
                _p->model->decrementStep();
            });

        p.valueObserver = ValueObserver<float>::create(
            p.model->observeValue(),
            [this](float value)
            {
                _textUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.rangeObserver = ValueObserver<RangeF>::create(
            p.model->observeRange(),
            [this](const RangeF& value)
            {
                _p->digits = digits(value.max());
                _setSizeUpdate();
                _textUpdate();
            });

        _textUpdate();
    }

    FloatEdit::FloatEdit() :
        _p(new Private)
    {}

    FloatEdit::~FloatEdit()
    {}

    std::shared_ptr<FloatEdit> FloatEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FloatEdit>(new FloatEdit);
        out->_init(context, FloatModel::create(context), parent);
        return out;
    }

    std::shared_ptr<FloatEdit> FloatEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<FloatModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FloatEdit>(new FloatEdit);
        out->_init(context, model, parent);
        return out;
    }

    float FloatEdit::getValue() const
    {
        return _p->model->getValue();
    }

    void FloatEdit::setValue(float value)
    {
        _p->model->setValue(value);
    }

    void FloatEdit::setCallback(const std::function<void(float)>& value)
    {
        _p->callback = value;
    }

    const RangeF& FloatEdit::getRange() const
    {
        return _p->model->getRange();
    }

    void FloatEdit::setRange(const RangeF& value)
    {
        _p->model->setRange(value);
    }

    float FloatEdit::getStep() const
    {
        return _p->model->getStep();
    }

    void FloatEdit::setStep(float value)
    {
        _p->model->setStep(value);
    }

    float FloatEdit::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void FloatEdit::setLargeStep(float value)
    {
        _p->model->setLargeStep(value);
    }

    const std::shared_ptr<FloatModel>& FloatEdit::getModel() const
    {
        return _p->model;
    }

    int FloatEdit::getPrecision() const
    {
        return _p->precision;
    }

    void FloatEdit::setPrecision(int value)
    {
        DTK_P();
        if (value == p.precision)
            return;
        p.precision = value;
        _textUpdate();
    }

    FontRole FloatEdit::getFontRole() const
    {
        return _p->lineEdit->getFontRole();
    }

    void FloatEdit::setFontRole(FontRole value)
    {
        _p->lineEdit->setFontRole(value);
    }

    void FloatEdit::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void FloatEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void FloatEdit::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (isEnabled() && p.model && 0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Down:
                event.accept = true;
                p.model->decrementStep();
                break;
            case Key::Up:
                event.accept = true;
                p.model->incrementStep();
                break;
            case Key::PageUp:
                event.accept = true;
                p.model->incrementLargeStep();
                break;
            case Key::PageDown:
                event.accept = true;
                p.model->decrementLargeStep();
                break;
            default: break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void FloatEdit::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    void FloatEdit::_textUpdate()
    {
        DTK_P();
        std::string text;
        std::string format;
        if (p.model)
        {
            text = Format("{0}").arg(p.model->getValue(), p.precision);
            int width = p.digits + 1 + p.precision;
            if (p.model->getRange().min() < 0 ||
                p.model->getRange().max() < 0)
            {
                ++width;
            }
            format = Format("{0}").arg(0, width);
        }
        p.lineEdit->setText(text);
        p.lineEdit->setFormat(format);
    }
}