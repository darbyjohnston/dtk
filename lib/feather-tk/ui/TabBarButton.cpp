// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/TabBarPrivate.h>

#include <feather-tk/ui/DrawUtil.h>

#include <optional>

namespace feather_tk
{
    struct TabBarButton::Private
    {
        bool current = false;

        struct SizeData
        {
            std::optional<float> displayScale = 0.F;
            int margin = 0;
            int border = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            TriMesh2F border;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        std::optional<DrawData> draw;
    };

    void TabBarButton::_init(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::TabBarButton", parent);
        FEATHER_TK_P();
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        setText(text);
        setButtonRole(ColorRole::None);
        setCheckedRole(ColorRole::Button);
    }

    TabBarButton::TabBarButton() :
        _p(new Private)
    {}

    TabBarButton::~TabBarButton()
    {}

    std::shared_ptr<TabBarButton> TabBarButton::create(
        const std::shared_ptr<Context>&context,
        const std::string & text,
        const std::shared_ptr<IWidget>&parent)
    {
        auto out = std::shared_ptr<TabBarButton>(new TabBarButton);
        out->_init(context, text, parent);
        return out;
    }

    void TabBarButton::setCurrent(bool value)
    {
        FEATHER_TK_P();
        if (p.current == value)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void TabBarButton::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IButton::setGeometry(value);
        FEATHER_TK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void TabBarButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.draw.reset();
        }

        Size2I sizeHint(
            p.size.textSize.w + p.size.pad * 2,
            p.size.fontMetrics.lineHeight);
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void TabBarButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        FEATHER_TK_P();
        if (clipped)
        {
            p.draw.reset();
        }
    }

    void TabBarButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        FEATHER_TK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            p.draw->g = getGeometry();
            p.draw->g2 = margin(p.draw->g, -(p.size.margin + p.size.border));
            p.draw->border = border(p.draw->g, p.size.border);
        }

        // Draw the background.
        const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
        if (colorRole != ColorRole::None)
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(colorRole));
        }

        // Draw the current state.
        if (p.current)
        {
            event.render->drawMesh(
                p.draw->border,
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the mouse state.
        if (_isMousePressed())
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                p.draw->g,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the text.
        if (!_text.empty() && p.draw->glyphs.empty())
        {
            p.draw->glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw->glyphs,
            p.size.fontMetrics,
            V2I(p.draw->g2.x() + p.size.pad,
                p.draw->g2.y() + p.draw->g2.h() / 2 - p.size.textSize.h / 2),
            event.style->getColorRole(_checked ? ColorRole::Text : ColorRole::TextDisabled));
    }
}
