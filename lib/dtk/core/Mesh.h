// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Box.h>

#include <array>
#include <cstddef>
#include <vector>

namespace dtk
{
    //! \name Triangle Meshes
    ///@{

    //! Two-dimensional vertex.
    struct Vertex2
    {
        Vertex2() = default;
        constexpr Vertex2(size_t v, size_t t = 0, size_t c = 0);

        size_t v = 0;
        size_t t = 0;
        size_t c = 0;
    };

    //! Three-dimensional vertex.
    struct Vertex3
    {
        Vertex3() = default;
        constexpr Vertex3(size_t v, size_t t = 0, size_t n = 0, size_t c = 0);

        size_t v = 0;
        size_t t = 0;
        size_t n = 0;
        size_t c = 0;
    };

    //! Two-dimensional triangle.
    struct Triangle2
    {
        std::array<Vertex2, 3> v;
    };

    //! Three-dimensional triangle.
    struct Triangle3
    {
        std::array<Vertex3, 3> v;
    };

    //! Two-dimensional triangle mesh.
    template<typename T>
    struct TriangleMesh2
    {
        std::vector<Vector<2, T> > v;
        std::vector<Vector<4, T> > c;
        std::vector<Vector<2, T> > t;
        std::vector<Triangle2> triangles;
    };

    //! Three-dimensional triangle mesh.
    template<typename T>
    struct TriangleMesh3
    {
        std::vector<Vector<3, T> > v;
        std::vector<Vector<4, T> > c;
        std::vector<Vector<2, T> > t;
        std::vector<Vector<3, T> > n;
        std::vector<Triangle3> triangles;
    };

    typedef TriangleMesh2<float> TriMesh2F;
    typedef TriangleMesh3<float> TriMesh3F;

    //! Edge function.
    float edge(const V2F& p, const V2F& v0, const V2F& v1);
        
    //! Create a mesh from a box.
    TriMesh2F mesh(const Box2I&, bool flipV = false);

    //! Create a mesh from a box.
    TriMesh2F mesh(const Box2F&, bool flipV = false);
        
    ///@}
}

#include <dtk/core/MeshInline.h>
