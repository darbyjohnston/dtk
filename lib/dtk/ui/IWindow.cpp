// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/IWindow.h>

#include <dtk/ui/IClipboard.h>
#include <dtk/ui/IDialog.h>
#include <dtk/ui/IPopup.h>
#include <dtk/ui/Tooltip.h>

namespace dtk
{
    struct IWindow::Private
    {
        bool inside = false;
        V2I cursorPos;
        V2I cursorPosPrev;
        std::weak_ptr<IWidget> hover;
        std::weak_ptr<IWidget> mousePress;
        MouseClickEvent mouseClickEvent;
        std::weak_ptr<IWidget> keyFocus;
        std::list<std::pair<
            std::shared_ptr<IWidget>,
            std::weak_ptr<IWidget> > > restoreKeyFocus;
        std::weak_ptr<IWidget> keyPress;
        KeyEvent keyEvent;

        std::shared_ptr<DragAndDropData> dndData;
        std::shared_ptr<Image> dndCursor;
        V2I dndCursorHotspot;
        std::weak_ptr<IWidget> dndHover;

        std::shared_ptr<IClipboard> clipboard;

        bool tooltipsEnabled = true;
        std::shared_ptr<Tooltip> tooltip;
        V2I tooltipPos;
        std::chrono::steady_clock::time_point tooltipTimer;

        struct SizeData
        {
            int dl = 0;
        };
        SizeData size;
    };

    IWindow::IWindow() :
        _p(new Private)
    {
        setBackgroundRole(ColorRole::Window);
    }

    IWindow::~IWindow()
    {}

    std::shared_ptr<IWidget> IWindow::getKeyFocus() const
    {
        return _p->keyFocus.lock();
    }

    void IWindow::setKeyFocus(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        if (value == p.keyFocus.lock())
            return;
        if (auto widget = p.keyFocus.lock())
        {
            p.keyFocus.reset();
            widget->keyFocusEvent(false);
            _setDrawUpdate();
        }
        if (value && value->acceptsKeyFocus())
        {
            p.keyFocus = value;
            if (auto widget = p.keyFocus.lock())
            {
                widget->keyFocusEvent(true);
                _setDrawUpdate();
            }
        }
    }

    std::shared_ptr<IWidget> IWindow::getNextKeyFocus(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        std::shared_ptr<IWidget> out;
        const auto& children = getChildren();
        if (!children.empty())
        {
            std::list<std::shared_ptr<IWidget> > widgets;
            _getKeyFocus(children.back(), widgets);
            if (!widgets.empty())
            {
                auto i = std::find(widgets.begin(), widgets.end(), value);
                if (i != widgets.end())
                {
                    ++i;
                    if (i != widgets.end())
                    {
                        out = *i;
                    }
                }
                if (!out)
                {
                    out = widgets.front();
                }
            }
        }
        return out;
    }

    std::shared_ptr<IWidget> IWindow::getPrevKeyFocus(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        std::shared_ptr<IWidget> out;
        const auto& children = getChildren();
        if (!children.empty())
        {
            std::list<std::shared_ptr<IWidget> > widgets;
            _getKeyFocus(children.back(), widgets);
            if (!widgets.empty())
            {
                auto i = std::find(widgets.rbegin(), widgets.rend(), value);
                if (i != widgets.rend())
                {
                    ++i;
                    if (i != widgets.rend())
                    {
                        out = *i;
                    }
                }
                if (!out)
                {
                    out = widgets.back();
                }
            }
        }
        return out;
    }

    const std::shared_ptr<IClipboard>& IWindow::getClipboard() const
    {
        return _p->clipboard;
    }

    void IWindow::setClipboard(const std::shared_ptr<IClipboard>& value)
    {
        _p->clipboard = value;
    }

    bool IWindow::getTooltipsEnabled() const
    {
        return _p->tooltipsEnabled;
    }

    void IWindow::setTooltipsEnabled(bool value)
    {
        DTK_P();
        if (value == p.tooltipsEnabled)
            return;
        p.tooltipsEnabled = value;
        if (!value)
        {
            _closeTooltip();
        }
    }

