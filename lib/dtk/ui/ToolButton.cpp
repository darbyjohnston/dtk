// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ToolButton.h>

#include <dtk/ui/Action.h>
#include <dtk/ui/DrawUtil.h>

#include <optional>

namespace dtk
{
    struct ToolButton::Private
    {
        std::shared_ptr<dtk::Action> action;
        std::shared_ptr<dtk::ValueObserver<std::string> > iconObserver;
        std::shared_ptr<dtk::ValueObserver<std::string> > checkedIconObserver;
        std::shared_ptr<dtk::ValueObserver<bool> > checkableObserver;
        std::shared_ptr<dtk::ValueObserver<bool> > checkedObserver;
        std::shared_ptr<dtk::ValueObserver<bool> > enabledObserver;
        std::shared_ptr<dtk::ValueObserver<std::string> > tooltipObserver;

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
            dtk::TriMesh2F mesh;
            dtk::TriMesh2F border;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        std::optional<DrawData> draw;
    };

    void ToolButton::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Action>& action,
        const std::shared_ptr<IWidget>& parent)
    {
        IButton::_init(context, "dtk::ToolButton", parent);
        DTK_P();

        setAcceptsKeyFocus(true);

        _buttonRole = ColorRole::None;

        p.action = action;

        if (action)
        {
            setClickedCallback(
                [this]
                {
                    _p->action->doCallback();
                });

            setCheckedCallback(
                [this](bool value)
                {
                    _p->action->doCheckedCallback(value);
                });

            p.iconObserver = dtk::ValueObserver<std::string>::create(
                action->observeIcon(),
                [this](const std::string& value)
                {
                    setIcon(value);
                });
            p.checkedIconObserver = dtk::ValueObserver<std::string>::create(
                action->observeCheckedIcon(),
                [this](const std::string& value)
                {
                    setCheckedIcon(value);
                });
            p.checkableObserver = dtk::ValueObserver<bool>::create(
                action->observeCheckable(),
                [this](bool value)
                {
                    setCheckable(value);
                });
            p.checkedObserver = dtk::ValueObserver<bool>::create(
                action->observeChecked(),
                [this](bool value)
                {
                    setChecked(value);
                });
            p.enabledObserver = dtk::ValueObserver<bool>::create(
                action->observeEnabled(),
                [this](bool value)
                {
                    setEnabled(value);
                });
            p.tooltipObserver = dtk::ValueObserver<std::string>::create(
                action->observeTooltip(),
                [this](const std::string& value)
                {
                    setTooltip(value);
                });
        }
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
        out->_init(context, nullptr, parent);
        return out;
    }

    std::shared_ptr<ToolButton> ToolButton::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolButton>(new ToolButton);
        out->_init(context, nullptr, parent);
        out->setText(text);
        return out;
    }

    std::shared_ptr<ToolButton> ToolButton::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Action>& action,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ToolButton>(new ToolButton);
        out->_init(context, action, parent);
        return out;
    }

    void ToolButton::setText(const std::string& value)
    {
        const bool changed = value != _text;
        IButton::setText(value);
        DTK_P();
        if (changed)
        {
            p.size.displayScale.reset();
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
            p.size.displayScale.reset();
            _setSizeUpdate();
            _setDrawUpdate();
        }
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

    void ToolButton::setGeometry(const Box2I& value)
    {
        const bool changed = value != getGeometry();
        IButton::setGeometry(value);
        DTK_P();
        if (changed)
        {
            p.draw.reset();
        }
    }

    void ToolButton::sizeHintEvent(const SizeHintEvent& event)
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
            p.size.fontInfo = event.style->getFontRole(_fontRole, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(_text, p.size.fontInfo);
            p.draw.reset();
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
            p.draw.reset();
        }
    }

    void ToolButton::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        DTK_P();

        if (!p.draw.has_value())
        {
            p.draw = Private::DrawData();
            p.draw->g = getGeometry();
            p.draw->g2 = margin(p.draw->g, -p.size.margin);
            if (acceptsKeyFocus())
            {
                p.draw->g2 = margin(p.draw->g2, -p.size.border);
            }
            p.draw->mesh = rect(p.draw->g);
            p.draw->border = border(p.draw->g, p.size.border);
        }

        // Draw the background.
        const ColorRole colorRole = _checked ? _checkedRole : _buttonRole;
        if (colorRole != ColorRole::None)
        {
            event.render->drawMesh(
                p.draw->mesh,
                event.style->getColorRole(colorRole));
        }

        // Draw the focus.
        if (hasKeyFocus())
        {
            event.render->drawMesh(
                p.draw->border,
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the mouse states.
        if (_isMousePressed())
        {
            event.render->drawMesh(
                p.draw->mesh,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawMesh(
                p.draw->mesh,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the icon.
        int x = p.draw->g2.x();
        auto image = _iconImage;
        if (_checked && _checkedIconImage)
        {
            image = _checkedIconImage;
        }
        if (image)
        {
            const Size2I& iconSize = image->getSize();
            if (_text.empty())
            {
                x = p.draw->g2.x() + p.draw->g2.w() / 2 - iconSize.w / 2;
            }
            event.render->drawImage(
                image,
                Box2I(
                    x,
                    p.draw->g2.y() + p.draw->g2.h() / 2 - iconSize.h / 2,
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
            if (p.draw->glyphs.empty())
            {
                p.draw->glyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw->glyphs,
                p.size.fontMetrics,
                V2I(x + p.size.pad,
                    p.draw->g2.y() + p.draw->g2.h() / 2 - p.size.textSize.h / 2),
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
