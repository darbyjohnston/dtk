// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/MenuPrivate.h>

#include <dtk/ui/DrawUtil.h>

#include <optional>

namespace dtk
{
    struct MenuButton::Private
    {
        bool current = false;
        Key shortcut = Key::Unknown;
        int shortcutModifiers = 0;
        std::string shortcutText;

        float iconScale = 1.F;
        std::string subMenuIcon;
        std::shared_ptr<Image> subMenuImage;

        std::shared_ptr<ValueObserver<std::string> > textObserver;
        std::shared_ptr<ValueObserver<std::string> > iconObserver;
        std::shared_ptr<ValueObserver<std::string> > checkedIconObserver;
        std::shared_ptr<ValueObserver<Key> > shortcutObserver;
        std::shared_ptr<ValueObserver<int> > shortcutModifiersObserver;
        std::shared_ptr<ValueObserver<bool> > checkableObserver;
        std::shared_ptr<ValueObserver<bool> > checkedObserver;
        std::shared_ptr<ValueObserver<bool> > enabledObserver;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int border = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
            Size2I shortcutSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            std::vector<std::shared_ptr<Glyph> > textGlyphs;
            std::vector<std::shared_ptr<Glyph> > shortcutGlyphs;
        };
        DrawData draw;
    };

    void MenuButton::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Action>& action,
        const std::shared_ptr<IWidget>& parent)
    {
        IButton::_init(context, "dtk::MenuButton", parent);
        DTK_P();

        setButtonRole(ColorRole::None);

        if (action)
        {
            p.textObserver = ValueObserver<std::string>::create(
                action->observeText(),
                [this](const std::string& value)
                {
                    setText(value);
                });
            p.iconObserver = ValueObserver<std::string>::create(
                action->observeIcon(),
                [this](const std::string& value)
                {
                    setIcon(value);
                });
            p.checkedIconObserver = ValueObserver<std::string>::create(
                action->observeCheckedIcon(),
                [this](const std::string& value)
                {
                    setCheckedIcon(value);
                });
            p.shortcutObserver = ValueObserver<Key>::create(
                action->observeShortcut(),
                [this](Key value)
                {
                    setShortcut(value, _p->shortcutModifiers);
                });
            p.shortcutModifiersObserver = ValueObserver<int>::create(
                action->observeShortcutModifiers(),
                [this](int value)
                {
                    setShortcut(_p->shortcut, value);
                });
            p.checkableObserver = ValueObserver<bool>::create(
                action->observeCheckable(),
                [this](bool value)
                {
                    setCheckable(value);
                    if ("Empty" == getIcon() && getCheckedIcon().empty())
                    {
                        setCheckedIcon("MenuChecked");
                    }
                });
            p.checkedObserver = ValueObserver<bool>::create(
                action->observeChecked(),
                [this](bool value)
                {
                    setChecked(value);
                    if ("Empty" == getIcon() && getCheckedIcon().empty())
                    {
                        setCheckedIcon("MenuChecked");
                    }
                });
            p.enabledObserver = ValueObserver<bool>::create(
                action->observeEnabled(),
                [this](bool value)
                {
                    setEnabled(value);
                });
        }
    }

    MenuButton::MenuButton() :
        _p(new Private)
    {}

    MenuButton::~MenuButton()
    {}

    std::shared_ptr<MenuButton> MenuButton::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<Action>& action,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MenuButton>(new MenuButton);
        out->_init(context, action, parent);
        return out;
    }

    void MenuButton::setCurrent(bool value)
    {
        DTK_P();
        if (value == p.current)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void MenuButton::setShortcut(Key key, int modifiers)
    {
        DTK_P();
        if (key == p.shortcut && modifiers == p.shortcutModifiers)
            return;
        p.shortcut = key;
        p.shortcutModifiers = modifiers;
        p.shortcutText = getShortcutLabel(p.shortcut, p.shortcutModifiers);
        p.size.displayScale.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void MenuButton::setSubMenuIcon(const std::string& name)
    {
        DTK_P();
        if (name == p.subMenuIcon)
            return;
        p.subMenuIcon = name;
        p.subMenuImage.reset();
    }

    void MenuButton::setText(const std::string& value)
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

    void MenuButton::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -(p.size.margin + p.size.border));
    }

    void MenuButton::sizeHintEvent(const SizeHintEvent& event)
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
            p.size.shortcutSize = event.fontSystem->getSize(p.shortcutText, p.size.fontInfo);
            p.draw.textGlyphs.clear();
            p.draw.shortcutGlyphs.clear();
        }

        if (event.displayScale != p.iconScale)
        {
            p.iconScale = event.displayScale;
            p.subMenuImage.reset();
        }
        if (!p.subMenuIcon.empty() && !p.subMenuImage)
        {
            p.subMenuImage = event.iconSystem->get(p.subMenuIcon, p.iconScale);
        }

        Size2I sizeHint;
        if (_iconImage)
        {
            sizeHint.w = _iconImage->getWidth();
            sizeHint.h = _iconImage->getHeight();
        }
        if (!_text.empty())
        {
            sizeHint.w += p.size.textSize.w + p.size.pad * 2;
            sizeHint.h = std::max(sizeHint.h, p.size.fontMetrics.lineHeight);
        }
        if (!p.shortcutText.empty())
        {
            sizeHint.w += p.size.shortcutSize.w + p.size.pad * 4;
            sizeHint.h = std::max(sizeHint.h, p.size.shortcutSize.h);
        }
        if (p.subMenuImage)
        {
            sizeHint.w += p.subMenuImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, p.subMenuImage->getHeight());
        }
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        _setSizeHint(sizeHint);
    }

    void MenuButton::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.textGlyphs.clear();
            p.draw.shortcutGlyphs.clear();
        }
    }

    void MenuButton::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
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
            const Box2I iconRect(
                x,
                p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                iconSize.w,
                iconSize.h);
            if (_checked)
            {
                event.render->drawRect(
                    iconRect,
                    event.style->getColorRole(ColorRole::Checked));
            }
            event.render->drawImage(
                image,
                iconRect,
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
            x += iconSize.w;
        }

        // Draw the text.
        if (!_text.empty())
        {
            if (p.draw.textGlyphs.empty())
            {
                p.draw.textGlyphs = event.fontSystem->getGlyphs(_text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.textGlyphs,
                p.size.fontMetrics,
                V2I(x + p.size.pad,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.textSize.h / 2),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }

        // Draw the shortcut.
        if (!p.shortcutText.empty())
        {
            if (p.draw.shortcutGlyphs.empty())
            {
                p.draw.shortcutGlyphs = event.fontSystem->getGlyphs(p.shortcutText, p.size.fontInfo);
            }
            const V2I pos(
                p.draw.g2.max.x - p.size.shortcutSize.w - p.size.pad,
                p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.shortcutSize.h / 2);
            event.render->drawText(
                p.draw.shortcutGlyphs,
                p.size.fontMetrics,
                pos,
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }

        // Draw the sub menu icon.
        if (p.subMenuImage)
        {
            const Size2I& iconSize = p.subMenuImage->getSize();
            event.render->drawImage(
                p.subMenuImage,
                Box2I(
                    p.draw.g2.max.x - iconSize.w,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }
    }
}