    void IWindow::setCloseCallback(const std::function<void(void)>& value)
    {}

    void IWindow::setVisible(bool value)
    {
        const bool changed = value != isVisible(false);
        IWidget::setVisible(value);
        DTK_P();
        if (changed && !isVisible(false))
        {
            if (auto hover = p.hover.lock())
            {
                p.hover.reset();
                hover->mouseLeaveEvent();
            }
            if (auto pressed = p.mousePress.lock())
            {
                p.mousePress.reset();
                p.mouseClickEvent.pos = p.cursorPos;
                p.mouseClickEvent.accept = false;
                pressed->mouseReleaseEvent(p.mouseClickEvent);
            }
            if (auto focus = p.keyFocus.lock())
            {
                p.keyFocus.reset();
                focus->keyFocusEvent(false);
            }
            if (auto keyPress = p.keyPress.lock())
            {
                p.keyPress.reset();
                p.keyEvent.pos = p.cursorPos;
                p.keyEvent.accept = false;
                keyPress->keyReleaseEvent(p.keyEvent);
            }
            if (auto dragAndDrop = p.dndHover.lock())
            {
                p.dndHover.reset();
                DragAndDropEvent event(
                    p.cursorPos,
                    p.cursorPosPrev,
                    p.dndData);
                dragAndDrop->dragLeaveEvent(event);
            }
            p.dndData.reset();
            p.dndCursor.reset();
            _clipEventRecursive(shared_from_this(), getGeometry(), true);
        }
    }

    void IWindow::tickEvent(
        bool parentsVisible,
        bool parentsEnabled,
        const TickEvent& event)
    {
        IWidget::tickEvent(parentsVisible, parentsEnabled, event);
        DTK_P();
        if (p.inside)
        {
            if (!p.mousePress.lock())
            {
                MouseMoveEvent mouseMoveEvent(p.cursorPos, p.cursorPos);
                _hoverUpdate(mouseMoveEvent);
            }

            if (p.tooltipsEnabled)
            {
                const auto tooltipTime = std::chrono::steady_clock::now();
                const auto tooltipDiff = std::chrono::duration_cast<std::chrono::milliseconds>(tooltipTime - p.tooltipTimer);
                if (tooltipDiff > tooltipTimeout && !p.tooltip)
                {
                    if (auto context = getContext())
                    {
                        std::string text;
                        const auto widgets = _getUnderCursor(UnderCursor::Tooltip, p.cursorPos);
                        for (const auto& widget : widgets)
                        {
                            text = widget->getTooltip();
                            if (!text.empty())
                            {
                                break;
                            }
                        }
                        if (!text.empty())
                        {
                            p.tooltip = Tooltip::create(
                                context,
                                text,
                                p.cursorPos,
                                shared_from_this());
                            p.tooltipPos = p.cursorPos;
                        }
                    }
                }
            }
        }
    }

