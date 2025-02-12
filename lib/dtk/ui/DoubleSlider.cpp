// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/DoubleSlider.h>

#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    struct DoubleSlider::Private
    {
        std::shared_ptr<DoubleModel> model;
        std::function<void(double)> callback;
        std::shared_ptr<ValueObserver<double> > valueObserver;
        std::shared_ptr<ValueObserver<RangeD> > rangeObserver;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int size = 0;
            int margin = 0;
            int border = 0;
            int handle = 0;
            FontMetrics fontMetrics;
        };
        SizeData size;

        struct DrawData
        {
            TriMesh2F border;
            Box2I background;
            Box2I margin;
            Box2I handle;
        };
        DrawData draw;
    };

    void DoubleSlider::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::DoubleSlider", parent);
        DTK_P();

        setAcceptsKeyFocus(true);
        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.model = model;

        p.valueObserver = ValueObserver<double>::create(
            p.model->observeValue(),
            [this](double value)
            {
                _setSizeUpdate();
                _setDrawUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.rangeObserver = ValueObserver<RangeD>::create(
            p.model->observeRange(),
            [this](const RangeD&)
            {
                _setSizeUpdate();
                _setDrawUpdate();
            });
    }

    DoubleSlider::DoubleSlider() :
        _p(new Private)
    {}

    DoubleSlider::~DoubleSlider()
    {}

    std::shared_ptr<DoubleSlider> DoubleSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<DoubleSlider>(new DoubleSlider);
        out->_init(context, DoubleModel::create(context), parent);
        return out;
    }

    std::shared_ptr<DoubleSlider> DoubleSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<DoubleModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<DoubleSlider>(new DoubleSlider);
        out->_init(context, model, parent);
        return out;
    }

    double DoubleSlider::getValue() const
    {
        return _p->model->getValue();
    }

    void DoubleSlider::setValue(double value)
    {
        _p->model->setValue(value);
    }

    void DoubleSlider::setCallback(const std::function<void(double)>& value)
    {
        _p->callback = value;
    }

    const RangeD& DoubleSlider::getRange() const
    {
        return _p->model->getRange();
    }

    void DoubleSlider::setRange(const RangeD& value)
    {
        _p->model->setRange(value);
    }

    double DoubleSlider::getStep() const
    {
        return _p->model->getStep();
    }

    void DoubleSlider::setStep(double value)
    {
        _p->model->setStep(value);
    }

    double DoubleSlider::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void DoubleSlider::setLargeStep(double value)
    {
        _p->model->setLargeStep(value);
    }

    const std::shared_ptr<DoubleModel>& DoubleSlider::getModel() const
    {
        return _p->model;
    }

    void DoubleSlider::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.draw.border = border(value, p.size.border);
        p.draw.background = margin(value, -p.size.border);
        p.draw.margin = margin(p.draw.background, -p.size.margin);
        const Box2I g = _getSliderGeometry();
        int pos = 0;
        if (p.model)
        {
            pos = _valueToPos(p.model->getValue());
        }
        p.draw.handle = Box2I(
            pos - p.size.handle / 2,
            g.y(),
            p.size.handle,
            g.h());
    }

    void DoubleSlider::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();
        if (p.size.init || event.displayScale != p.size.displayScale)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.size = event.style->getSizeRole(SizeRole::Slider, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
            p.size.handle = event.style->getSizeRole(SizeRole::Handle, p.size.displayScale);
            auto fontInfo = event.style->getFontRole(FontRole::Label, p.size.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(fontInfo);
        }
        Size2I sizeHint(p.size.size, p.size.fontMetrics.lineHeight);
        sizeHint = margin(sizeHint, p.size.border * 2);
        _setSizeHint(sizeHint);
    }

    void DoubleSlider::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();

        // Draw the background.
        event.render->drawRect(
            p.draw.background,
            event.style->getColorRole(ColorRole::Base));

        // Draw the handle.
        event.render->drawRect(
            p.draw.handle,
            event.style->getColorRole(ColorRole::Button));
        if (_isMousePressed())
        {
            event.render->drawRect(
                p.draw.handle,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                p.draw.handle,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the focus and border.
        const Box2I& g = getGeometry();
        event.render->drawMesh(
            p.draw.border,
            event.style->getColorRole(hasKeyFocus() ? ColorRole::KeyFocus : ColorRole::Border));
    }

    void DoubleSlider::mouseEnterEvent(MouseEnterEvent& event)
    {
        IWidget::mouseEnterEvent(event);
        _setDrawUpdate();
    }

    void DoubleSlider::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        _setDrawUpdate();
    }

    void DoubleSlider::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        DTK_P();
        if (_isMousePressed() && p.model)
        {
            p.model->setValue(_posToValue(_getMousePos().x));
        }
    }

    void DoubleSlider::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        DTK_P();
        if (p.model)
        {
            p.model->setValue(_posToValue(_getMousePos().x));
        }
        takeKeyFocus();
        _setDrawUpdate();
    }

    void DoubleSlider::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        _setDrawUpdate();
    }

    void DoubleSlider::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (isEnabled() && p.model && 0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Left:
            case Key::Down:
                event.accept = true;
                p.model->decrementStep();
                break;
            case Key::Right:
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
            case Key::Home:
                event.accept = true;
                p.model->setValue(p.model->getRange().min());
                break;
            case Key::End:
                event.accept = true;
                p.model->setValue(p.model->getRange().max());
                break;
            case Key::Escape:
                if (hasKeyFocus())
                {
                    event.accept = true;
                    releaseKeyFocus();
                }
                break;
            default: break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void DoubleSlider::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    Box2I DoubleSlider::_getSliderGeometry() const
    {
        DTK_P();
        return margin(
            p.draw.margin,
            -(p.size.handle / 2),
            0,
            -(p.size.handle / 2),
            0);
    }

    double DoubleSlider::_posToValue(int pos) const
    {
        DTK_P();
        const Box2I g = _getSliderGeometry();
        const double v = (pos - g.x()) / static_cast<double>(g.w());
        double out = 0.0;
        if (p.model)
        {
            const RangeD& range = p.model->getRange();
            out = range.min() + (range.max() - range.min()) * v;
        }
        return out;
    }

    int DoubleSlider::_valueToPos(double value) const
    {
        DTK_P();
        const Box2I g = _getSliderGeometry();
        double v = 0.0;
        if (p.model)
        {
            const RangeD& range = p.model->getRange();
            if (range.min() != range.max())
            {
                v = (value - range.min()) /
                    static_cast<double>(range.max() - range.min());
            }
        }
        return g.x() + g.w() * v;
    }
}