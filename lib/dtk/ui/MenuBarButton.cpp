// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/MenuBarPrivate.h>

#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    struct MenuBarButton::Private
    {
        bool current = false;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
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
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        DrawData draw;
    };

    void MenuBarButton::_init(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::MenuBarButton", parent);
        DTK_P();
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        setText(text);
        setButtonRole(ColorRole::None);
    }

    MenuBarButton::MenuBarButton() :
        _p(new Private)
    {}

    MenuBarButton::~MenuBarButton()
    {}

    std::shared_ptr<MenuBarButton> MenuBarButton::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MenuBarButton>(new MenuBarButton);
        out->_init(context, text, parent);
        return out;
    }

    void MenuBarButton::setCurrent(bool value)
    {
        DTK_P();
        if (p.current == value)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void MenuBarButton::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
    }

    void MenuBarButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        DTK_P();
        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (p.size.init || displayScaleChanged)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, p.size.displayScale);
            p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.draw.glyphs.clear();
        }

        Size2I sizeHint(
            p.size.textSize.w + p.size.pad * 2,
            p.size.fontMetrics.lineHeight);
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void MenuBarButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void MenuBarButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        DTK_P();

        // Draw the background.
        const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
        if (colorRole != ColorRole::None)
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(colorRole));
        }

        // Draw the current state.
        if (p.current)
        {
            event.render->drawMesh(
                border(p.draw.g, p.size.border),
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the mouse state.
        if (_isMousePressed())
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the text.
        if (!_text.empty() && p.draw.glyphs.empty())
        {
            p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw.glyphs,
            p.size.fontMetrics,
            V2I(p.draw.g2.x() + p.size.pad, p.draw.g2.y()),
            event.style->getColorRole(ColorRole::Text));
    }
}