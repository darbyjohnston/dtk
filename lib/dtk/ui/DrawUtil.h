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
        TriMesh2F rect(
            const Box2I&,
            int cornerRadius = 0,
            size_t resolution = 8);

        //! Create a mesh for drawing a circle.
        TriMesh2F circle(
            const V2I&,
            int radius,
            size_t resolution = 120);

        //! Create a mesh for drawing a border.
        TriMesh2F border(
            const Box2I&,
            int width,
            int radius = 0,
            size_t resolution = 8);

        //! Create a mesh for drawing a shadow.
        TriMesh2F shadow(
            const Box2I&,
            int cornerRadius,
            const float alpha = .2F,
            size_t resolution = 8);

        //! Create a mesh for drawing checkers.
        TriMesh2F checkers(
            const Box2I&,
            const Color4F& color0,
            const Color4F& color1,
            const Size2I& checkerSize);
        
        ///@}
    }
}
