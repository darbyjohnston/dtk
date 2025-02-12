// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/GridLayout.h>

#include <dtk/ui/LayoutUtil.h>

namespace dtk
{
    namespace
    {
        struct GridPos
        {
            int row = 0;
            int column = 0;
        };
    }

    struct GridLayout::Private
    {
        std::map<std::shared_ptr<IWidget>, GridPos> gridPos;
        ColorRole rowBackgroundRole = ColorRole::None;
        SizeRole marginRole = SizeRole::None;
        SizeRole spacingRole = SizeRole::Spacing;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int margin = 0;
            int spacing = 0;
        };
        SizeData size;

        struct GeomData
        {
            std::vector<int> rowSizeHints;
            int rowsVisibleCount = 0;
            std::vector<bool> rowsVisible;
            std::vector<int> rowSizes;

            std::vector<int> columnSizeHints;
            int columnsVisibleCount = 0;
            std::vector<bool> columnsVisible;
            std::vector<int> columnSizes;
        };
        GeomData geom;

        GridPos getSize() const;

        void getSizeHints(
            std::vector<int>& rows,
            std::vector<int>& columns) const;

        void getStretch(
            std::vector<bool>& rows,
            std::vector<bool>& columns) const;

        void getVisible(
            int& rows,
            int& columns) const;

