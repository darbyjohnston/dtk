// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/gl/Window.h>

#include <dtk/gl/GL.h>
#include <dtk/gl/Init.h>

#include <dtk/core/Box.h>
#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/LogSystem.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <vector>

namespace dtk
{
    namespace gl
    {
        namespace
        {
#if defined(dtk_API_GL_4_1_Debug)
            void APIENTRY glDebugOutput(
                GLenum         source,
                GLenum         type,
                GLuint         id,
                GLenum         severity,
                GLsizei        length,
                const GLchar*  message,
                const void*    userParam)
            {
                switch (severity)
                {
                case GL_DEBUG_SEVERITY_HIGH:
                    std::cerr << "GL HIGH: " << message << std::endl;
                    break;
                case GL_DEBUG_SEVERITY_MEDIUM:
                    std::cerr << "GL MEDIUM: " << message << std::endl;
                    break;
                case GL_DEBUG_SEVERITY_LOW:
                    std::cerr << "GL LOW: " << message << std::endl;
                    break;
                    //case GL_DEBUG_SEVERITY_NOTIFICATION:
                    //    std::cerr << "GL NOTIFICATION: " << message << std::endl;
                    //    break;
                default: break;
                }
            }
#endif // dtk_API_GL_4_1_Debug
        }

        struct Window::Private
        {
            std::weak_ptr<Context> context;
            GLFWwindow* glfwWindow = nullptr;
            bool gladInit = true;
            Size2I size;
            V2I pos;
            Size2I frameBufferSize;
            V2F contentScale = V2F(1.F, 1.F);
            bool fullScreen = false;
            Size2I restoreSize;
            bool floatOnTop = false;

            std::function<void(const Size2I&)> sizeCallback;
            std::function<void(const Size2I&)> frameBufferSizeCallback;
            std::function<void(const V2F&)> contentScaleCallback;
            std::function<void(void)> refreshCallback;
            std::function<void(bool)> cursorEnterCallback;
            std::function<void(const V2F&)> cursorPosCallback;
            std::function<void(int, int, int)> buttonCallback;
            std::function<void(const V2F&)> scrollCallback;
            std::function<void(int, int, int, int)> keyCallback;
            std::function<void(unsigned int)> charCallback;
            std::function<void(int, const char**)> dropCallback;
            std::function<void(void)> closeCallback;
        };
        
