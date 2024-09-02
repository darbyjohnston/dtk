// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/RenderUtil.h>

#include <dtk/core/IRender.h>

namespace dtk
{
    struct RenderSizeState::Private
    {
        std::shared_ptr<IRender> render;
        Size2I size;
    };

    RenderSizeState::RenderSizeState(const std::shared_ptr<IRender>& render) :
        _p(new Private)
    {
        DTK_P();
        p.render = render;
        p.size = render->getRenderSize();
    }

    RenderSizeState::~RenderSizeState()
    {
        DTK_P();
        p.render->setRenderSize(p.size);
    }

    struct ViewportState::Private
    {
        std::shared_ptr<IRender> render;
        Box2I viewport;
    };

    ViewportState::ViewportState(const std::shared_ptr<IRender>& render) :
        _p(new Private)
    {
        DTK_P();
        p.render = render;
        p.viewport = render->getViewport();
    }

    ViewportState::~ViewportState()
    {
        DTK_P();
        p.render->setViewport(p.viewport);
    }

    struct ClipRectEnabledState::Private
    {
        std::shared_ptr<IRender> render;
        bool clipRectEnabled = false;
    };

    ClipRectEnabledState::ClipRectEnabledState(const std::shared_ptr<IRender>& render) :
        _p(new Private)
    {
        DTK_P();
        p.render = render;
        p.clipRectEnabled = render->getClipRectEnabled();
    }

    ClipRectEnabledState::~ClipRectEnabledState()
    {
        DTK_P();
        p.render->setClipRectEnabled(p.clipRectEnabled);
    }

    struct ClipRectState::Private
    {
        std::shared_ptr<IRender> render;
        Box2I clipRect;
    };

    ClipRectState::ClipRectState(const std::shared_ptr<IRender>& render) :
        _p(new Private)
    {
        DTK_P();
        p.render = render;
        p.clipRect = render->getClipRect();
    }

    ClipRectState::~ClipRectState()
    {
        DTK_P();
        p.render->setClipRect(p.clipRect);
    }

    const Box2I& ClipRectState::getClipRect() const
    {
        return _p->clipRect;
    }

    struct TransformState::Private
    {
        std::shared_ptr<IRender> render;
        M44F transform;
    };

    TransformState::TransformState(const std::shared_ptr<IRender>& render) :
        _p(new Private)
    {
        DTK_P();
        p.render = render;
        p.transform = render->getTransform();
    }

    TransformState::~TransformState()
    {
        DTK_P();
        p.render->setTransform(p.transform);
    }
}
