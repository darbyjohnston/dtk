// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/ListItemsWidgetPrivate.h>

#include <dtkUI/DrawUtil.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        struct ListItemButton::Private
        {
            bool current = false;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                int border = 0;

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

        void ListItemButton::_init(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "dtk::ui::ListItemButton", parent);
            DTK_P();
            _setMouseHoverEnabled(true);
            _setMousePressEnabled(true);
            setText(text);
            setButtonRole(ColorRole::None);
        }

        ListItemButton::ListItemButton() :
            _p(new Private)
        {}

        ListItemButton::~ListItemButton()
        {}

        std::shared_ptr<ListItemButton> ListItemButton::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ListItemButton>(new ListItemButton);
            out->_init(context, text, parent);
            return out;
        }

        void ListItemButton::setCurrent(bool value)
        {
            DTK_P();
            if (p.current == value)
                return;
            p.current = value;
            _setDrawUpdate();
        }

        void ListItemButton::setGeometry(const Box2I& value)
        {
            IButton::setGeometry(value);
            DTK_P();
            p.draw.g = value;
            p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
        }

        void ListItemButton::sizeHintEvent(const SizeHintEvent& event)
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
                p.size.fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
                p.draw.glyphs.clear();
            }

            Size2I sizeHint(
                p.size.textSize.w + p.size.margin * 2,
                p.size.fontMetrics.lineHeight);
            sizeHint = margin(sizeHint, p.size.margin + p.size.border);
            _setSizeHint(sizeHint);
        }

        void ListItemButton::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IButton::clipEvent(clipRect, clipped);
            DTK_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void ListItemButton::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            DTK_P();

            // Draw the background.
            const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(colorRole));
            }

            // Draw the mouse state.
            if (_isMousePressed())
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawRect(
                    convert(p.draw.g),
                    event.style->getColorRole(ColorRole::Hover));
            }

            // Draw the current state.
            if (p.current)
            {
                event.render->drawMesh(
                    border(p.draw.g, p.size.border),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }

            // Draw the text.
            if (!_text.empty() && p.draw.glyphs.empty())
            {
                p.draw.glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.glyphs,
                p.size.fontMetrics,
                V2F(p.draw.g2.x() + p.size.margin, p.draw.g2.y()),
                event.style->getColorRole(ColorRole::Text));
        }

    }
}
