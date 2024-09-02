// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/ComboBoxPrivate.h>

#include <dtk/ui/DrawUtil.h>

namespace dtk
{
    ComboBoxItem::ComboBoxItem(
        const std::string& text,
        const std::string& icon) :
        text(text),
        icon(icon)
    {}

    bool ComboBoxItem::operator == (const ComboBoxItem& other) const
    {
        return text == other.text && icon == other.icon;
    }

    bool ComboBoxItem::operator != (const ComboBoxItem& other) const
    {
        return !(*this == other);
    }

    struct ComboBox::Private
    {
        std::vector<ComboBoxItem> items;
        int currentIndex = -1;
        std::function<void(int)> indexCallback;
        std::function<void(const ComboBoxItem&)> itemCallback;
        FontRole fontRole = FontRole::Label;
        std::string text;
        std::string icon;
        std::shared_ptr<ComboBoxMenu> menu;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int margin = 0;
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
            float iconScale = 1.F;
            std::shared_ptr<Image> iconImage;
            std::shared_ptr<Image> arrowIconImage;
        };
        DrawData draw;
    };

    void ComboBox::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ComboBox", parent);
        setAcceptsKeyFocus(true);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
    }

    ComboBox::ComboBox() :
        _p(new Private)
    {}

    ComboBox::~ComboBox()
    {}

    std::shared_ptr<ComboBox> ComboBox::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ComboBox>(new ComboBox);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<ComboBox> ComboBox::create(
        const std::shared_ptr<Context>& context,
        const std::vector<ComboBoxItem>& items,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setItems(items);
        return out;
    }

    std::shared_ptr<ComboBox> ComboBox::create(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& items,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setItems(items);
        return out;
    }

    const std::vector<ComboBoxItem>& ComboBox::getItems() const
    {
        return _p->items;
    }

    void ComboBox::setItems(const std::vector<ComboBoxItem>& value)
    {
        DTK_P();
        if (value == p.items)
            return;
        p.items = value;
        p.currentIndex = clamp(p.currentIndex, 0, static_cast<int>(p.items.size()) - 1);
        const ComboBoxItem item = _getItem(p.currentIndex);
        p.text = item.text;
        p.icon = item.icon;
        p.size.init = true;
        p.draw.iconImage.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ComboBox::setItems(const std::vector<std::string>& value)
    {
        DTK_P();
        std::vector<ComboBoxItem> items;
        for (const auto& s : value)
        {
            items.push_back(ComboBoxItem(s));
        }
        setItems(items);
    }

    int ComboBox::getCurrentIndex() const
    {
        return _p->currentIndex;
    }

    void ComboBox::setCurrentIndex(int value)
    {
        DTK_P();
        const int tmp = clamp(value, 0, static_cast<int>(p.items.size()) - 1);
        if (tmp == p.currentIndex)
            return;
        p.currentIndex = tmp;
        const ComboBoxItem item = _getItem(p.currentIndex);
        p.text = item.text;
        p.icon = item.icon;
        p.size.init = true;
        p.draw.iconImage.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ComboBox::setIndexCallback(const std::function<void(int)>& value)
    {
        _p->indexCallback = value;
    }

    void ComboBox::setItemCallback(const std::function<void(const ComboBoxItem&)>& value)
    {
        _p->itemCallback = value;
    }

    FontRole ComboBox::getFontRole() const
    {
        return _p->fontRole;
    }

    void ComboBox::setFontRole(FontRole value)
    {
        DTK_P();
        if (value == p.fontRole)
            return;
        p.fontRole = value;
        p.size.init = true;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ComboBox::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -p.size.borderFocus);
        p.draw.g3 = margin(p.draw.g2, -p.size.margin);
    }

    void ComboBox::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (p.size.init || displayScaleChanged)
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
            p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            p.size.borderFocus = event.style->getSizeRole(SizeRole::BorderFocus, p.size.displayScale);
            p.size.fontInfo = event.style->getFontRole(p.fontRole, p.size.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = Size2I();
            for (const auto& i : p.items)
            {
                if (!i.text.empty())
                {
                    const Size2I textSize = event.fontSystem->getSize(i.text, p.size.fontInfo);
                    p.size.textSize.w = std::max(p.size.textSize.w, textSize.w);
                    p.size.textSize.h = std::max(p.size.textSize.h, textSize.h);
                }
            }
            p.draw.glyphs.clear();
        }

        if (event.displayScale != p.draw.iconScale)
        {
            p.draw.iconScale = event.displayScale;
            p.draw.iconImage.reset();
            p.draw.arrowIconImage.reset();
        }
        if (!p.icon.empty() && !p.draw.iconImage)
        {
            p.draw.iconImage = event.iconLibrary->request(p.icon, event.displayScale).get();
        }
        if (!p.draw.arrowIconImage)
        {
            p.draw.arrowIconImage = event.iconLibrary->request("MenuArrow", event.displayScale).get();
        }

        Size2I sizeHint;
        sizeHint.w = p.size.textSize.w + p.size.margin * 2;
        sizeHint.h = p.size.fontMetrics.lineHeight;
        if (p.draw.iconImage)
        {
            if (!p.text.empty())
            {
                sizeHint.w += p.size.spacing;
            }
            sizeHint.w += p.draw.iconImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, p.draw.iconImage->getHeight());
        }
        if (p.draw.arrowIconImage)
        {
            sizeHint.w += p.size.spacing;
            sizeHint.w += p.draw.arrowIconImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, p.draw.arrowIconImage->getHeight());
        }
        sizeHint = margin(sizeHint, p.size.margin + p.size.borderFocus);
        _setSizeHint(sizeHint);
    }

    void ComboBox::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
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
        event.render->drawRect(
            convert(p.draw.g2),
            event.style->getColorRole(ColorRole::Button));

        // Draw the mouse states.
        if (_isMousePressed())
        {
            event.render->drawRect(
                convert(p.draw.g2),
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                convert(p.draw.g2),
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the icon.
        int x = p.draw.g3.x();
        if (p.draw.iconImage)
        {
            const Size2I& iconSize = p.draw.iconImage->getSize();
            event.render->drawImage(
                p.draw.iconImage,
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
        if (!p.text.empty())
        {
            if (p.draw.glyphs.empty())
            {
                p.draw.glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
            }
            event.render->drawText(
                p.draw.glyphs,
                p.size.fontMetrics,
                V2F(
                    x + p.size.margin,
                    p.draw.g3.y() + p.draw.g3.h() / 2 - p.size.textSize.h / 2),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }

        // Draw the arrow icon.
        if (p.draw.arrowIconImage)
        {
            const Size2I& iconSize = p.draw.arrowIconImage->getSize();
            event.render->drawImage(
                p.draw.arrowIconImage,
                Box2F(
                    p.draw.g3.x() + p.draw.g3.w() - iconSize.w,
                    p.draw.g3.y() + p.draw.g3.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
        }
    }

    void ComboBox::mouseEnterEvent()
    {
        IWidget::mouseEnterEvent();
        _setDrawUpdate();
    }

    void ComboBox::mouseLeaveEvent()
    {
        IWidget::mouseLeaveEvent();
        _setDrawUpdate();
    }

    void ComboBox::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
        DTK_P();
        _click();
        _setDrawUpdate();
    }

    void ComboBox::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
        _setDrawUpdate();
    }

    void ComboBox::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::Up:
                event.accept = true;
                _commit(p.currentIndex - 1);
                break;
            case Key::Down:
                event.accept = true;
                _commit(p.currentIndex + 1);
                break;
            case Key::Home:
                event.accept = true;
                _commit(0);
                break;
            case Key::End:
                event.accept = true;
                _commit(static_cast<int>(p.items.size()) - 1);
                break;
            case Key::Enter:
                event.accept = true;
                _click();
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
            IWidget::keyPressEvent(event);
        }
    }

    void ComboBox::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    ComboBoxItem ComboBox::_getItem(int value) const
    {
        DTK_P();
        ComboBoxItem out;
        if (value >= 0 && value < static_cast<int>(p.items.size()))
        {
            out = p.items[value];
        }
        return out;
    }

    void ComboBox::_click()
    {
        DTK_P();
        takeKeyFocus();
        if (auto context = _getContext().lock())
        {
            if (!p.menu)
            {
                p.menu = ComboBoxMenu::create(context, p.items, p.currentIndex);
                p.menu->open(getWindow(), getGeometry());
                auto weak = std::weak_ptr<ComboBox>(std::dynamic_pointer_cast<ComboBox>(shared_from_this()));
                p.menu->setCallback(
                    [weak](int index)
                    {
                        if (auto widget = weak.lock())
                        {
                            widget->_p->menu->close();
                            if (index != -1)
                            {
                                widget->_commit(index);
                            }
                        }
                    });
                p.menu->setCloseCallback(
                    [weak]
                    {
                        if (auto widget = weak.lock())
                        {
                            widget->_p->menu.reset();
                        }
                    });
            }
            else
            {
                p.menu->close();
                p.menu.reset();
            }
        }
    }

    void ComboBox::_commit(int value)
    {
        DTK_P();
        const int currentIndex = p.currentIndex;
        setCurrentIndex(value);
        if (p.currentIndex != currentIndex)
        {
            if (p.indexCallback)
            {
                p.indexCallback(p.currentIndex);
            }
            if (p.itemCallback)
            {
                p.itemCallback(_getItem(p.currentIndex));
            }
        }
    }
}