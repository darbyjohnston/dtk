// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/DoubleEdit.h>

#include <dtk/ui/IncButtons.h>
#include <dtk/ui/LineEdit.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Format.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
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
            IWidget::_init(context, "dtk::ui::DoubleEdit", parent);
            DTK_P();

            p.model = model;
            if (!p.model)
            {
                p.model = DoubleModel::create(context);
            }

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
            DTK_P();
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

        void DoubleEdit::keyReleaseEvent(KeyEvent& event)
        {
            IWidget::keyReleaseEvent(event);
            event.accept = true;
        }

        void DoubleEdit::_textUpdate()
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
}
