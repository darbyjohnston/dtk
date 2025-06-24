// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/gl/Init.h>

#include <feather-tk/gl/GL.h>
#include <feather-tk/gl/System.h>

#include <feather-tk/core/Context.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace feather_tk
{
    namespace gl
    {
        void init(const std::shared_ptr<Context>& context)
        {
            if (!context->getSystem<System>())
            {
                context->addSystem(System::create(context));
            }
        }

        void initGLAD()
        {
#if defined(FEATHER_TK_API_GL_4_1)
            gladLoaderLoadGL();
#elif defined(FEATHER_TK_API_GLES_2)
            gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
#endif // FEATHER_TK_API_GL_4_1
        }
    }
}
