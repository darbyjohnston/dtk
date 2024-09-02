// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace dtk
{
    class Context;

    //! OpenGL support
    namespace gl
    {
        //! Initialize the library.
        void init(const std::shared_ptr<Context>&);

        //! Initialize GLAD.
        void initGLAD();
    }
}
