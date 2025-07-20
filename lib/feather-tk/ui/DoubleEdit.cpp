// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/DoubleEdit.h>

#include <feather-tk/ui/IncButtons.h>
#include <feather-tk/ui/LineEdit.h>
#include <feather-tk/ui/RowLayout.h>
#include <feather-tk/ui/ToolButton.h>

#include <feather-tk/core/Format.h>

namespace feather_tk
{
    struct DoubleEdit::Private
    {
        std::shared_ptr<DoubleModel> model;
        int digits = 3;
        int precision = 2;

        std::shared_ptr<LineEdit> lineEdit;
        std::shared_ptr<IncButtons> incButtons;
        std::shared_ptr<HorizontalLayout> layout;

        std::function<void(double)> callback;
        std::shared_ptr<ValueObserver<double> > valueObserver;
        std::shared_ptr<ValueObserver<RangeD> > rangeObserver;
    };

    void DoubleEdit::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::DoubleEdit", parent);
        FEATHER_TK_P();

        p.model = model;

        p.lineEdit = LineEdit::create(context);
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

        p.valueObserver = ValueObserver<double>::create(
            p.model->observeValue(),
            [this](double value)
            {
                _textUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.rangeObserver = ValueObserver<RangeD>::create(
            p.model->observeRange(),
            [this](const RangeD& value)
            {
                _p->digits = digits(value.max());
                _setSizeUpdate();
                _textUpdate();
            });

        _textUpdate();
    }

    DoubleEdit::DoubleEdit() :
        _p(new Private)
    {}

    DoubleEdit::~DoubleEdit()
    {}

    std::shared_ptr<DoubleEdit> DoubleEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<DoubleEdit>(new DoubleEdit);
        out->_init(context, DoubleModel::create(context), parent);
        return out;
    }

    std::shared_ptr<DoubleEdit> DoubleEdit::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<DoubleEdit>(new DoubleEdit);
        out->_init(context, model, parent);
        return out;
    }

    double DoubleEdit::getValue() const
    {
        return _p->model->getValue();
    }

    void DoubleEdit::setValue(double value)
    {
        _p->model->setValue(value);
    }

    void DoubleEdit::setCallback(const std::function<void(double)>& value)
    {
        _p->callback = value;
    }

    const RangeD& DoubleEdit::getRange() const
    {
        return _p->model->getRange();
    }

    void DoubleEdit::setRange(const RangeD& value)
    {
        _p->model->setRange(value);
    }

    void DoubleEdit::setRange(double min, double max)
    {
        _p->model->setRange(RangeD(min, max));
    }

    double DoubleEdit::getStep() const
    {
        return _p->model->getStep();
    }

    void DoubleEdit::setStep(double value)
    {
        _p->model->setStep(value);
    }

    double DoubleEdit::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void DoubleEdit::setLargeStep(double value)
    {
        _p->model->setLargeStep(value);
    }

    const std::shared_ptr<DoubleModel>& DoubleEdit::getModel() const
    {
        return _p->model;
    }

    int DoubleEdit::getPrecision() const
    {
        return _p->precision;
    }

    void DoubleEdit::setPrecision(int value)
    {
        FEATHER_TK_P();
        if (value == p.precision)
            return;
        p.precision = value;
        _textUpdate();
    }

    FontRole DoubleEdit::getFontRole() const
    {
        return _p->lineEdit->getFontRole();
    }

    void DoubleEdit::setFontRole(FontRole value)
    {
        _p->lineEdit->setFontRole(value);
    }

    void DoubleEdit::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void DoubleEdit::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void DoubleEdit::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
        if (isEnabled() &&
            p.lineEdit->hasKeyFocus() &&
            p.model &&
            0 == event.modifiers)
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

    void DoubleEdit::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    void DoubleEdit::_textUpdate()
    {
        FEATHER_TK_P();
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

    struct DoubleResetButton::Private
    {
        std::shared_ptr<DoubleModel> model;

        std::shared_ptr<ToolButton> resetButton;

        std::shared_ptr<ValueObserver<double> > valueObserver;
        std::shared_ptr<ValueObserver<bool> > hasDefaultObserver;
        std::shared_ptr<ValueObserver<double> > defaultValueObserver;
    };

    void DoubleResetButton::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::DoubleResetButton", parent);
        FEATHER_TK_P();

        p.model = model;

        p.resetButton = ToolButton::create(context, shared_from_this());
        p.resetButton->setIcon("Reset");
        p.resetButton->setTooltip("Reset to the default value");

        p.resetButton->setClickedCallback(
            [this]
            {
                _p->model->setDefaultValue();
            });

        p.valueObserver = ValueObserver<double>::create(
            p.model->observeValue(),
            [this](double)
            {
                _widgetUpdate();
            });

        p.hasDefaultObserver = ValueObserver<bool>::create(
            p.model->observeHasDefaultValue(),
            [this](bool)
            {
                _widgetUpdate();
            });

        p.defaultValueObserver = ValueObserver<double>::create(
            p.model->observeDefaultValue(),
            [this](double)
            {
                _widgetUpdate();
            });
    }

    DoubleResetButton::DoubleResetButton() :
        _p(new Private)
    {}

    DoubleResetButton::~DoubleResetButton()
    {}

    std::shared_ptr<DoubleResetButton> DoubleResetButton::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<DoubleResetButton>(new DoubleResetButton);
        out->_init(context, model, parent);
        return out;
    }

    void DoubleResetButton::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->resetButton->setGeometry(value);
    }

    void DoubleResetButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->resetButton->getSizeHint());
    }

    void DoubleResetButton::_widgetUpdate()
    {
        FEATHER_TK_P();
        setVisible(p.model->hasDefaultValue());
        setEnabled(p.model->getValue() != p.model->getDefaultValue());
    }
}