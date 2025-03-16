// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ScrollWidget.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/GridLayout.h>
#include <dtk/ui/ScrollArea.h>
#include <dtk/ui/ScrollBar.h>

#include <optional>

namespace dtk
{
    struct ScrollWidget::Private
    {
        ScrollType scrollType = ScrollType::Both;
        bool scrollBarsVisible = true;
        bool scrollBarsAutoHide = true;
        bool scrollEventsEnabled = true;
        bool border = true;
        std::shared_ptr<IWidget> widget;
        std::shared_ptr<ScrollArea> scrollArea;
        std::shared_ptr<ScrollBar> horizontalScrollBar;
        std::shared_ptr<ScrollBar> verticalScrollBar;
        std::shared_ptr<GridLayout> layout;
        std::function<void(const V2I&)> scrollPosCallback;

        struct SizeData
        {
            std::optional<float> displayScale;
            int border = 0;
        };
        SizeData size;
    };

    void ScrollWidget::_init(
        const std::shared_ptr<Context>& context,
        ScrollType scrollType,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ScrollWidget", parent);
        DTK_P();

        p.scrollType = scrollType;

        p.scrollArea = ScrollArea::create(context, scrollType);
        p.scrollArea->setStretch(Stretch::Expanding);

        switch (scrollType)
        {
        case ScrollType::Horizontal:
            p.horizontalScrollBar = ScrollBar::create(context, Orientation::Horizontal);
            break;
        case ScrollType::Vertical:
        case ScrollType::Menu:
            p.verticalScrollBar = ScrollBar::create(context, Orientation::Vertical);
            break;
        case ScrollType::Both:
            p.horizontalScrollBar = ScrollBar::create(context, Orientation::Horizontal);
            p.verticalScrollBar = ScrollBar::create(context, Orientation::Vertical);
            break;
        default: break;
        }

        p.layout = GridLayout::create(context, shared_from_this());
        p.layout->setMarginRole(p.border ? SizeRole::Border : SizeRole::None);
        p.layout->setSpacingRole(SizeRole::None);
        p.scrollArea->setParent(p.layout);
        p.layout->setGridPos(p.scrollArea, 0, 0);
        if (p.horizontalScrollBar)
        {
            if (p.scrollBarsAutoHide)
            {
                p.horizontalScrollBar->hide();
            }
            p.horizontalScrollBar->setParent(p.layout);
            p.layout->setGridPos(p.horizontalScrollBar, 1, 0);
        }
        if (p.verticalScrollBar)
        {
            if (p.scrollBarsAutoHide)
            {
                p.verticalScrollBar->hide();
            }
            p.verticalScrollBar->setParent(p.layout);
            p.layout->setGridPos(p.verticalScrollBar, 0, 1);
        }

        if (p.horizontalScrollBar)
        {
            p.horizontalScrollBar->setScrollPosCallback(
                [this](int value)
                {
                    V2I scrollPos;
                    scrollPos.x = value;
                    if (_p->verticalScrollBar)
                    {
                        scrollPos.y = _p->verticalScrollBar->getScrollPos();
                    }
                    _p->scrollArea->setScrollPos(scrollPos);
                });
        }

        if (p.verticalScrollBar)
        {
            p.verticalScrollBar->setScrollPosCallback(
                [this](int value)
                {
                    V2I scrollPos;
                    if (_p->horizontalScrollBar)
                    {
                        scrollPos.x = _p->horizontalScrollBar->getScrollPos();
                    }
                    scrollPos.y = value;
                    _p->scrollArea->setScrollPos(scrollPos);
                });
        }

        p.scrollArea->setScrollSizeCallback(
            [this](const Size2I& value)
            {
                if (_p->horizontalScrollBar)
                {
                    _p->horizontalScrollBar->setScrollSize(value.w);
                }
                if (_p->verticalScrollBar)
                {
                    _p->verticalScrollBar->setScrollSize(value.h);
                }
            });

        p.scrollArea->setScrollPosCallback(
            [this](const V2I& value)
            {
                if (_p->horizontalScrollBar)
                {
                    _p->horizontalScrollBar->setScrollPos(value.x);
                }
                if (_p->verticalScrollBar)
                {
                    _p->verticalScrollBar->setScrollPos(value.y);
                }
                if (_p->scrollPosCallback)
                {
                    _p->scrollPosCallback(value);
                }
            });
    }

    ScrollWidget::ScrollWidget() :
        _p(new Private)
    {}

    ScrollWidget::~ScrollWidget()
    {}

    std::shared_ptr<ScrollWidget> ScrollWidget::create(
        const std::shared_ptr<Context>& context,
        ScrollType scrollType,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ScrollWidget>(new ScrollWidget);
        out->_init(context, scrollType, parent);
        return out;
    }

    const std::shared_ptr<IWidget>& ScrollWidget::getWidget() const
    {
        return _p->widget;
    }

