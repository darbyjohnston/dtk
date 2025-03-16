// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Spacer.h>

#include <optional>

namespace dtk
{
    struct Spacer::Private
    {
        Orientation orientation = Orientation::Horizontal;
        SizeRole spacingRole = SizeRole::Spacing;

        struct SizeData
        {
            std::optional<float> displayScale;
            int size = 0;
        };
        SizeData size;
    };

    void Spacer::_init(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::Spacer", parent);
        DTK_P();
        p.orientation = orientation;
    }

    Spacer::Spacer() :
        _p(new Private)
    {}

    Spacer::~Spacer()
    {}

    std::shared_ptr<Spacer> Spacer::create(
        const std::shared_ptr<Context>& context,
        Orientation orientation,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<Spacer>(new Spacer);
        out->_init(context, orientation, parent);
        return out;
    }

    SizeRole Spacer::getSpacingRole() const
    {
        return _p->spacingRole;
    }

    void Spacer::setSpacingRole(SizeRole value)
    {
        DTK_P();
        if (value == p.spacingRole)
            return;
        p.spacingRole = value;
        p.size.displayScale.reset();
        _setSizeUpdate();
    }

    void Spacer::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.size = event.style->getSizeRole(p.spacingRole, event.displayScale);
        }

        Size2I sizeHint;
        switch (p.orientation)
        {
        case Orientation::Horizontal:
            sizeHint.w = p.size.size;
            break;
        case Orientation::Vertical:
            sizeHint.h = p.size.size;
            break;
        default: break;
        }
        _setSizeHint(sizeHint);
    }
}