        void getVisible(
            std::vector<bool>& rows,
            std::vector<bool>& columns) const;
    };

    void GridLayout::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::GridLayout", parent);
    }

    GridLayout::GridLayout() :
        _p(new Private)
    {}

    GridLayout::~GridLayout()
    {}

    std::shared_ptr<GridLayout> GridLayout::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<GridLayout>(new GridLayout);
        out->_init(context, parent);
        return out;
    }

    void GridLayout::setGridPos(
        const std::shared_ptr<IWidget>& child,
        int row,
        int column)
    {
        DTK_P();
        p.gridPos[child].row = row;
        p.gridPos[child].column = column;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    ColorRole GridLayout::getRowBackgroundRole(ColorRole) const
    {
        return _p->rowBackgroundRole;
    }

    void GridLayout::setRowBackgroundRole(ColorRole value)
    {
        DTK_P();
        if (value == p.rowBackgroundRole)
            return;
        p.rowBackgroundRole = value;
        _setDrawUpdate();
    }

    SizeRole GridLayout::getMarginRole() const
    {
        return _p->marginRole;
    }

    void GridLayout::setMarginRole(SizeRole value)
    {
        DTK_P();
        if (value == p.marginRole)
            return;
        p.marginRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    SizeRole GridLayout::getSpacingRole() const
    {
        return _p->spacingRole;
    }

    void GridLayout::setSpacingRole(SizeRole value)
    {
        DTK_P();
        if (value == p.spacingRole)
            return;
        p.spacingRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void GridLayout::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();

        // Get the total size.
        V2I totalSize;
        for (const auto& i : p.geom.rowSizeHints)
        {
            totalSize.y += i;
        }
        for (const auto& i : p.geom.columnSizeHints)
        {
            totalSize.x += i;
        }
        p.getVisible(p.geom.rowsVisible, p.geom.columnsVisible);

        // Get the layout stretch.
        std::vector<bool> rowStretch;
        std::vector<bool> columnStretch;
        p.getStretch(rowStretch, columnStretch);

        // Get the layout stretch size.
        const Box2I g = margin(getGeometry(), -p.size.margin);
        size_t rowStretchCount = 0;
        size_t columnStretchCount = 0;
        for (bool i : rowStretch)
        {
            if (i)
            {
                ++rowStretchCount;
            }
        }
        for (bool i : columnStretch)
        {
            if (i)
            {
                ++columnStretchCount;
            }
        }
        V2I stretchSize;
        if (rowStretchCount > 0)
        {
            stretchSize.y = (g.h() -
                (p.geom.rowsVisibleCount - 1) * p.size.spacing -
                totalSize.y) / rowStretchCount;
        }
        if (columnStretchCount > 0)
        {
            stretchSize.x = (g.w() -
                (p.geom.columnsVisibleCount - 1) * p.size.spacing -
                totalSize.x) / columnStretchCount;
        }

        // Get the sizes.
        p.geom.rowSizes.clear();
        p.geom.columnSizes.clear();
        for (int i = 0; i < p.geom.rowSizeHints.size(); ++i)
        {
            int size = p.geom.rowSizeHints[i];
            if (rowStretch[i])
            {
                size += stretchSize.y;
            }
            p.geom.rowSizes.push_back(size);
        }
        for (int i = 0; i < p.geom.columnSizeHints.size(); ++i)
        {
            int size = p.geom.columnSizeHints[i];
            if (columnStretch[i])
            {
                size += stretchSize.x;
            }
            p.geom.columnSizes.push_back(size);
        }

        // Layout the children.
        for (const auto& i : p.gridPos)
        {
            const bool visible = i.first->isVisible(false);
            V2I pos = g.min;
            for (int j = 0; j < i.second.row; ++j)
            {
                if (p.geom.rowsVisible[j])
                {
                    pos.y += p.geom.rowSizes[j] + (visible ? p.size.spacing : 0);
                }
            }
            for (int j = 0; j < i.second.column; ++j)
            {
                if (p.geom.columnsVisible[j])
                {
                    pos.x += p.geom.columnSizes[j] + (visible ? p.size.spacing : 0);
                }
            }
            const V2I size(
                p.geom.columnSizes[i.second.column],
                p.geom.rowSizes[i.second.row]);
            i.first->setGeometry(Box2I(pos.x, pos.y, size.x, size.y));
            /*i.first->setGeometry(
                align(
                    Box2I(pos.x, pos.y, size.x, size.y),
                    i.first->getSizeHint(),
                    i.first->getHAlign(),
                    i.first->getVAlign()));*/
        }
    }

    void GridLayout::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (p.size.init || event.displayScale != p.size.displayScale)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(p.marginRole, p.size.displayScale);
            p.size.spacing = event.style->getSizeRole(p.spacingRole, p.size.displayScale);
        }

        // Get size hints.
        p.geom.rowSizeHints.clear();
        p.geom.columnSizeHints.clear();
        p.getSizeHints(p.geom.rowSizeHints, p.geom.columnSizeHints);
        Size2I sizeHint;
        for (int i : p.geom.rowSizeHints)
        {
            sizeHint.h += i;
        }
        for (int i : p.geom.columnSizeHints)
        {
            sizeHint.w += i;
        }

        // Add spacing.
        p.geom.rowsVisibleCount = 0;
        p.geom.columnsVisibleCount = 0;
        p.getVisible(p.geom.rowsVisibleCount, p.geom.columnsVisibleCount);
        if (p.geom.rowsVisibleCount > 0)
        {
            sizeHint.h += (p.geom.rowsVisibleCount - 1) * p.size.spacing;
        }
        if (p.geom.columnsVisibleCount > 0)
        {
            sizeHint.w += (p.geom.columnsVisibleCount - 1) * p.size.spacing;
        }

        // Add the margin.
        sizeHint.w += p.size.margin * 2;
        sizeHint.h += p.size.margin * 2;

        _setSizeHint(sizeHint);
    }

    void GridLayout::drawEvent(const Box2I& drawRect, const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        if (p.rowBackgroundRole != ColorRole::None)
        {
            const Box2I g = margin(getGeometry(), -p.size.margin);
            int y = g.min.y;
            int row = 0;
            for (size_t i = 0;
                i < p.geom.rowSizes.size() && i < p.geom.rowsVisible.size();
                ++i)
            {
                if (p.geom.rowsVisible[i])
                {
                    if (row % 2 == 0)
                    {
                        event.render->drawRect(
                            Box2I(g.min.x, y, g.w(), p.geom.rowSizes[i]),
                            event.style->getColorRole(p.rowBackgroundRole));
                    }
                    y += p.geom.rowSizes[i] + p.size.spacing;
                    ++row;
                }
            }
        }
    }

    void GridLayout::childRemoveEvent(const ChildRemoveEvent& event)
    {
        IWidget::childRemoveEvent(event);
        DTK_P();
        const auto i = p.gridPos.find(event.child);
        if (i != p.gridPos.end())
        {
            p.gridPos.erase(i);
        }
        _setSizeUpdate();
        _setDrawUpdate();
    }

    GridPos GridLayout::Private::getSize() const
    {
        GridPos out;
        for (const auto& i : gridPos)
        {
            out.row = std::max(out.row, i.second.row);
            out.column = std::max(out.column, i.second.column);
        }
        if (!gridPos.empty())
        {
            out.row += 1;
            out.column += 1;
        }
        return out;
    }

    void GridLayout::Private::getSizeHints(
        std::vector<int>& rows,
        std::vector<int>& columns) const
    {
        const GridPos size = getSize();
        rows = std::vector<int>(size.row, false);
        columns = std::vector<int>(size.column, false);
        for (const auto& i : gridPos)
        {
            const bool visible = i.first->isVisible(false);
            if (visible)
            {
                const Size2I& sizeHint = i.first->getSizeHint();
                rows[i.second.row] = std::max(
                    rows[i.second.row],
                    sizeHint.h);
                columns[i.second.column] = std::max(
                    columns[i.second.column],
                    sizeHint.w);
            }
        }
    }

    void GridLayout::Private::getStretch(
        std::vector<bool>& rows,
        std::vector<bool>& columns) const
    {
        const GridPos size = getSize();
        rows = std::vector<bool>(size.row, false);
        columns = std::vector<bool>(size.column, false);
        for (const auto& i : gridPos)
        {
            const bool visible = i.first->isVisible(false);
            if (visible)
            {
                if (Stretch::Expanding == i.first->getVStretch())
                {
                    rows[i.second.row] = true;
                }
                if (Stretch::Expanding == i.first->getHStretch())
                {
                    columns[i.second.column] = true;
                }
            }
        }
    }

    void GridLayout::Private::getVisible(
        int& rows,
        int& columns) const
    {
        rows = 0;
        columns = 0;
        std::vector<bool> rowsVisible;
        std::vector<bool> columnsVisible;
        getVisible(rowsVisible, columnsVisible);
        for (bool i : rowsVisible)
        {
            if (i)
            {
                ++rows;
            }
        }
        for (bool i : columnsVisible)
        {
            if (i)
            {
                ++columns;
            }
        }
    }

    void GridLayout::Private::getVisible(
        std::vector<bool>& rows,
        std::vector<bool>& columns) const
    {
        const GridPos size = getSize();
        rows = std::vector<bool>(size.row, false);
        columns = std::vector<bool>(size.column, false);
        for (const auto& i : gridPos)
        {
            const bool visible = i.first->isVisible(false);
            rows[i.second.row] = rows[i.second.row] || visible;
            columns[i.second.column] = columns[i.second.column] || visible;
        }
    }
}