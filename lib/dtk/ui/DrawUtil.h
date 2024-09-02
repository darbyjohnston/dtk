// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Color.h>
#include <dtk/core/Image.h>
#include <dtk/core/Mesh.h>

namespace dtk
{
    namespace ui
    {
        //! \name Drawing
        ///@{
        
        //! Create a mesh for drawing a rectangle.
        core::TriMesh2F rect(
            const core::Box2I&,
            int cornerRadius = 0,
            size_t resolution = 8);

        //! Create a mesh for drawing a circle.
        core::TriMesh2F circle(
            const core::V2I&,
            int radius,
            size_t resolution = 120);

        //! Create a mesh for drawing a border.
        core::TriMesh2F border(
            const core::Box2I&,
            int width,
            int radius = 0,
            size_t resolution = 8);

        //! Create a mesh for drawing a shadow.
        core::TriMesh2F shadow(
            const core::Box2I&,
            int cornerRadius,
            const float alpha = .2F,
            size_t resolution = 8);

        //! Create a mesh for drawing checkers.
        core::TriMesh2F checkers(
            const core::Box2I&,
            const core::Color4F& color0,
            const core::Color4F& color1,
            const core::Size2I& checkerSize);
        
        ///@}
    }
}
