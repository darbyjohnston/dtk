// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ToolButton.h>

#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    struct ToolButton::Private
    {
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

    void ToolButton::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IButton::_init(context, "dtk::ToolButton", parent);
        setAcceptsKeyFocus(true);
        _buttonRole = ColorRole::None;
    }

    ToolButton::ToolButton() :
        _p(new Private)
    {}

    ToolButton::~ToolButton()
    {}

    std::shared_ptr<ToolButton> ToolButton::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolButton>(new ToolButton);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<ToolButton> ToolButton::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setText(text);
        return out;
    }

    void ToolButton::setText(const std::string& value)
    {
        const bool changed = value != _text;
        IButton::setText(value);
        DTK_P();
        if (changed)
        {
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void ToolButton::setFontRole(FontRole value)
    {
        const bool changed = value != _fontRole;
        IButton::setFontRole(value);
        DTK_P();
        if (changed)
        {
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void ToolButton::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(
            p.draw.g,
            -(p.size.margin + (acceptsKeyFocus() ? p.size.border : 0)));
    }

    void ToolButton::setAcceptsKeyFocus(bool value)
    {
        const bool changed = value != acceptsKeyFocus();
        IButton::setAcceptsKeyFocus(value);
        if (changed)
        {
            _setSizeUpdate();
            _setDrawUpdate();
        }
    }

    void ToolButton::sizeHintEvent(const SizeHintEvent& event)
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
            p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.draw.glyphs.clear();
        }

        Size2I sizeHint;
        if (!_text.empty())
        {
            sizeHint.w = p.size.textSize.w + p.size.pad * 2;
            sizeHint.h = p.size.fontMetrics.lineHeight;
            if (_icon.empty())
            {
                const int max = std::max(sizeHint.w, sizeHint.h);
                sizeHint.w = max;
                sizeHint.h = sizeHint.h;
            }
        }
        if (_iconImage)
        {
            sizeHint.w += _iconImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, _iconImage->getHeight());
        }
        sizeHint = margin(sizeHint, p.size.margin);
        if (acceptsKeyFocus())
        {
            sizeHint = margin(sizeHint, p.size.border);
        }
        _setSizeHint(sizeHint);
    }

    void ToolButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void ToolButton::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
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

        // Draw the mouse states.
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

        // Draw the focus.
        if (hasKeyFocus())
        {
            event.render->drawMesh(
                border(p.draw.g, p.size.border),
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the icon.
        int x = p.draw.g2.x();
        if (_iconImage)
        {
            const Size2I& iconSize = _iconImage->getSize();
            if (_text.empty())
            {
                x = p.draw.g2.x() + p.draw.g2.w() / 2 - iconSize.w / 2;
            }
            event.render->drawImage(
                _iconImage,
                Box2I(
                    x,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
            x += iconSize.w;
        }
            
        // Draw the text.
        if (!_text.empty())
        {
            if (p.draw.glyphs.empty())
            {
                p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.glyphs,
                p.size.fontMetrics,
                V2I(x + p.size.margin + p.size.pad,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.textSize.h / 2),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }
    }

    void ToolButton::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Enter:
                event.accept = true;
                click();
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
            IButton::keyPressEvent(event);
        }
    }

    void ToolButton::keyReleaseEvent(KeyEvent& event)
    {
        IButton::keyReleaseEvent(event);
        event.accept = true;
    }
}
