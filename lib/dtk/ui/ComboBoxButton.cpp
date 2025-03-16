// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ComboBoxPrivate.h>

#include <dtk/ui/DrawUtil.h>

#include <optional>

namespace dtk
{
    struct ComboBoxButton::Private
    {
        bool current = false;

        struct SizeData
        {
            std::optional<float> displayScale;
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

    void ComboBoxButton::_init(
        const std::shared_ptr<Context>& context,
        const ComboBoxItem& item,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ComboBoxButton", parent);
        DTK_P();
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
        setText(item.text);
        setIcon(!item.icon.empty() ? item.icon : "Empty");
        if (item.icon.empty())
        {
            setCheckedIcon("MenuChecked");
        }
        setButtonRole(ColorRole::None);
    }

    ComboBoxButton::ComboBoxButton() :
        _p(new Private)
    {}

    ComboBoxButton::~ComboBoxButton()
    {}

    std::shared_ptr<ComboBoxButton> ComboBoxButton::create(
        const std::shared_ptr<Context>& context,
        const ComboBoxItem& item,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ComboBoxButton>(new ComboBoxButton);
        out->_init(context, item, parent);
        return out;
    }

    void ComboBoxButton::setCurrent(bool value)
    {
        DTK_P();
        if (p.current == value)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void ComboBoxButton::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
    }

    void ComboBoxButton::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        DTK_P();

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
            p.draw.glyphs.clear();
        }

        Size2I sizeHint;
        if (!_text.empty())
        {
            sizeHint.w = p.size.textSize.w + p.size.pad * 2;
            sizeHint.h = p.size.fontMetrics.lineHeight;
        }
        if (_iconImage)
        {
            sizeHint.w += _iconImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, _iconImage->getHeight());
        }
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void ComboBoxButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IButton::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void ComboBoxButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        DTK_P();

        // Draw the background.
        if (_buttonRole != ColorRole::None)
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(_buttonRole));
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

        // Draw the icon.
        int x = p.draw.g2.x();
        if (auto image = _checked && _checkedIconImage ? _checkedIconImage : _iconImage)
        {
            const Size2I& iconSize = _iconImage->getSize();
            const Box2I iconBox(
                x,
                p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                iconSize.w,
                iconSize.h);
            if (_checked)
            {
                event.render->drawRect(
                    iconBox,
                    event.style->getColorRole(ColorRole::Checked));
            }
            event.render->drawImage(
                image,
                iconBox,
                event.style->getColorRole(ColorRole::Text));
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
                V2I(x + p.size.pad,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.textSize.h / 2),
                event.style->getColorRole(ColorRole::Text));
        }
    }
}