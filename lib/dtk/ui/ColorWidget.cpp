// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ColorWidget.h>

#include <dtk/ui/ColorSwatch.h>
#include <dtk/ui/FloatEditSlider.h>
#include <dtk/ui/GridLayout.h>
#include <dtk/ui/Label.h>
#include <dtk/ui/RowLayout.h>

namespace dtk
{
    struct ColorWidget::Private
    {
        Color4F color;

        std::shared_ptr<ColorSwatch> swatch;
        std::map<std::string, std::shared_ptr<FloatEditSlider> > sliders;
        std::shared_ptr<HorizontalLayout> layout;

        std::function<void(const Color4F&)> callback;
    };

    void ColorWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ColorWidget", parent);
        DTK_P();

        p.swatch = ColorSwatch::create(context);
        p.swatch->setSizeRole(SizeRole::SwatchLarge);

        p.sliders["Red"] = FloatEditSlider::create(context);
        p.sliders["Green"] = FloatEditSlider::create(context);
        p.sliders["Blue"] = FloatEditSlider::create(context);
        p.sliders["Alpha"] = FloatEditSlider::create(context);

        p.layout = HorizontalLayout::create(context, shared_from_this());
        p.layout->setSpacingRole(SizeRole::SpacingSmall);
        p.swatch->setParent(p.layout);
        auto gridLayout = GridLayout::create(context, p.layout);
        gridLayout->setSpacingRole(SizeRole::SpacingTool);
        gridLayout->setHStretch(Stretch::Expanding);
        auto label = Label::create(context, "Red:", gridLayout);
        gridLayout->setGridPos(label, 0, 0);
        p.sliders["Red"]->setParent(gridLayout);
        gridLayout->setGridPos(p.sliders["Red"], 0, 1);
        label = Label::create(context, "Green:", gridLayout);
        gridLayout->setGridPos(label, 1, 0);
        p.sliders["Green"]->setParent(gridLayout);
        gridLayout->setGridPos(p.sliders["Green"], 1, 1);
        label = Label::create(context, "Blue:", gridLayout);
        gridLayout->setGridPos(label, 2, 0);
        p.sliders["Blue"]->setParent(gridLayout);
        gridLayout->setGridPos(p.sliders["Blue"], 2, 1);
        label = Label::create(context, "Alpha:", gridLayout);
        gridLayout->setGridPos(label, 3, 0);
        p.sliders["Alpha"]->setParent(gridLayout);
        gridLayout->setGridPos(p.sliders["Alpha"], 3, 1);

        _colorUpdate();

        p.sliders["Red"]->setCallback(
            [this](float value)
            {
                _p->color.r = value;
                _colorUpdate();
                if (_p->callback)
                {
                    _p->callback(_p->color);
                }
            });
        p.sliders["Green"]->setCallback(
            [this](float value)
            {
                _p->color.g = value;
                _colorUpdate();
                if (_p->callback)
                {
                    _p->callback(_p->color);
                }
            });
        p.sliders["Blue"]->setCallback(
            [this](float value)
            {
                _p->color.b = value;
                _colorUpdate();
                if (_p->callback)
                {
                    _p->callback(_p->color);
                }
            });
        p.sliders["Alpha"]->setCallback(
            [this](float value)
            {
                _p->color.a = value;
                _colorUpdate();
                if (_p->callback)
                {
                    _p->callback(_p->color);
                }
            });
    }

    ColorWidget::ColorWidget() :
        _p(new Private)
    {}

    ColorWidget::~ColorWidget()
    {}

    std::shared_ptr<ColorWidget> ColorWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ColorWidget>(new ColorWidget);
        out->_init(context, parent);
        return out;
    }

    const Color4F& ColorWidget::getColor() const
    {
        return _p->color;
    }

    void ColorWidget::setColor(const Color4F& value)
    {
        DTK_P();
        if (value == p.color)
            return;
        p.color = value;
        _colorUpdate();
        _setDrawUpdate();
    }

    void ColorWidget::setCallback(const std::function<void(const Color4F&)>& value)
    {
        _p->callback = value;
    }

    void ColorWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        _p->layout->setGeometry(value);
    }

    void ColorWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
    }

    void ColorWidget::_colorUpdate()
    {
        DTK_P();
        p.swatch->setColor(p.color);
        p.sliders["Red"]->setValue(p.color.r);
        p.sliders["Green"]->setValue(p.color.g);
        p.sliders["Blue"]->setValue(p.color.b);
        p.sliders["Alpha"]->setValue(p.color.a);
    }
}