// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/MeshTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Mesh.h>

namespace dtk
{
    namespace core_test
    {
        MeshTest::MeshTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::MeshTest")
        {}

        MeshTest::~MeshTest()
        {}

        std::shared_ptr<MeshTest> MeshTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MeshTest>(new MeshTest(context));
        }
        
        void MeshTest::run()
        {
            _members();
            _functions();
        }
        
        void MeshTest::_members()
        {
            {
                const Vertex2 v;
                DTK_ASSERT(0 == v.v);
                DTK_ASSERT(0 == v.t);
                DTK_ASSERT(0 == v.c);
            }
            {
                const Vertex2 v(1, 2, 3);
                DTK_ASSERT(1 == v.v);
                DTK_ASSERT(2 == v.t);
                DTK_ASSERT(3 == v.c);
            }
            {
                const Vertex3 v;
                DTK_ASSERT(0 == v.v);
                DTK_ASSERT(0 == v.t);
                DTK_ASSERT(0 == v.n);
                DTK_ASSERT(0 == v.c);
            }
            {
                const Vertex3 v(1, 2, 3, 4);
                DTK_ASSERT(1 == v.v);
                DTK_ASSERT(2 == v.t);
                DTK_ASSERT(3 == v.n);
                DTK_ASSERT(4 == v.c);
            }
        }
        
        void MeshTest::_functions()
        {
            const float e = edge(
                V2F(0.F, 1.F),
                V2F(1.F, 0.F),
                V2F(1.F, 1.F));
            const TriMesh2F m = mesh(Box2I(0, 1, 2, 3));
            const TriMesh2F m1 = mesh(Box2F(0.F, 1.F, 2.F, 3.F));
        }
    }
}

