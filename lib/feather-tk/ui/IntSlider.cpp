// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IntSlider.h>

#include <feather-tk/ui/DrawUtil.h>

#include <optional>

namespace feather_tk
{
    struct IntSlider::Private
    {
        std::shared_ptr<IntModel> model;
        std::function<void(int)> callback;
        std::shared_ptr<ValueObserver<int> > valueObserver;
        std::shared_ptr<ValueObserver<RangeI> > rangeObserver;

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

    void IntSlider::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IntModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::IntSlider", parent);
        FEATHER_TK_P();

        setAcceptsKeyFocus(true);
        setHStretch(Stretch::Expanding);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);

        p.model = model;

        p.valueObserver = ValueObserver<int>::create(
            p.model->observeValue(),
            [this](int value)
            {
                _setSizeUpdate();
                _setDrawUpdate();
                if (_p->callback)
                {
                    _p->callback(value);
                }
            });

        p.rangeObserver = ValueObserver<RangeI>::create(
            p.model->observeRange(),
            [this](const RangeI&)
            {
                _setSizeUpdate();
                _setDrawUpdate();
            });
    }

    IntSlider::IntSlider() :
        _p(new Private)
    {}

    IntSlider::~IntSlider()
    {}

    std::shared_ptr<IntSlider> IntSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<IntSlider>(new IntSlider);
        out->_init(context, IntModel::create(context), parent);
        return out;
    }

    std::shared_ptr<IntSlider> IntSlider::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IntModel>& model,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<IntSlider>(new IntSlider);
        out->_init(context, model, parent);
        return out;
    }

    int IntSlider::getValue() const
    {
        return _p->model->getValue();
    }

    void IntSlider::setValue(int value)
    {
        _p->model->setValue(value);
    }

    void IntSlider::setCallback(const std::function<void(int)>& value)
    {
        _p->callback = value;
    }

    const RangeI& IntSlider::getRange() const
    {
        return _p->model->getRange();
    }

    void IntSlider::setRange(const RangeI& value)
    {
        _p->model->setRange(value);
    }

    void IntSlider::setRange(int min, int max)
    {
        _p->model->setRange(RangeI(min, max));
    }

    int IntSlider::getStep() const
    {
        return _p->model->getStep();
    }

    void IntSlider::setStep(int value)
    {
        _p->model->setStep(value);
    }

    int IntSlider::getLargeStep() const
    {
        return _p->model->getLargeStep();
    }

    void IntSlider::setLargeStep(int value)
    {
        _p->model->setLargeStep(value);
    }

    int IntSlider::getDefaultValue() const
    {
        return _p->model->getDefaultValue();
    }

    void IntSlider::setDefaultValue(int value)
    {
        _p->model->setDefaultValue(value);
    }

    const std::shared_ptr<IntModel>& IntSlider::getModel() const
    {
        return _p->model;
    }

    void IntSlider::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IWidget::setGeometry(value);
        FEATHER_TK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void IntSlider::sizeHintEvent(const SizeHintEvent& event)
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

    void IntSlider::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void IntSlider::drawEvent(
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

    void IntSlider::mouseEnterEvent(MouseEnterEvent& event)
    {
        IWidget::mouseEnterEvent(event);
        _setDrawUpdate();
    }

    void IntSlider::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        _setDrawUpdate();
    }

    void IntSlider::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
        FEATHER_TK_P();
        if (_isMousePressed() && p.model)
        {
            p.model->setValue(_posToValue(_getMousePos().x));
        }
    }

    void IntSlider::mousePressEvent(MouseClickEvent& event)
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

    void IntSlider::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        _setDrawUpdate();
    }

    void IntSlider::scrollEvent(ScrollEvent& event)
    {
        FEATHER_TK_P();
        event.accept = true;
        const int step = event.modifiers & static_cast<int>(KeyModifier::Shift) ?
            p.model->getLargeStep() :
            p.model->getStep();
        p.model->setValue(p.model->getValue() + step * event.value.y);
    }

    void IntSlider::keyPressEvent(KeyEvent& event)
    {
        FEATHER_TK_P();
        if (isEnabled() && p.model)
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

    void IntSlider::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    Box2I IntSlider::_getSliderGeometry() const
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

    int IntSlider::_posToValue(int pos) const
    {
        FEATHER_TK_P();
        const Box2I g = _getSliderGeometry();
        const RangeI range = p.model ? p.model->getRange() : RangeI();
        const float inc = g.w() /
            static_cast<float>(range.max() - range.min());
        const float v = (pos + inc / 2 - g.x()) /
            static_cast<float>(g.w());
        const int out = range.min() +
            (range.max() - range.min()) * v;
        return out;
    }

    int IntSlider::_valueToPos(int value) const
    {
        FEATHER_TK_P();
        const Box2I g = _getSliderGeometry();
        const RangeI range = p.model ? p.model->getRange() : RangeI();
        float v = 0.F;
        if (range.min() != range.max())
        {
            v = (value - range.min()) /
                static_cast<float>(range.max() - range.min());
        }
        const int out = g.x() + g.w() * v;
        return out;
    }
}