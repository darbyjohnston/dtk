// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/FloatSlider.h>

#include <feather-tk/ui/DrawUtil.h>

#include <optional>

namespace feather_tk
{
    struct FloatSlider::Private
    {
        std::shared_ptr<FloatModel> model;
        std::function<void(float)> callback;
        std::shared_ptr<ValueObserver<float> > valueObserver;
        std::shared_ptr<ValueObserver<RangeF> > rangeObserver;

        struct SizeData
        {
            std::optional<float> displayScale;
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
        };
        std::optional<DrawData> draw;
    };

    void FloatSlider::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<FloatModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::FloatSlider", parent);
        FEATHER_TK_P();

        setAcceptsKeyFocus(true);
        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.model = model;

        p.valueObserver = ValueObserver<float>::create(
            p.model->observeValue(),
            [this](float value)
            {
                _setSizeUpdate();
                _setDrawUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.rangeObserver = ValueObserver<RangeF>::create(
            p.model->observeRange(),
            [this](const RangeF&)
            {
                _setSizeUpdate();
                _setDrawUpdate();
            });
    }

    FloatSlider::FloatSlider() :
        _p(new Private)
    {}

    FloatSlider::~FloatSlider()
    {}

    std::shared_ptr<FloatSlider> FloatSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FloatSlider>(new FloatSlider);
        out->_init(context, FloatModel::create(context), parent);
        return out;
    }

    std::shared_ptr<FloatSlider> FloatSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<FloatModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FloatSlider>(new FloatSlider);
        out->_init(context, model, parent);
        return out;
    }

    float FloatSlider::getValue() const
    {
        return _p->model->getValue();
    }

    void FloatSlider::setValue(float value)
    {
        _p->model->setValue(value);
    }

    void FloatSlider::setCallback(const std::function<void(float)>& value)
    {
        _p->callback = value;
    }

    const RangeF& FloatSlider::getRange() const
    {
        return _p->model->getRange();
    }

    void FloatSlider::setRange(const RangeF& value)
    {
        _p->model->setRange(value);
    }

    void FloatSlider::setRange(float min, float max)
    {
        _p->model->setRange(RangeF(min, max));
    }

    float FloatSlider::getStep() const
    {
        return _p->model->getStep();
    }

    void FloatSlider::setStep(float value)
    {
        _p->model->setStep(value);
    }

    float FloatSlider::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void FloatSlider::setLargeStep(float value)
    {
        _p->model->setLargeStep(value);
    }

    float FloatSlider::getDefaultValue() const
    {
        return _p->model->getDefaultValue();
    }

    void FloatSlider::setDefaultValue(float value)
    {
        _p->model->setDefaultValue(value);
    }

    const std::shared_ptr<FloatModel>& FloatSlider::getModel() const
    {
        return _p->model;
    }

    void FloatSlider::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IWidget::setGeometry(value);
        FEATHER_TK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void FloatSlider::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.size = event.style->getSizeRole(SizeRole::Slider, event.displayScale);
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.handle = event.style->getSizeRole(SizeRole::Handle, event.displayScale);
            auto fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(fontInfo);
            p.draw.reset();
        }

        Size2I sizeHint(p.size.size, p.size.fontMetrics.lineHeight);
        sizeHint = margin(sizeHint, p.size.border * 2);
        _setSizeHint(sizeHint);
    }

    void FloatSlider::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void FloatSlider::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            const Box2I& g = getGeometry();
            p.draw->border = border(g, p.size.border);
            p.draw->background = margin(g, -p.size.border);
            p.draw->margin = margin(p.draw->background, -p.size.margin);
        }

        // Draw the background.
        event.render->drawRect(
            p.draw->background,
            event.style->getColorRole(ColorRole::Base));

        // Draw the handle.
        const Box2I g = _getSliderGeometry();
        int pos = 0;
        if (p.model)
        {
            pos = _valueToPos(p.model->getValue());
        }
        const Box2I handle(
            pos - p.size.handle / 2,
            g.y(),
            p.size.handle,
            g.h());
        event.render->drawRect(
            handle,
            event.style->getColorRole(ColorRole::Button));
        if (_isMousePressed())
        {
            event.render->drawRect(
                handle,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                handle,
                event.style->getColorRole(ColorRole::Hover));
        }
        event.render->drawMesh(
            border(handle, p.size.border),
            event.style->getColorRole(ColorRole::Border));

        // Draw the focus and border.
        event.render->drawMesh(
            p.draw->border,
            event.style->getColorRole(hasKeyFocus() ? ColorRole::KeyFocus : ColorRole::Border));
    }

    void FloatSlider::mouseEnterEvent(MouseEnterEvent& event)
    {
        IWidget::mouseEnterEvent(event);
        _setDrawUpdate();
    }

    void FloatSlider::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        _setDrawUpdate();
    }

    void FloatSlider::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FEATHER_TK_P();
        if (_isMousePressed() && p.model)
        {
            p.model->setValue(_posToValue(_getMousePos().x));
        }
    }

    void FloatSlider::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        FEATHER_TK_P();
        if (p.model)
        {
            p.model->setValue(_posToValue(_getMousePos().x));
        }
        takeKeyFocus();
        _setDrawUpdate();
    }

    void FloatSlider::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        _setDrawUpdate();
    }

    void FloatSlider::scrollEvent(ScrollEvent& event)
    {
        FEATHER_TK_P();
        event.accept = true;
        const float step = event.modifiers & static_cast<int>(KeyModifier::Shift) ?
            p.model->getLargeStep() :
            p.model->getStep();
        p.model->setValue(p.model->getValue() + step * event.value.y);
    }

    void FloatSlider::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
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

    void FloatSlider::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    Box2I FloatSlider::_getSliderGeometry() const
    {
        FEATHER_TK_P();
        Box2I out;
        if (p.draw.has_value())
        {
            out = margin(
                p.draw->margin,
                -(p.size.handle / 2),
                0,
                -(p.size.handle / 2),
                0);
        }
        return out;
    }

    float FloatSlider::_posToValue(int pos) const
    {
        FEATHER_TK_P();
        const Box2I g = _getSliderGeometry();
        const float v = (pos - g.x()) / static_cast<float>(g.w());
        float out = 0.F;
        if (p.model)
        {
            const RangeF& range = p.model->getRange();
            out = range.min() + (range.max() - range.min()) * v;
        }
        return out;
    }

    int FloatSlider::_valueToPos(float value) const
    {
        FEATHER_TK_P();
        const Box2I g = _getSliderGeometry();
        float v = 0.F;
        if (p.model)
        {
            const RangeF& range = p.model->getRange();
            if (range.min() != range.max())
            {
                v = (value - range.min()) /
                    static_cast<float>(range.max() - range.min());
            }
        }
        return g.x() + g.w() * v;
    }
}