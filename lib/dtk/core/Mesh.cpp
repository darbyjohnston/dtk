// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/Mesh.h>

namespace dtk
{
    namespace core
    {
        TriMesh2F mesh(const Box2I& box, bool flipV)
        {
            TriMesh2F out;

            const auto& min = box.min;
            const auto& max = box.max;
            out.v.push_back(V2F(min.x, min.y));
            out.v.push_back(V2F(max.x + 1, min.y));
            out.v.push_back(V2F(max.x + 1, max.y + 1));
            out.v.push_back(V2F(min.x, max.y + 1));
            out.t.push_back(V2F(0.F, flipV ? 1.F : 0.F));
            out.t.push_back(V2F(1.F, flipV ? 1.F : 0.F));
            out.t.push_back(V2F(1.F, flipV ? 0.F : 1.F));
            out.t.push_back(V2F(0.F, flipV ? 0.F : 1.F));

            Triangle2 triangle;
            triangle.v[0].v = 1;
            triangle.v[1].v = 2;
            triangle.v[2].v = 3;
            triangle.v[0].t = 1;
            triangle.v[1].t = 2;
            triangle.v[2].t = 3;
            out.triangles.push_back(triangle);
            triangle.v[0].v = 3;
            triangle.v[1].v = 4;
            triangle.v[2].v = 1;
            triangle.v[0].t = 3;
            triangle.v[1].t = 4;
            triangle.v[2].t = 1;
            out.triangles.push_back(triangle);

            return out;
        }

        TriMesh2F mesh(const Box2F& box, bool flipV)
        {
            TriMesh2F out;

            const auto& min = box.min;
            const auto& max = box.max;
            out.v.push_back(V2F(min.x, min.y));
            out.v.push_back(V2F(max.x, min.y));
            out.v.push_back(V2F(max.x, max.y));
            out.v.push_back(V2F(min.x, max.y));
            out.t.push_back(V2F(0.F, flipV ? 1.F : 0.F));
            out.t.push_back(V2F(1.F, flipV ? 1.F : 0.F));
            out.t.push_back(V2F(1.F, flipV ? 0.F : 1.F));
            out.t.push_back(V2F(0.F, flipV ? 0.F : 1.F));

            Triangle2 triangle;
            triangle.v[0].v = 1;
            triangle.v[1].v = 2;
            triangle.v[2].v = 3;
            triangle.v[0].t = 1;
            triangle.v[1].t = 2;
            triangle.v[2].t = 3;
            out.triangles.push_back(triangle);
            triangle.v[0].v = 3;
            triangle.v[1].v = 4;
            triangle.v[2].v = 1;
            triangle.v[0].t = 3;
            triangle.v[1].t = 4;
            triangle.v[2].t = 1;
            out.triangles.push_back(triangle);

            return out;
        }
    }
}
