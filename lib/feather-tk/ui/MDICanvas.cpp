// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/MDICanvas.h>

#include <feather-tk/ui/MDIWidget.h>

namespace feather_tk
{
    struct MDICanvas::Private
    {
        Size2I canvasSize = Size2I(500, 500);
        Size2I gridSize = Size2I(20, 20);
        std::vector<std::pair<V2I, std::shared_ptr<MDIWidget> > > newWidgets;
        std::map<std::shared_ptr<IWidget>, Size2I> sizeHints;

        struct SizeData
        {
            Size2I gridSize;
        };
        SizeData size;

        struct MouseData
        {
            std::shared_ptr<MDIWidget> widget;
            Box2I geom;
        };
        MouseData mouse;
    };

    void MDICanvas::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::MDICanvas", parent);
        _setMouseHoverEnabled(true);
        _setMousePressEnabled(true);
    }

    MDICanvas::MDICanvas() :
        _p(new Private)
    {}

    MDICanvas::~MDICanvas()
    {}

    std::shared_ptr<MDICanvas> MDICanvas::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<MDICanvas>(new MDICanvas);
        out->_init(context, parent);
        return out;
    }

    const Size2I& MDICanvas::getCanvasSize() const
    {
        return _p->canvasSize;
    }

    void MDICanvas::setCanvasSize(const Size2I& value)
    {
        FEATHER_TK_P();
        if (value == p.canvasSize)
            return;
        p.canvasSize = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    const Size2I& MDICanvas::getGridSize() const
    {
        return _p->gridSize;
    }

    void MDICanvas::setGridSize(const Size2I& value)
    {
        FEATHER_TK_P();
        if (value == p.gridSize)
            return;
        p.gridSize = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    std::shared_ptr<MDIWidget> MDICanvas::addWidget(
        const std::string& title,
        const V2I& pos,
        const std::shared_ptr<IWidget>& value)
    {
        FEATHER_TK_P();
        std::shared_ptr<MDIWidget> out;
        if (auto context = getContext())
        {
            out = MDIWidget::create(context, title, shared_from_this());
            out->setWidget(value);
            auto weak = std::weak_ptr<MDIWidget>(out);
            out->setPressCallback(
                [this, weak](bool value)
                {
                    if (value)
                    {
                        if (auto widget = weak.lock())
                        {
                            moveToFront(widget);
                            _p->mouse.widget = widget;
                            _p->mouse.geom = widget->getGeometry();
                        }
                    }
                    else
                    {
                        _p->mouse.widget.reset();
                        _p->mouse.geom = Box2I();
                    }
                });
            out->setMoveCallback(
                [this](const V2I& move)
                {
                    if (auto widget = _p->mouse.widget)
                    {
                        const Box2I& pg = getGeometry();
                        Box2I g = widget->_removeMargins(_p->mouse.geom);
                        g = Box2I(
                            clamp(
                                _snapToGridX(g.min.x - pg.min.x + move.x),
                                0,
                                _snapToGridX(pg.max.x + 1 - pg.min.x - g.w())) + pg.min.x,
                            clamp(
                                _snapToGridY(g.min.y - pg.min.y + move.y),
                                0,
                                _snapToGridY(pg.max.y + 1 - pg.min.y - g.h())) + pg.min.y,
                            g.w(),
                            g.h());
                        widget->setGeometry(widget->_addMargins(g));
                    }
                });
            out->setResizeCallback(
                [this](MDIResize value, const V2I& move)
                {
                    if (auto widget = _p->mouse.widget)
                    {
                        const Box2I& pg = getGeometry();
                        const Size2I sizeHintGrid = _snapToGrid(widget->_removeMargins(widget->getSizeHint()));
                        Box2I g = widget->_removeMargins(_p->mouse.geom);
                        switch (value)
                        {
                        case MDIResize::North:
                            g.min.y = clamp(
                                _snapToGridY(g.min.y - pg.min.y + move.y),
                                0,
                                _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                            break;
                        case MDIResize::NorthEast:
                            g.min.y = clamp(
                                _snapToGridY(g.min.y - pg.min.y + move.y),
                                0,
                                _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                            g.max.x = clamp(
                                _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                            break;
                        case MDIResize::East:
                            g.max.x = clamp(
                                _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                            break;
                        case MDIResize::SouthEast:
                            g.max.x = clamp(
                                _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                            g.max.y = clamp(
                                _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                            break;
                        case MDIResize::South:
                            g.max.y = clamp(
                                _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                            break;
                        case MDIResize::SouthWest:
                            g.min.x = clamp(
                                _snapToGridX(g.min.x - pg.min.x + move.x),
                                0,
                                _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                            g.max.y = clamp(
                                _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                            break;
                        case MDIResize::West:
                            g.min.x = clamp(
                                _snapToGridX(g.min.x - pg.min.x + move.x),
                                0,
                                _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                            break;
                        case MDIResize::NorthWest:
                            g.min.x = clamp(
                                _snapToGridX(g.min.x - pg.min.x + move.x),
                                0,
                                _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                            g.min.y = clamp(
                                _snapToGridY(g.min.y - pg.min.y + move.y),
                                0,
                                _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                            break;
                        default: break;
                        }
                        widget->setGeometry(widget->_addMargins(g));
                    }
                });
            p.newWidgets.push_back(std::make_pair(pos, out));
            _setSizeUpdate();
            _setDrawUpdate();
        }
        return out;
    }

    void MDICanvas::setGeometry(const Box2I& value)
    {
        V2I offset = value.min - getGeometry().min;
        IWidget::setGeometry(value);
        FEATHER_TK_P();

        // Place new child widgets on the canvas.
        const Box2I& pg = getGeometry();
        const Size2I& gridSize = p.size.gridSize;
        for (auto i : p.newWidgets)
        {
            const Size2I& sizeHint = i.second->getSizeHint();
            p.sizeHints[i.second] = sizeHint;
            Box2I g = i.second->_removeMargins(Box2I(i.first, sizeHint));
            const Size2I sizeHintGrid = _snapToGrid(i.second->_removeMargins(sizeHint));
            g = Box2I(
                _snapToGridX(g.min.x),
                _snapToGridY(g.min.y),
                sizeHintGrid.w,
                sizeHintGrid.h);
            i.second->setGeometry(i.second->_addMargins(g));
        }
        p.newWidgets.clear();

        // Update the child widget geometry.
        for (const auto& child : getChildren())
        {
            if (auto mdi = std::dynamic_pointer_cast<MDIWidget>(child))
            {
                Box2I g = mdi->_removeMargins(mdi->getGeometry());

                // Add the parent offset.
                g.min = g.min + offset;
                g.max = g.max + offset;

                // Update the size hint.
                const Size2I& sizeHint = mdi->getSizeHint();
                const auto i = p.sizeHints.find(mdi);
                if (i != p.sizeHints.end() && i->second != sizeHint)
                {
                    p.sizeHints[mdi] = sizeHint;
                    const Size2I sizeHintGrid = _snapToGrid(mdi->_removeMargins(sizeHint));
                    g = Box2I(
                        g.min.x,
                        g.min.y,
                        std::max(g.w(), sizeHintGrid.w),
                        std::max(g.h(), sizeHintGrid.h));
                }

                // Clamp to the parent geometry.
                if (g.min.x < pg.min.x ||
                    g.min.y < pg.min.y ||
                    g.max.x > pg.max.x ||
                    g.max.y > pg.max.y)
                {
                    const Size2I sizeHintGrid = _snapToGrid(mdi->_removeMargins(sizeHint));
                    g.min.x = clamp(
                        _snapToGridX(g.min.x - pg.min.x),
                        0,
                        _snapToGridX(pg.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                    g.min.y = clamp(
                        _snapToGridY(g.min.y - pg.min.y),
                        0,
                        _snapToGridY(pg.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                    g.max.x = clamp(
                        _snapToGridX(g.max.x + 1 - pg.min.x),
                        _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                        _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                    g.max.y = clamp(
                        _snapToGridX(g.max.y + 1 - pg.min.y),
                        _snapToGridX(g.min.y - pg.min.y) + sizeHintGrid.h,
                        _snapToGridX(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                }

                mdi->setGeometry(mdi->_addMargins(g));
            }
        }
    }

    void MDICanvas::childRemoveEvent(const ChildRemoveEvent& event)
    {
        IWidget::childRemoveEvent(event);
        FEATHER_TK_P();
        const auto i = p.sizeHints.find(event.child);
        if (i != p.sizeHints.end())
        {
            p.sizeHints.erase(i);
        }
    }

    void MDICanvas::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();
        p.size.gridSize = p.gridSize * static_cast<int>(event.displayScale);
        _setSizeHint(p.canvasSize * static_cast<int>(event.displayScale));
    }

    void MDICanvas::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        FEATHER_TK_P();
        const Box2I& g = getGeometry();

        // Draw the grid.
        const Size2I& gridSize = p.size.gridSize;
        V2I offset;
        offset.x = g.min.x % gridSize.w;
        offset.y = g.min.y % gridSize.h;
        Box2I gridRect = intersect(g, drawRect);
        gridRect.min.x = (gridRect.min.x / gridSize.w - 2) * gridSize.w + offset.x;
        gridRect.min.y = (gridRect.min.y / gridSize.h - 2) * gridSize.h + offset.y;
        gridRect.max.x = (gridRect.max.x / gridSize.w + 2) * gridSize.w + offset.x;
        gridRect.max.y = (gridRect.max.y / gridSize.h + 2) * gridSize.h + offset.y;
        LineOptions options;
        options.width = 1 * event.displayScale;
        std::vector<std::pair<V2I, V2I> > lines;
        for (int x = gridRect.min.x; x < gridRect.max.x; x += gridSize.w)
        {
            lines.push_back({ V2I(x, gridRect.min.y), V2I(x, gridRect.max.y) });
        }
        for (int y = gridRect.min.y; y < gridRect.max.y; y += gridSize.h)
        {
            lines.push_back({ V2I(gridRect.min.x, y), V2I(gridRect.max.x, y) });
        }
        event.render->drawLines(
            lines,
            event.style->getColorRole(ColorRole::Border),
            options);
    }

    void MDICanvas::mouseMoveEvent(MouseMoveEvent& event)
    {
        IWidget::mouseMoveEvent(event);
    }

    void MDICanvas::mousePressEvent(MouseClickEvent& event)
    {
        IWidget::mousePressEvent(event);
    }

    void MDICanvas::mouseReleaseEvent(MouseClickEvent& event)
    {
        IWidget::mouseReleaseEvent(event);
    }

    int MDICanvas::_snapToGridX(int value) const
    {
        FEATHER_TK_P();
        return value / p.size.gridSize.w * p.size.gridSize.w;
    }

    int MDICanvas::_snapToGridY(int value) const
    {
        FEATHER_TK_P();
        return value / p.size.gridSize.h * p.size.gridSize.h;
    }

    Size2I MDICanvas::_snapToGrid(const Size2I& value) const
    {
        FEATHER_TK_P();
        return Size2I(
            ceilf(value.w / static_cast<float>(p.size.gridSize.w)) * p.size.gridSize.w,
            ceilf(value.h / static_cast<float>(p.size.gridSize.h)) * p.size.gridSize.h);
    }
}