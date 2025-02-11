// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <glTest/WindowTest.h>

#include <dtk/gl/Window.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::gl;

namespace dtk
{
    namespace gl_test
    {
        WindowTest::WindowTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::gl_test::WindowTest")
        {}

        WindowTest::~WindowTest()
        {}

        std::shared_ptr<WindowTest> WindowTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<WindowTest>(new WindowTest(context));
        }
        
        void WindowTest::run()
        {
            if (auto context = _context.lock())
            {
                Size2I size(1024, 1024);
                auto window = Window::create(context, "WindowTest", size);
                DTK_ASSERT(window->getGLFW());
                DTK_ASSERT(size == window->getSize());                
                _print(Format("Frame buffer size: {0}").arg(window->getFrameBufferSize()));
                _print(Format("Content scale: {0}").arg(window->getContentScale()));
                _print(Format("Screen: {0}").arg(window->getScreen()));
                _print(Format("Full screen: {0}").arg(window->isFullScreen()));
                _print(Format("Float on top: {0}").arg(window->isFloatOnTop()));

                window->setSizeCallback([](const Size2I&){});
                window->setFrameBufferSizeCallback([](const Size2I&){});
                window->setContentScaleCallback([](const V2F&){});
                window->setRefreshCallback([]{});
                window->setCursorEnterCallback([](bool){});
                window->setCursorPosCallback([](const V2F&){});
                window->setButtonCallback([](int, int, int){});
                window->setScrollCallback([](const V2F&){});
                window->setKeyCallback([](int, int, int, int){});
                window->setCharCallback([](unsigned int){});
                window->setDropCallback([](int, const char**){});

                size = Size2I(512, 512);
                window->setSize(size);
                window->hide();
                window->show();
                window->setFullScreen(true);
                window->setFullScreen(true);
                window->setFullScreen(false);
                window->setFloatOnTop(true);
                window->setFloatOnTop(true);
                window->setFloatOnTop(false);
                window->makeCurrent();
                window->swap();
                window->doneCurrent();
            }
            if (auto context = _context.lock())
            {
                try
                {
                    auto window = Window::create(context, "WindowTest", Size2I(0, 0));
                    DTK_ASSERT(false);
                }
                catch (const std::exception&)
                {}
            }
        }
    }
}

