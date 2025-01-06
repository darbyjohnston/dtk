// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Box.h>
#include <dtk/core/Util.h>

#include <memory>

namespace dtk
{
    class IRender;

    //! \name Rendering
    ///@{
        
    //! Set and restore the render size.
    class RenderSizeState
    {
    public:
        RenderSizeState(const std::shared_ptr<IRender>&);

        ~RenderSizeState();

    private:
        DTK_PRIVATE();
    };

    //! Set and restore the viewport.
    class ViewportState
    {
    public:
        ViewportState(const std::shared_ptr<IRender>&);

        ~ViewportState();

    private:
        DTK_PRIVATE();
    };

    //! Set and restore whether the clipping rectangle is enabled.
    class ClipRectEnabledState
    {
    public:
        ClipRectEnabledState(const std::shared_ptr<IRender>&);

        ~ClipRectEnabledState();

    private:
        DTK_PRIVATE();
    };

    //! Set and restore the clipping rectangle.
    class ClipRectState
    {
    public:
        ClipRectState(const std::shared_ptr<IRender>&);

        ~ClipRectState();

        const Box2I& getClipRect() const;

    private:
        DTK_PRIVATE();
    };

    //! Set and restore the transform.
    class TransformState
    {
    public:
        TransformState(const std::shared_ptr<IRender>&);

        ~TransformState();

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
