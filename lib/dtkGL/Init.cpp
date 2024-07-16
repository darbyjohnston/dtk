// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkGL/Init.h>

#include <dtkGL/GL.h>
#include <dtkGL/System.h>

#include <dtkCore/Context.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using namespace dtk::core;

namespace dtk
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
#if defined(dtk_API_GL_4_1)
            gladLoaderLoadGL();
#elif defined(dtk_API_GLES_2)
            gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress);
#endif // dtk_API_GL_4_1
        }
    }
}
