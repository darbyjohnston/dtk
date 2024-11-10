// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Icon.h>

#include <dtk/ui/LayoutUtil.h>

#include <dtk/core/String.h>

namespace dtk
{
    struct Icon::Private
    {
        std::string icon;
        float iconScale = 1.F;
        std::shared_ptr<Image> iconImage;
        SizeRole marginRole = SizeRole::None;

        struct SizeData
        {
            float displayScale = 0.F;
            int margin = 0;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
        };
        DrawData draw;
    };

    void Icon::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::Icon", parent);
        setHAlign(HAlign::Left);
    }

    Icon::Icon() :
        _p(new Private)
    {}

    Icon::~Icon()
    {}

    std::shared_ptr<Icon> Icon::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Icon>(new Icon);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<Icon> Icon::create(
        const std::shared_ptr<Context>& context,
        const std::string& icon,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setIcon(icon);
        return out;
    }

    const std::string& Icon::getIcon() const
    {
        return _p->icon;
    }

    void Icon::setIcon(const std::string& value)
    {
        DTK_P();
        if (value == p.icon)
            return;
        p.icon = value;
        p.iconImage.reset();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    SizeRole Icon::getMarginRole() const
    {
        return _p->marginRole;
    }

    void Icon::setMarginRole(SizeRole value)
    {
        DTK_P();
        if (value == p.marginRole)
            return;
        p.marginRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void Icon::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.draw.g = margin(value, -p.size.margin);
    }

    void Icon::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (event.displayScale != p.size.displayScale)
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(p.marginRole, p.size.displayScale);
        }

        if (event.displayScale != p.iconScale)
        {
            p.iconScale = event.displayScale;
            p.iconImage.reset();
        }
        if (!p.icon.empty() && !p.iconImage)
        {
            p.iconImage = event.iconSystem->get(p.icon, event.displayScale);
        }

        Size2I sizeHint;
        if (p.iconImage)
        {
            sizeHint.w = p.iconImage->getWidth();
            sizeHint.h = p.iconImage->getHeight();
        }
        _setSizeHint(sizeHint);
    }

    void Icon::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        if (p.iconImage)
        {
            const Size2I& iconSize = p.iconImage->getSize();
            event.render->drawImage(
                p.iconImage,
                Box2I(
                    p.draw.g.x() + p.draw.g.w() / 2 - iconSize.w / 2,
                    p.draw.g.y() + p.draw.g.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(ColorRole::Text));
        }
    }
}