        Window::Window(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size,
            int options,
            const std::shared_ptr<Window>& share) :
            _p(new Private)
        {
            DTK_P();

            p.context = context;

#if defined(dtk_API_GL_4_1)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#elif defined(dtk_API_GLES_2)
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
#endif // dtk_API_GL_4_1
            glfwWindowHint(GLFW_VISIBLE,
                options & static_cast<int>(WindowOptions::Visible));
            glfwWindowHint(GLFW_DOUBLEBUFFER,
                options & static_cast<int>(WindowOptions::DoubleBuffer));
#if defined(dtk_API_GL_4_1_Debug)
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // dtk_API_GL_4_1_Debug
            p.glfwWindow = glfwCreateWindow(
                size.w,
                size.h,
                name.c_str(),
                nullptr,
                share ? share->getGLFW() : nullptr);
            if (!p.glfwWindow)
            {
                throw std::runtime_error("Cannot create window");
            }

            glfwGetWindowSize(p.glfwWindow, &p.size[0], &p.size[1]);
            glfwGetFramebufferSize(p.glfwWindow, &p.frameBufferSize[0], &p.frameBufferSize[1]);
            glfwGetWindowContentScale(p.glfwWindow, &p.contentScale[0], &p.contentScale[1]);

            glfwSetWindowUserPointer(p.glfwWindow, this);
            glfwSetWindowSizeCallback(p.glfwWindow, _sizeCallback);
            glfwSetFramebufferSizeCallback(p.glfwWindow, _frameBufferSizeCallback);
            glfwSetWindowContentScaleCallback(p.glfwWindow, _windowContentScaleCallback);
            glfwSetWindowRefreshCallback(p.glfwWindow, _windowRefreshCallback);
            glfwSetCursorEnterCallback(p.glfwWindow, _cursorEnterCallback);
            glfwSetCursorPosCallback(p.glfwWindow, _cursorPosCallback);
            glfwSetMouseButtonCallback(p.glfwWindow, _mouseButtonCallback);
            glfwSetScrollCallback(p.glfwWindow, _scrollCallback);
            glfwSetKeyCallback(p.glfwWindow, _keyCallback);
            glfwSetCharCallback(p.glfwWindow, _charCallback);
            glfwSetDropCallback(p.glfwWindow, _dropCallback);
            glfwSetWindowCloseCallback(p.glfwWindow, _closeCallback);

            if (options & static_cast<int>(WindowOptions::MakeCurrent))
            {
                makeCurrent();
            }

            const int glMajor = glfwGetWindowAttrib(p.glfwWindow, GLFW_CONTEXT_VERSION_MAJOR);
            const int glMinor = glfwGetWindowAttrib(p.glfwWindow, GLFW_CONTEXT_VERSION_MINOR);
            const int glRevision = glfwGetWindowAttrib(p.glfwWindow, GLFW_CONTEXT_REVISION);
            if (auto logSystem = context->getSystem<LogSystem>())
            {
                logSystem->print(
                    "dtk::gl::Window",
                    Format(
                        "New window:\n"
                        "    Size: {0}\n"
                        "    Frame buffer: {1}\n"
                        "    Content scale: {2}\n"
                        "    OpenGL version: {3}.{4}.{5}").
                    arg(p.size).
                    arg(p.frameBufferSize).
                    arg(p.contentScale).
                    arg(glMajor).
                    arg(glMinor).
                    arg(glRevision));
            }
        }
        
        Window::~Window()
        {
            DTK_P();
            if (p.glfwWindow)
            {
                glfwDestroyWindow(p.glfwWindow);
            }
        }

        std::shared_ptr<Window> Window::create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            const Size2I& size,
            int options,
            const std::shared_ptr<Window>& share)
        {
            return std::shared_ptr<Window>(new Window(context, name, size, options, share));
        }

        GLFWwindow* Window::getGLFW() const
        {
            return _p->glfwWindow;
        }

        const Size2I& Window::getSize() const
        {
            return _p->size;
        }

        void Window::setSize(const Size2I& value)
        {
            glfwSetWindowSize(_p->glfwWindow, value[0], value[1]);
        }

        const Size2I& Window::getFrameBufferSize() const
        {
            return _p->frameBufferSize;
        }

        const V2F& Window::getContentScale() const
        {
            return _p->contentScale;
        }

        void Window::show()
        {
            glfwShowWindow(_p->glfwWindow);
        }

        void Window::hide()
        {
            glfwHideWindow(_p->glfwWindow);
        }

        void Window::makeCurrent()
        {
            DTK_P();
            glfwMakeContextCurrent(p.glfwWindow);
            if (p.gladInit)
            {
                p.gladInit = false;
                initGLAD();
#if defined(dtk_API_GL_4_1_Debug)
                GLint flags = 0;
                glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
                if (flags & static_cast<GLint>(GL_CONTEXT_FLAG_DEBUG_BIT))
                {
                    glEnable(GL_DEBUG_OUTPUT);
                    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
                    glDebugMessageCallback(glDebugOutput, nullptr);
                    glDebugMessageControl(
                        static_cast<GLenum>(GL_DONT_CARE),
                        static_cast<GLenum>(GL_DONT_CARE),
                        static_cast<GLenum>(GL_DONT_CARE),
                        0,
                        nullptr,
                        GL_TRUE);
                }
#endif // dtk_API_GL_4_1_Debug
            }
        }

        void Window::doneCurrent()
        {
            glfwMakeContextCurrent(nullptr);
        }

