// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/gl/System.h>

#include <dtk/gl/GL.h>

#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>

namespace dtk
{
    namespace gl
    {
        namespace
        {
            void glfwErrorCallback(int, const char* description)
            {
                std::cerr << "GLFW ERROR: " << description << std::endl;
            }
        }
        
        struct System::Private
        {
            bool glfwInit = false;
        };
        
        System::System(const std::shared_ptr<Context>& context) :
            ISystem(context, "dtk::gl::System"),
            _p(new Private)
        {
            DTK_P();

            // Initialize GLFW.
            glfwSetErrorCallback(glfwErrorCallback);
            int glfwMajor = 0;
            int glfwMinor = 0;
            int glfwRevision = 0;
            glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);
            if (!glfwInit())
            {
                throw std::runtime_error("Cannot initialize GLFW");
            }
            p.glfwInit = true;
            if (auto logSystem = context->getSystem<LogSystem>())
            {
                logSystem->print(
                    "dtk::gl::System",
                    Format("GLFW version: {0}.{1}.{2}").
                    arg(glfwMajor).
                    arg(glfwMinor).
                    arg(glfwRevision));
            }
        }

        System::~System()
        {
            DTK_P();
            if (p.glfwInit)
            {
                glfwTerminate();
            }
        }

        std::shared_ptr<System> System::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<System>(new System(context));
        }
    }
}
