// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/RadioButton.h>

#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    struct RadioButton::Private
    {
        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int margin = 0;
            int spacing = 0;
            int border = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
            int diameter = 0;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            Box2I g3;
            Box2I g4;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        DrawData draw;
    };

    void RadioButton::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IButton::_init(context, "dtk::RadioButton", parent);
        setCheckable(true);
        setAcceptsKeyFocus(true);
        _buttonRole = ColorRole::None;
    }

    RadioButton::RadioButton() :
        _p(new Private)
    {}

    RadioButton::~RadioButton()
    {}

    std::shared_ptr<RadioButton> RadioButton::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<RadioButton>(new RadioButton);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<RadioButton> RadioButton::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setText(text);
        return out;
    }

    void RadioButton::setText(const std::string& value)
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

    void RadioButton::setFontRole(FontRole value)
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

    void RadioButton::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
        p.draw.g3 = Box2I(
            p.draw.g2.x(),
            p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.diameter / 2,
            p.size.diameter,
            p.size.diameter);
    }

    void RadioButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        DTK_P();

        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (p.size.init || displayScaleChanged)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
            p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, p.size.displayScale);
            p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.size.diameter = p.size.fontMetrics.lineHeight * .8F;
            p.draw.glyphs.clear();
        }

        Size2I sizeHint;
        sizeHint.w += p.size.diameter;
        sizeHint.w += p.size.spacing;
        sizeHint.w += p.size.textSize.w + p.size.pad * 2;
        sizeHint.h = p.size.fontMetrics.lineHeight;
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void RadioButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void RadioButton::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        DTK_P();

        // Draw the focus.
        if (hasKeyFocus())
        {
            event.render->drawMesh(
                border(p.draw.g, p.size.border),
                event.style->getColorRole(ColorRole::KeyFocus));
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

        // Draw the button.
        event.render->drawMesh(
            circle(center(p.draw.g3), p.size.diameter / 2),
            event.style->getColorRole(ColorRole::Border));
        event.render->drawMesh(
            circle(center(p.draw.g3), p.size.diameter / 2 - p.size.border),
            event.style->getColorRole(_checked ? ColorRole::Checked : ColorRole::Base));

        // Draw the text.
        if (!_text.empty() && p.draw.glyphs.empty())
        {
            p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw.glyphs,
            p.size.fontMetrics,
            V2I(p.draw.g2.x() + p.size.diameter + p.size.spacing + p.size.pad,
                p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.textSize.h / 2),
            event.style->getColorRole(isEnabled() ?
                ColorRole::Text :
                ColorRole::TextDisabled));
    }

    void RadioButton::keyPressEvent(KeyEvent& event)
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

    void RadioButton::keyReleaseEvent(KeyEvent& event)
    {
        IButton::keyReleaseEvent(event);
        event.accept = true;
    }
}