    void IWindow::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();
        p.size.dl = event.style->getSizeRole(SizeRole::DragLength, event.displayScale);
    }

    void IWindow::drawOverlayEvent(const Box2I& clipRect, const DrawEvent& event)
    {
        IWidget::drawOverlayEvent(clipRect, event);
        DTK_P();
        if (p.dndCursor)
        {
            event.render->drawImage(
                p.dndCursor,
                Box2F(
                    p.cursorPos.x - p.dndCursorHotspot.x,
                    p.cursorPos.y - p.dndCursorHotspot.y,
                    p.dndCursor->getWidth(),
                    p.dndCursor->getHeight()),
                Color4F(1.F, 1.F, 1.F));
        }
    }

    bool IWindow::_hasSizeUpdate(const std::shared_ptr<IWidget>& widget) const
    {
        bool out = widget->getUpdates() & static_cast<int>(Update::Size);
        if (out)
        {
            //std::cout << "Size update: " << widget->getObjectName() << std::endl;
        }
        else
        {
            for (const auto& child : widget->getChildren())
            {
                out |= _hasSizeUpdate(child);
            }
        }
        return out;
    }

    void IWindow::_sizeHintEventRecursive(
        const std::shared_ptr<IWidget>& widget,
        const SizeHintEvent& event)
    {
        for (const auto& child : widget->getChildren())
        {
            _sizeHintEventRecursive(child, event);
        }
        widget->sizeHintEvent(event);
    }

    bool IWindow::_hasDrawUpdate(const std::shared_ptr<IWidget>& widget) const
    {
        bool out = false;
        if (!widget->isClipped())
        {
            out = widget->getUpdates() & static_cast<int>(Update::Draw);
            if (out)
            {
                //std::cout << "Draw update: " << widget->getObjectName() << std::endl;
            }
            else
            {
                for (const auto& child : widget->getChildren())
                {
                    out |= _hasDrawUpdate(child);
                }
            }
        }
        return out;
    }

    void IWindow::_drawEventRecursive(
        const std::shared_ptr<IWidget>& widget,
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        const Box2I& g = widget->getGeometry();
        if (!widget->isClipped() && g.w() > 0 && g.h() > 0)
        {
            event.render->setClipRect(drawRect);
            widget->drawEvent(drawRect, event);
            const Box2I childrenClipRect = intersect(
                widget->getChildrenClipRect(),
                drawRect);
            for (const auto& child : widget->getChildren())
            {
                const Box2I& childGeometry = child->getGeometry();
                if (intersects(childGeometry, childrenClipRect))
                {
                    _drawEventRecursive(
                        child,
                        intersect(childGeometry, childrenClipRect),
                        event);
                }
            }
            event.render->setClipRect(drawRect);
            widget->drawOverlayEvent(drawRect, event);
        }
    }

    bool IWindow::_key(
        Key key,
        bool press,
        int modifiers)
    {
        DTK_P();
        _closeTooltip();
        p.keyEvent = KeyEvent(key, modifiers, p.cursorPos);
        if (press)
        {
            // Send event to the focused widget or parent.
            if (auto widget = p.keyFocus.lock())
            {
                while (widget)
                {
                    widget->keyPressEvent(p.keyEvent);
                    if (p.keyEvent.accept)
                    {
                        p.keyPress = widget;
                        break;
                    }
                    if (auto dialog = std::dynamic_pointer_cast<IDialog>(widget))
                    {
                        break;
                    }
                    widget = widget->getParent().lock();
                }
            }

            // Send event to the hovered widget.
            if (!p.keyEvent.accept)
            {
                auto widgets = _getUnderCursor(UnderCursor::Hover, p.cursorPos);
                for (auto i = widgets.begin(); i != widgets.end(); ++i)
                {
                    (*i)->keyPressEvent(p.keyEvent);
                    if (p.keyEvent.accept)
                    {
                        p.keyPress = *i;
                        break;
                    }
                }
            }

            // Handle tab key navigation.
            if (!p.keyEvent.accept && Key::Tab == key)
            {
                auto keyFocus = p.keyFocus.lock();
                if (modifiers == static_cast<int>(KeyModifier::Shift))
                {
                    keyFocus = getPrevKeyFocus(keyFocus);
                }
                else
                {
                    keyFocus = getNextKeyFocus(keyFocus);
                }
                setKeyFocus(keyFocus);
            }
        }
        else if (auto widget = p.keyPress.lock())
        {
            widget->keyReleaseEvent(p.keyEvent);
        }
        return p.keyEvent.accept;
    }

    void IWindow::_text(const std::string& value)
    {
        DTK_P();
        _closeTooltip();
        TextEvent event(value);
        if (auto widget = p.keyFocus.lock())
        {
            while (widget)
            {
                widget->textEvent(event);
                if (event.accept)
                {
                    break;
                }
                widget = widget->getParent().lock();
            }
        }
    }

    void IWindow::_cursorEnter(bool enter)
    {
        DTK_P();
        p.inside = enter;
        if (!p.inside)
        {
            if (auto hover = p.hover.lock())
            {
                hover->mouseLeaveEvent();
            }
            p.hover.reset();
        }
    }

    void IWindow::_cursorPos(const V2I& pos)
    {
        DTK_P();

        p.cursorPosPrev = p.cursorPos;
        p.cursorPos = pos;

        MouseMoveEvent event(p.cursorPos, p.cursorPosPrev);
        auto widget = p.mousePress.lock();
        if (widget)
        {
            if (p.dndData)
            {
                // Find the drag and drop hover widget.
                DragAndDropEvent event(
                    p.cursorPos,
                    p.cursorPosPrev,
                    p.dndData);
                auto hover = p.dndHover.lock();
                auto widgets = _getUnderCursor(UnderCursor::Hover, p.cursorPos);
                std::shared_ptr<IWidget> widget;
                while (!widgets.empty())
                {
                    if (hover == widgets.front())
                    {
                        break;
                    }
                    widgets.front()->dragEnterEvent(event);
                    if (event.accept)
                    {
                        widget = widgets.front();
                        break;
                    }
                    widgets.pop_front();
                }
                if (widget)
                {
                    if (hover)
                    {
                        hover->dragLeaveEvent(event);
                    }
                    p.dndHover = widget;
                }
                else if (widgets.empty() && hover)
                {
                    p.dndHover.reset();
                    hover->dragLeaveEvent(event);
                }
                hover = p.dndHover.lock();
                if (hover)
                {
                    DragAndDropEvent event(
                        p.cursorPos,
                        p.cursorPosPrev,
                        p.dndData);
                    hover->dragMoveEvent(event);
                }
            }
            else
            {
                widget->mouseMoveEvent(event);

                p.dndData = event.dndData;
                p.dndCursor = event.dndCursor;
                p.dndCursorHotspot = event.dndCursorHotspot;
                if (p.dndData)
                {
                    // Start a drag and drop.
                    widget->mouseReleaseEvent(p.mouseClickEvent);
                    widget->mouseLeaveEvent();
                }
            }
        }
        else
        {
            _hoverUpdate(event);
        }

        if (widget && p.dndCursor)
        {
            _setDrawUpdate();
        }

        if (length(p.cursorPos - p.tooltipPos) > p.size.dl)
        {
            _closeTooltip();
        }
    }

    void IWindow::_mouseButton(int button, bool press, int modifiers)
    {
        DTK_P();
        _closeTooltip();
        p.mouseClickEvent = MouseClickEvent(button, modifiers, p.cursorPos);
        if (press)
        {
            auto widgets = _getUnderCursor(UnderCursor::Hover, p.cursorPos);
            auto i = widgets.begin();
            for (; i != widgets.end(); ++i)
            {
                (*i)->mousePressEvent(p.mouseClickEvent);
                if (p.mouseClickEvent.accept)
                {
                    p.mousePress = *i;
                    break;
                }
                if (auto popup = std::dynamic_pointer_cast<IPopup>(*i))
                {
                    popup->close();
                }
            }
            if (!p.mouseClickEvent.accept)
            {
                setKeyFocus(nullptr);
            }
        }
        else
        {
            if (auto widget = p.mousePress.lock())
            {
                p.mousePress.reset();
                if (auto hover = p.dndHover.lock())
                {
                    // Finish a drag and drop.
                    p.dndHover.reset();
                    DragAndDropEvent event(
                        p.cursorPos,
                        p.cursorPosPrev,
                        p.dndData);
                    hover->dropEvent(event);
                    hover->dragLeaveEvent(event);
                }
                else
                {
                    widget->mouseReleaseEvent(p.mouseClickEvent);
                }
                p.dndData.reset();
                p.dndCursor.reset();
                _setDrawUpdate();
            }

            MouseMoveEvent event(
                p.cursorPos,
                p.cursorPosPrev);
            _hoverUpdate(event);
        }
    }

    void IWindow::_scroll(const V2F& value, int modifiers)
    {
        DTK_P();
        _closeTooltip();
        ScrollEvent event(value, modifiers, p.cursorPos);
        auto widgets = _getUnderCursor(UnderCursor::Hover, p.cursorPos);
        for (auto i = widgets.begin(); i != widgets.end(); ++i)
        {
            (*i)->scrollEvent(event);
            if (event.accept)
            {
                break;
            }
        }
    }

    void IWindow::_clipEventRecursive(
        const std::shared_ptr<IWidget>& widget,
        const Box2I& clipRect,
        bool clipped)
    {
        const Box2I& g = widget->getGeometry();
        clipped |= !intersects(g, clipRect);
        clipped |= !widget->isVisible(false);
        const Box2I intersectedClipRect = intersect(g, clipRect);
        widget->clipEvent(intersectedClipRect, clipped);
        const Box2I childrenClipRect = intersect(
            widget->getChildrenClipRect(), intersectedClipRect);
        for (const auto& child : widget->getChildren())
        {
            const Box2I& childGeometry = child->getGeometry();
            _clipEventRecursive(
                child,
                intersect(childGeometry, childrenClipRect),
                clipped);
        }
    }

    void IWindow::_drop(const std::vector<std::string>&)
    {}

    std::list<std::shared_ptr<IWidget> > IWindow::_getUnderCursor(
        UnderCursor type,
        const V2I& pos)
    {
        DTK_P();
        std::list<std::shared_ptr<IWidget> > out;
        _getUnderCursor(type, shared_from_this(), pos, out);
        if (UnderCursor::Tooltip == type)
        {
            auto i = out.begin();
            for (; i != out.end() && !std::dynamic_pointer_cast<IPopup>(*i); ++i)
                ;
            if (i != out.end())
            {
                out.erase(i, out.end());
            }
        }
        return out;
    }

    void IWindow::_getUnderCursor(
        UnderCursor type,
        const std::shared_ptr<IWidget>& widget,
        const V2I& pos,
        std::list<std::shared_ptr<IWidget> >& out)
    {
        if (!widget->isClipped() &&
            (UnderCursor::Tooltip == type ? true : widget->isEnabled()) &&
            contains(widget->getGeometry(), pos))
        {
            for (auto i = widget->getChildren().rbegin();
                i != widget->getChildren().rend();
                ++i)
            {
                _getUnderCursor(type, *i, pos, out);
            }
            out.push_back(widget);
        }
    }

    void IWindow::_hoverUpdate(MouseMoveEvent& event)
    {
        DTK_P();
        const auto widgets = _getUnderCursor(UnderCursor::Hover, p.cursorPos);
        std::shared_ptr<IWidget> hover;
        auto prev = p.hover.lock();
        for (const auto& widget : widgets)
        {
            if (widget == prev)
            {
                widget->mouseMoveEvent(event);
                hover = widget;
                break;
            }
            MouseEnterEvent enterEvent(p.cursorPos);
            widget->mouseEnterEvent(enterEvent);
            if (enterEvent.accept)
            {
                if (prev)
                {
                    prev->mouseLeaveEvent();
                }
                widget->mouseMoveEvent(event);
                hover = widget;
                break;
            }
        }
        if (!hover && prev)
        {
            prev->mouseLeaveEvent();
        }
        p.hover = hover;
    }

    void IWindow::_getKeyFocus(
        const std::shared_ptr<IWidget>& widget,
        std::list<std::shared_ptr<IWidget> >& out)
    {
        if (widget->acceptsKeyFocus())
        {
            out.push_back(widget);
        }
        for (const auto& child : widget->getChildren())
        {
            if (!child->isClipped() && child->isEnabled())
            {
                _getKeyFocus(child, out);
            }
        }
    }

    void IWindow::_closeTooltip()
    {
        DTK_P();
        if (p.tooltip)
        {
            p.tooltip->close();
            p.tooltip.reset();
        }
        p.tooltipTimer = std::chrono::steady_clock::now();
        p.tooltipPos = p.cursorPos;
    }
}