// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Box.h>
#include <feather-tk/core/Util.h>

#include <memory>

namespace feather_tk
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
        FEATHER_TK_PRIVATE();
    };

    //! Set and restore the viewport.
    class ViewportState
    {
    public:
        ViewportState(const std::shared_ptr<IRender>&);

        ~ViewportState();

    private:
        FEATHER_TK_PRIVATE();
    };

    //! Set and restore whether the clipping rectangle is enabled.
    class ClipRectEnabledState
    {
    public:
        ClipRectEnabledState(const std::shared_ptr<IRender>&);

        ~ClipRectEnabledState();

    private:
        FEATHER_TK_PRIVATE();
    };

    //! Set and restore the clipping rectangle.
    class ClipRectState
    {
    public:
        ClipRectState(const std::shared_ptr<IRender>&);

        ~ClipRectState();

        const Box2I& getClipRect() const;

    private:
        FEATHER_TK_PRIVATE();
    };

    //! Set and restore the transform.
    class TransformState
    {
    public:
        TransformState(const std::shared_ptr<IRender>&);

        ~TransformState();

    private:
        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
