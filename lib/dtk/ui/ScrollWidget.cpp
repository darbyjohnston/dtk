// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/ScrollWidget.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/GridLayout.h>
#include <dtk/ui/ScrollArea.h>
#include <dtk/ui/ScrollBar.h>

namespace dtk
{
    struct ScrollWidget::Private
    {
        ScrollType scrollType = ScrollType::Both;
        bool scrollBarsVisible = true;
        bool scrollEventsEnabled = true;
        std::shared_ptr<IWidget> widget;
        std::shared_ptr<ScrollArea> scrollArea;
        std::shared_ptr<ScrollBar> horizontalScrollBar;
        std::shared_ptr<ScrollBar> verticalScrollBar;
        std::shared_ptr<GridLayout> layout;
        std::function<void(const V2I&)> scrollPosCallback;
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
        p.layout->setSpacingRole(SizeRole::None);
        p.layout->setStretch(Stretch::Expanding);
        p.scrollArea->setParent(p.layout);
        p.layout->setGridPos(p.scrollArea, 0, 0);
        if (p.horizontalScrollBar)
        {
            p.horizontalScrollBar->setParent(p.layout);
            p.layout->setGridPos(p.horizontalScrollBar, 1, 0);
        }
        if (p.verticalScrollBar)
        {
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
        DTK_P();
        bool out = false;
        if (p.horizontalScrollBar)
        {
            out |= p.horizontalScrollBar->isVisible(false);
        }
        if (p.verticalScrollBar)
        {
            out |= p.verticalScrollBar->isVisible(false);
        }
        return out;
    }

    void ScrollWidget::setScrollBarsVisible(bool value)
    {
        DTK_P();
        if (value == p.scrollBarsVisible)
            return;
        p.scrollBarsVisible = value;
        if (p.horizontalScrollBar)
        {
            p.horizontalScrollBar->setVisible(value);
        }
        if (p.verticalScrollBar)
        {
            p.verticalScrollBar->setVisible(value);
        }
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
        return _p->scrollArea->hasBorder();
    }

    void ScrollWidget::setBorder(bool value)
    {
        _p->scrollArea->setBorder(value);
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
        _p->layout->setGeometry(value);
    }

    void ScrollWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        _setSizeHint(_p->layout->getSizeHint());
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
}