        int Window::getScreen() const
        {
            DTK_P();

            V2I windowPos;
            Size2I windowSize;
            glfwGetWindowPos(p.glfwWindow, &windowPos[0], &windowPos[1]);
            glfwGetWindowSize(_p->glfwWindow, &windowSize[0], &windowSize[1]);
            const Box2I windowBox(windowPos, windowSize);

            struct MonitorData
            {
                int index = 0;
                int width = 0;
                int height = 0;
                int refreshRate = 0;
                Box2I intersect;
            };
            std::vector<MonitorData> monitorData;
            int glfwMonitorsCount = 0;
            GLFWmonitor** glfwMonitors = glfwGetMonitors(&glfwMonitorsCount);
            for (int i = 0; i < glfwMonitorsCount; ++i)
            {
                Size2I monitorPos;
                glfwGetMonitorPos(glfwMonitors[i], &monitorPos[0], &monitorPos[1]);
                const GLFWvidmode* glfwVidmode = glfwGetVideoMode(glfwMonitors[i]);
                const Box2I monitorBox(
                    monitorPos[0],
                    monitorPos[1],
                    glfwVidmode->width,
                    glfwVidmode->height);
                monitorData.push_back({
                    i,
                    glfwVidmode->width,
                    glfwVidmode->height,
                    glfwVidmode->refreshRate,
                    intersect(windowBox, monitorBox)
                    });
            }
            std::sort(
                monitorData.begin(),
                monitorData.end(),
                [](const MonitorData& a, const MonitorData& b)
                {
                    return area(a.intersect) > area(b.intersect);
                });

            return !monitorData.empty() ? monitorData.front().index : -1;
        }

        bool Window::isFullScreen() const
        {
            return _p->fullScreen;
        }

        void Window::setFullScreen(bool value, int screen)
        {
            DTK_P();
            if (value == p.fullScreen)
                return;
            p.fullScreen = value;
            if (p.fullScreen)
            {
                V2I windowPos;
                Size2I windowSize;
                glfwGetWindowPos(p.glfwWindow, &windowPos[0], &windowPos[1]);
                glfwGetWindowSize(_p->glfwWindow, &windowSize[0], &windowSize[1]);
                const Box2I windowBox(windowPos, windowSize);
                p.pos = windowPos;
                p.restoreSize = windowSize;

                int glfwMonitorsCount = 0;
                GLFWmonitor** glfwMonitors = glfwGetMonitors(&glfwMonitorsCount);
                const int monitor = screen < 0 ? getScreen() : screen;
                if (monitor >= 0 && monitor < glfwMonitorsCount)
                {
                    const GLFWvidmode* glfwVidmode = glfwGetVideoMode(glfwMonitors[monitor]);
                    glfwSetWindowMonitor(
                        p.glfwWindow,
                        glfwMonitors[monitor],
                        0,
                        0,
                        glfwVidmode->width,
                        glfwVidmode->height,
                        glfwVidmode->refreshRate);
                }
            }
            else
            {
                glfwSetWindowMonitor(
                    p.glfwWindow,
                    nullptr,
                    p.pos[0],
                    p.pos[1],
                    p.restoreSize[0],
                    p.restoreSize[1],
                    0);
            }
        }

        bool Window::isFloatOnTop() const
        {
            return _p->floatOnTop;
        }

        void Window::setFloatOnTop(bool value)
        {
            DTK_P();
            if (value == p.floatOnTop)
                return;
            p.floatOnTop = value;
            glfwSetWindowAttrib(
                p.glfwWindow,
                GLFW_FLOATING,
                p.floatOnTop ? GLFW_TRUE : GLFW_FALSE);
        }

        void Window::swap()
        {
            glfwSwapBuffers(_p->glfwWindow);
        }

        void Window::setSizeCallback(
            const std::function<void(const Size2I&)>& value)
        {
            _p->sizeCallback = value;
        }

        void Window::setFrameBufferSizeCallback(
            const std::function<void(const Size2I&)>& value)
        {
            _p->frameBufferSizeCallback = value;
        }

