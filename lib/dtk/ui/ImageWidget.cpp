// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/ImageWidget.h>

#include <dtk/ui/LayoutUtil.h>

#include <dtk/core/String.h>

#include <optional>

namespace dtk
{
    struct ImageWidget::Private
    {
        std::shared_ptr<Image> image;
        SizeRole marginRole = SizeRole::None;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
        };
        SizeData size;
    };

    void ImageWidget::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::ImageWidget", parent);
        setHAlign(HAlign::Left);
        setVAlign(VAlign::Center);
    }

    ImageWidget::ImageWidget() :
        _p(new Private)
    {}

    ImageWidget::~ImageWidget()
    {}

    std::shared_ptr<ImageWidget> ImageWidget::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<ImageWidget>(new ImageWidget);
        out->_init(context, parent);
        return out;
    }

    const std::shared_ptr<Image>& ImageWidget::getImage() const
    {
        return _p->image;
    }

    void ImageWidget::setImage(const std::shared_ptr<Image>& value)
    {
        DTK_P();
        if (value == p.image)
            return;
        p.image = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    SizeRole ImageWidget::getMarginRole() const
    {
        return _p->marginRole;
    }

    void ImageWidget::setMarginRole(SizeRole value)
    {
        DTK_P();
        if (value == p.marginRole)
            return;
        p.marginRole = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void ImageWidget::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(p.marginRole, event.displayScale);
        }

        Size2I sizeHint;
        if (p.image)
        {
            sizeHint.w = p.image->getWidth();
            sizeHint.h = p.image->getHeight();
        }
        sizeHint = sizeHint + p.size.margin * 2;
        _setSizeHint(sizeHint);
    }

    void ImageWidget::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        if (p.image)
        {
            const Box2I g = margin(getGeometry(), -p.size.margin);
            const Size2I& size = p.image->getSize();
            event.render->drawImage(
                p.image,
                Box2I(
                    g.x() + g.w() / 2 - size.w / 2,
                    g.y() + g.h() / 2 - size.h / 2,
                    size.w,
                    size.h));
        }
    }
}