    void ScrollWidget::setWidget(const std::shared_ptr<IWidget>& value)
    {
        DTK_P();
        if (p.widget)
        {
            p.widget->setParent(nullptr);
        }
        p.widget = value;
        if (p.widget)
        {
            p.widget->setParent(_p->scrollArea);
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }

    Box2I ScrollWidget::getViewport() const
    {
        return _p->scrollArea->getChildrenClipRect();
    }

    const Size2I& ScrollWidget::getScrollSize() const
    {
        return _p->scrollArea->getScrollSize();
    }

    const V2I& ScrollWidget::getScrollPos() const
    {
        return _p->scrollArea->getScrollPos();
    }

    void ScrollWidget::setScrollPos(const V2I& value, bool clamp)
    {
        _p->scrollArea->setScrollPos(value, clamp);
    }

    void ScrollWidget::scrollTo(const Box2I& value)
    {
        _p->scrollArea->scrollTo(value);
    }

    void ScrollWidget::setScrollPosCallback(const std::function<void(const V2I&)>& value)
    {
        _p->scrollPosCallback = value;
    }

    bool ScrollWidget::areScrollBarsVisible() const
    {
        return _p->scrollBarsVisible;
    }

    void ScrollWidget::setScrollBarsVisible(bool value)
    {
        DTK_P();
        if (value == p.scrollBarsVisible)
            return;
        p.scrollBarsVisible = value;
        _scrollBarsUpdate();
    }

    bool ScrollWidget::getScrollBarsAutoHide() const
    {
        return _p->scrollBarsAutoHide;
    }

    void ScrollWidget::setScrollBarsAutoHide(bool value)
    {
        DTK_P();
        if (value == p.scrollBarsAutoHide)
            return;
        p.scrollBarsAutoHide = value;
        _scrollBarsUpdate();
    }

    bool ScrollWidget::areScrollEventsEnabled() const
    {
        return _p->scrollEventsEnabled;
    }

    void ScrollWidget::setScrollEventsEnabled(bool value)
    {
        _p->scrollEventsEnabled = value;
    }

    bool ScrollWidget::hasBorder() const
    {
        return _p->border;
    }

    void ScrollWidget::setBorder(bool value)
    {
        DTK_P();
        if (value == p.border)
            return;
        p.border = value;
        p.layout->setMarginRole(p.border ? SizeRole::Border : SizeRole::None);
        _setSizeUpdate();
        _setDrawUpdate();
    }

    SizeRole ScrollWidget::getMarginRole() const
    {
        return _p->layout->getMarginRole();
    }

    void ScrollWidget::setMarginRole(SizeRole value)
    {
        _p->layout->setMarginRole(value);
    }

    void ScrollWidget::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.layout->setGeometry(value);
        _scrollBarsUpdate();
    }

    void ScrollWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
        }

        Size2I sizeHint = _p->layout->getSizeHint();
        _setSizeHint(sizeHint);
    }

    void ScrollWidget::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        if (p.border)
        {
            const Box2I& g = getGeometry();
            event.render->drawMesh(
                border(g, p.size.border),
                event.style->getColorRole(ColorRole::Border));
        }
    }

    void ScrollWidget::scrollEvent(ScrollEvent& event)
    {
        IWidget::scrollEvent(event);
        DTK_P();
        if (p.scrollEventsEnabled)
        {
            event.accept = true;
            V2I scrollPos = getScrollPos();
            scrollPos.y -= event.value.y * _getLineStep();
            setScrollPos(scrollPos);
        }
    }

    void ScrollWidget::keyPressEvent(KeyEvent& event)
    {
        DTK_P();
        if (0 == event.modifiers)
        {
            switch (event.key)
            {
            case Key::PageUp:
            {
                event.accept = true;
                V2I scrollPos = getScrollPos();
                scrollPos.y -= _getPageStep();
                setScrollPos(scrollPos);
                break;
            }
            case Key::PageDown:
            {
                event.accept = true;
                V2I scrollPos = getScrollPos();
                scrollPos.y += _getPageStep();
                setScrollPos(scrollPos);
                break;
            }
            default: break;
            }
        }
        if (!event.accept)
        {
            IWidget::keyPressEvent(event);
        }
    }

    void ScrollWidget::keyReleaseEvent(KeyEvent& event)
    {
        IWidget::keyReleaseEvent(event);
        event.accept = true;
    }

    int ScrollWidget::_getLineStep() const
    {
        DTK_P();
        const Size2I scrollAreaSize = p.scrollArea->getGeometry().size();
        return scrollAreaSize.h / 10.F;
    }

    int ScrollWidget::_getPageStep() const
    {
        DTK_P();
        const Size2I scrollAreaSize = p.scrollArea->getGeometry().size();
        return scrollAreaSize.h;
    }

    void ScrollWidget::_scrollBarsUpdate()
    {
        DTK_P();
        const Size2I scrollSize = p.scrollArea->getScrollSize();
        const Size2I scrollAreaSize = p.scrollArea->getGeometry().size();
        if (p.horizontalScrollBar)
        {
            bool visible = p.scrollBarsVisible;
            if (p.scrollBarsAutoHide)
            {
                visible &= scrollSize.w > scrollAreaSize.w;
            }
            p.horizontalScrollBar->setVisible(visible);
        }
        if (p.verticalScrollBar)
        {
            bool visible = p.scrollBarsVisible;
            if (p.scrollBarsAutoHide)
            {
                visible &= scrollSize.h > scrollAreaSize.h;
            }
            p.verticalScrollBar->setVisible(visible);
        }
    }
}