// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/Divider.h>

#include <optional>

namespace feather_tk
{
    struct Divider::Private
    {
        struct SizeData
        {
            std::optional<float> displayScale;
            int size = 0;
        };
        SizeData size;
    };

    void Divider::_init(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "feather_tk::Divider", parent);
        setBackgroundRole(ColorRole::Border);
        switch (orientation)
        {
        case Orientation::Horizontal:
            setVStretch(Stretch::Expanding);
            break;
        case Orientation::Vertical:
            setHStretch(Stretch::Expanding);
            break;
        default: break;
        }
    }

    Divider::Divider() :
        _p(new Private)
    {}

    Divider::~Divider()
    {}

    std::shared_ptr<Divider> Divider::create(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Divider>(new Divider);
        out->_init(context, orientation, parent);
        return out;
    }

    void Divider::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        FEATHER_TK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.size = event.style->getSizeRole(SizeRole::Border, event.displayScale);
        }

        _setSizeHint(Size2I(p.size.size, p.size.size));
    }
}