        void Window::setContentScaleCallback(
            const std::function<void(const V2F&)>& value)
        {
            _p->contentScaleCallback = value;
        }

        void Window::setRefreshCallback(const std::function<void(void)>& value)
        {
            _p->refreshCallback = value;
        }

        void Window::setCursorEnterCallback(const std::function<void(bool)>& value)
        {
            _p->cursorEnterCallback = value;
        }

        void Window::setCursorPosCallback(const std::function<void(const V2F&)>& value)
        {
            _p->cursorPosCallback = value;
        }

        void Window::setButtonCallback(const std::function<void(int, int, int)>& value)
        {
            _p->buttonCallback = value;
        }

        void Window::setScrollCallback(const std::function<void(const V2F&)>& value)
        {
            _p->scrollCallback = value;
        }

        void Window::setKeyCallback(const std::function<void(int, int, int, int)>& value)
        {
            _p->keyCallback = value;
        }

        void Window::setCharCallback(const std::function<void(unsigned int)>& value)
        {
            _p->charCallback = value;
        }

        void Window::setDropCallback(const std::function<void(int, const char**)>& value)
        {
            _p->dropCallback = value;
        }

        void Window::setCloseCallback(const std::function<void(void)>& value)
        {
            _p->closeCallback = value;
        }

        void Window::_sizeCallback(GLFWwindow* glfwWindow, int w, int h)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            window->_p->size[0] = w;
            window->_p->size[1] = h;
            if (window->_p->sizeCallback)
            {
                window->_p->sizeCallback(window->_p->size);
            }
        }

        void Window::_frameBufferSizeCallback(GLFWwindow* glfwWindow, int w, int h)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            window->_p->frameBufferSize[0] = w;
            window->_p->frameBufferSize[1] = h;
            if (window->_p->frameBufferSizeCallback)
            {
                window->_p->frameBufferSizeCallback(window->_p->frameBufferSize);
            }
        }

        void Window::_windowContentScaleCallback(GLFWwindow* glfwWindow, float x, float y)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            window->_p->contentScale[0] = x;
            window->_p->contentScale[1] = y;
            if (window->_p->contentScaleCallback)
            {
                window->_p->contentScaleCallback(window->_p->contentScale);
            }
        }

        void Window::_windowRefreshCallback(GLFWwindow* glfwWindow)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->refreshCallback)
            {
                window->_p->refreshCallback();
            }
        }

        void Window::_cursorEnterCallback(GLFWwindow* glfwWindow, int value)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->cursorEnterCallback)
            {
                window->_p->cursorEnterCallback(GLFW_TRUE == value);
            }
        }

        void Window::_cursorPosCallback(GLFWwindow* glfwWindow, double x, double y)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->cursorPosCallback)
            {
                window->_p->cursorPosCallback(V2F(x, y));
            }
        }

        void Window::_mouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->buttonCallback)
            {
                window->_p->buttonCallback(button, action, mods);
            }
        }

        void Window::_scrollCallback(GLFWwindow* glfwWindow, double x, double y)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->scrollCallback)
            {
                window->_p->scrollCallback(V2F(x, y));
            }
        }

        void Window::_keyCallback(GLFWwindow* glfwWindow, int key, int scanCode, int action, int mods)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->keyCallback)
            {
                window->_p->keyCallback(key, scanCode, action, mods);
            }
        }

        void Window::_charCallback(GLFWwindow* glfwWindow, unsigned int c)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->charCallback)
            {
                window->_p->charCallback(c);
            }
        }

        void Window::_dropCallback(GLFWwindow* glfwWindow, int count, const char** paths)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            if (window->_p->dropCallback)
            {
                window->_p->dropCallback(count, paths);
            }
        }

        void Window::_closeCallback(GLFWwindow* glfwWindow)
        {
            Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
            glfwSetWindowShouldClose(window->getGLFW(), 0);
            glfwHideWindow(window->getGLFW());
            if (window->_p->closeCallback)
            {
                window->_p->closeCallback();
            }
        }
    }
}
