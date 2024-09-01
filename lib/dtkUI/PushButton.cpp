// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/PushButton.h>

#include <dtkUI/DrawUtil.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        struct PushButton::Private
        {
            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int margin2 = 0;
                int spacing = 0;
                int border = 0;
                int borderFocus = 0;
                FontInfo fontInfo;
                FontMetrics fontMetrics;
                Size2I textSize;
            };
            SizeData size;

            struct DrawData
            {
                Box2I g;
                Box2I g2;
                Box2I g3;
                std::vector<std::shared_ptr<Glyph> > glyphs;
            };
            DrawData draw;
        };

        void PushButton::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IButton::_init(context, "dtk::ui::PushButton", parent);
            setAcceptsKeyFocus(true);
        }

        PushButton::PushButton() :
            _p(new Private)
        {}

        PushButton::~PushButton()
        {}

        std::shared_ptr<PushButton> PushButton::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<PushButton>(new PushButton);
            out->_init(context, parent);
            return out;
        }

        std::shared_ptr<PushButton> PushButton::create(
            const std::shared_ptr<Context>& context,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = create(context, parent);
            out->setText(text);
            return out;
        }

        void PushButton::setText(const std::string& value)
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

        void PushButton::setFontRole(FontRole value)
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

        void PushButton::setGeometry(const Box2I& value)
        {
            IButton::setGeometry(value);
            DTK_P();
            p.draw.g = value;
            p.draw.g2 = margin(p.draw.g, -p.size.borderFocus);
            p.draw.g3 = margin(
                p.draw.g2,
                -p.size.margin,
                -p.size.margin2,
                -p.size.margin,
                -p.size.margin2);
        }

        void PushButton::sizeHintEvent(const SizeHintEvent& event)
        {
            IButton::sizeHintEvent(event);
            DTK_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (p.size.init || displayScaleChanged)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::Margin, p.size.displayScale);
                p.size.margin2 = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
                p.size.borderFocus = event.style->getSizeRole(SizeRole::BorderFocus, p.size.displayScale);
                p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
                p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
                p.draw.glyphs.clear();
            }

            Size2I sizeHint;
            if (!_text.empty())
            {
                sizeHint.w = p.size.textSize.w + p.size.margin2 * 2;
                sizeHint.h = p.size.fontMetrics.lineHeight;
            }
            if (_iconImage)
            {
                sizeHint.w += _iconImage->getWidth();
                if (!_text.empty())
                {
                    sizeHint.w += p.size.spacing;
                }
                sizeHint.h = std::max(sizeHint.h, _iconImage->getHeight());
            }
            sizeHint = margin(
                sizeHint,
                p.size.margin + p.size.borderFocus,
                p.size.margin2 + p.size.borderFocus);
            _setSizeHint(sizeHint);
        }

        void PushButton::clipEvent(const Box2I& clipRect, bool clipped)
        {
            IWidget::clipEvent(clipRect, clipped);
            DTK_P();
            if (clipped)
            {
                p.draw.glyphs.clear();
            }
        }

        void PushButton::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IButton::drawEvent(drawRect, event);
            DTK_P();

            // Draw the focus and border.
            const Box2I& g = getGeometry();
            if (hasKeyFocus())
            {
                event.render->drawMesh(
                    border(g, p.size.borderFocus),
                    event.style->getColorRole(ColorRole::KeyFocus));
            }
            else
            {
                event.render->drawMesh(
                    border(margin(g, p.size.border - p.size.borderFocus), p.size.border),
                    event.style->getColorRole(ColorRole::Border));
            }

            // Draw the background.
            const auto mesh = rect(p.draw.g2);
            const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
            if (colorRole != ColorRole::None)
            {
                event.render->drawMesh(
                    mesh,
                    event.style->getColorRole(colorRole));
            }

            // Draw the mouse states.
            if (_isMousePressed())
            {
                event.render->drawMesh(
                    mesh,
                    event.style->getColorRole(ColorRole::Pressed));
            }
            else if (_isMouseInside())
            {
                event.render->drawMesh(
                    mesh,
                    event.style->getColorRole(ColorRole::Hover));
            }

            // Draw the icon.
            int x = p.draw.g3.x();
            if (_iconImage)
            {
                const Size2I& iconSize = _iconImage->getSize();
                event.render->drawImage(
                  _iconImage,
                  Box2F(
                      x,
                      p.draw.g3.y() + p.draw.g3.h() / 2 - iconSize.h / 2,
                      iconSize.w,
                      iconSize.h),
                  event.style->getColorRole(isEnabled() ?
                      ColorRole::Text :
                      ColorRole::TextDisabled));
                x += iconSize.w + p.size.spacing;
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
                    V2F(
                        x + p.size.margin2,
                        p.draw.g3.y() + p.draw.g3.h() / 2 - p.size.textSize.h / 2),
                    event.style->getColorRole(isEnabled() ?
                        ColorRole::Text :
                        ColorRole::TextDisabled));
            }
        }

        void PushButton::keyPressEvent(KeyEvent& event)
        {
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

        void PushButton::keyReleaseEvent(KeyEvent& event)
        {
            IButton::keyReleaseEvent(event);
            event.accept = true;
        }
    }
}
