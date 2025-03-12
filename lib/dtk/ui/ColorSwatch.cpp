// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ColorSwatch.h>

#include <dtk/ui/ColorPopup.h>
#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    struct ColorSwatch::Private
    {
        Color4F color;
        bool editable = false;
        std::function<void(const Color4F&)> callback;
        SizeRole sizeRole = SizeRole::Swatch;
        std::shared_ptr<ColorPopup> popup;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int size = 0;
            int border = 0;
        };
        SizeData size;

        struct DrawData
        {
            TriMesh2F border;
            Box2I g2;
        };
        DrawData draw;
    };

    void ColorSwatch::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ColorSwatch", parent);
    }

    ColorSwatch::ColorSwatch() :
        _p(new Private)
    {}

    ColorSwatch::~ColorSwatch()
    {}

    std::shared_ptr<ColorSwatch> ColorSwatch::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ColorSwatch>(new ColorSwatch);
        out->_init(context, parent);
        return out;
    }

    const Color4F& ColorSwatch::getColor() const
    {
        return _p->color;
    }

    void ColorSwatch::setColor(const Color4F& value)
    {
        DTK_P();
        if (value == p.color)
            return;
        p.color = value;
        _setDrawUpdate();
    }

    bool ColorSwatch::isEditable() const
    {
        return _p->editable;
    }

    void ColorSwatch::setEditable(bool value)
    {
        DTK_P();
        if (value == p.editable)
            return;
        p.editable = value;
        _setMouseHoverEnabled(p.editable);
        _setMousePressEnabled(p.editable);
    }

    void ColorSwatch::setCallback(const std::function<void(const Color4F&)>& value)
    {
        _p->callback = value;
    }

    SizeRole ColorSwatch::getSizeRole() const
    {
        return _p->sizeRole;
    }

    void ColorSwatch::setSizeRole(SizeRole value)
    {
        DTK_P();
        if (value == p.sizeRole)
            return;
        p.sizeRole = value;
        p.size.init = true;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ColorSwatch::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.draw.border = border(value, p.size.border);
        p.draw.g2 = margin(value, -p.size.border);
    }

    void ColorSwatch::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();
        if (p.size.init || event.displayScale != p.size.displayScale)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.size = event.style->getSizeRole(p.sizeRole, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
        }
        _setSizeHint(Size2I(p.size.size, p.size.size));
    }

    void ColorSwatch::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        event.render->drawMesh(
            p.draw.border,
            event.style->getColorRole(ColorRole::Border));
        event.render->drawRect(p.draw.g2, Color4F(0.F, 0.F, 0.F));
        event.render->drawRect(p.draw.g2, p.color);
    }

    void ColorSwatch::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        DTK_P();
        if (p.editable)
        {
            _showPopup();
        }
    }

    void ColorSwatch::_showPopup()
    {
        DTK_P();
        if (auto context = getContext())
        {
            if (!p.popup)
            {
                p.popup = ColorPopup::create(context, p.color);
                p.popup->open(getWindow(), getGeometry());
                p.popup->setCallback(
                    [this](const Color4F& value)
                    {
                        _p->color = value;
                        _setDrawUpdate();
                        if (_p->callback)
                        {
                            _p->callback(value);
                        }
                    });
                p.popup->setCloseCallback(
                    [this]
                    {
                        _p->popup.reset();
                    });
            }
            else
            {
                p.popup->close();
                p.popup.reset();
            }
        }
    }
}