// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <glTest/OffscreenBufferTest.h>

#include <dtk/gl/OffscreenBuffer.h>
#include <dtk/gl/Window.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>

using namespace dtk::core;
using namespace dtk::gl;

namespace dtk
{
    namespace gl_test
    {
        OffscreenBufferTest::OffscreenBufferTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::gl_test::OffscreenBufferTest")
        {}

        OffscreenBufferTest::~OffscreenBufferTest()
        {}

        std::shared_ptr<OffscreenBufferTest> OffscreenBufferTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<OffscreenBufferTest>(new OffscreenBufferTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "OffscreenBufferTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
        }
        
        void OffscreenBufferTest::run()
        {
            _enums();
            _members();
            _functions();
            _operators();
        }
        
        void OffscreenBufferTest::_enums()
        {
            DTK_TEST_ENUM(OffscreenDepth);
            DTK_TEST_ENUM(OffscreenStencil);
            DTK_TEST_ENUM(OffscreenSampling);
        }
        
        void OffscreenBufferTest::_members()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);

                const Size2I size(1920, 1080);
                std::vector<OffscreenBufferOptions> optionsList;
                for (auto imageType : getImageTypeEnums())
                {
                    OffscreenBufferOptions options;
                    options.color = imageType;
                    optionsList.push_back(options);
                }
                for (auto depth : getOffscreenDepthEnums())
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.depth = depth;
                    optionsList.push_back(options);
                }
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.stencil = OffscreenStencil::_8;
                    optionsList.push_back(options);
                }
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.stencil = OffscreenStencil::_8;
                    options.depth = OffscreenDepth::_16;
                    optionsList.push_back(options);
                }
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.stencil = OffscreenStencil::_8;
                    options.depth = OffscreenDepth::_24;
                    optionsList.push_back(options);
                }
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.stencil = OffscreenStencil::_8;
                    options.depth = OffscreenDepth::_32;
                    optionsList.push_back(options);
                }
                for (auto sampling : getOffscreenSamplingEnums())
                {
                    OffscreenBufferOptions options;
                    options.color = offscreenColorDefault;
                    options.sampling = sampling;
                    optionsList.push_back(options);
                }
                for (const auto& options : optionsList)
                {
                    try
                    {
                        _print(Format("Offscreen buffer: color={0}, depth={1}, stencil={2}, sampling={3}").
                            arg(options.color).
                            arg(options.depth).
                            arg(options.stencil).
                            arg(options.sampling));
                        auto offscreen = OffscreenBuffer::create(size, options);
                        DTK_ASSERT(size == offscreen->getSize());
                        DTK_ASSERT(size.w == offscreen->getWidth());
                        DTK_ASSERT(size.h == offscreen->getHeight());
                        DTK_ASSERT(options == offscreen->getOptions());
                        DTK_ASSERT(offscreen->getID());
                        if (options.color != ImageType::None)
                        {
                            DTK_ASSERT(offscreen->getColorID());
                            offscreen->bind();
                        }
                    }
                    catch (const std::exception& e)
                    {
                        _error(e.what());
                    }
                }
            }
        }
        
        void OffscreenBufferTest::_functions()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);

                std::shared_ptr<OffscreenBuffer> buffer;
                Size2I size(1920, 1080);
                OffscreenBufferOptions options;
                options.color = offscreenColorDefault;
                bool create = doCreate(buffer, size, options);
                DTK_ASSERT(create);
                buffer = OffscreenBuffer::create(size, options);

                size = Size2I(1280, 960);
                create = doCreate(buffer, size, options);
                DTK_ASSERT(create);
                buffer = OffscreenBuffer::create(size, options);
                
                options.depth = offscreenDepthDefault;
                create = doCreate(buffer, size, options);
                DTK_ASSERT(create);
                buffer = OffscreenBuffer::create(size, options);
            }
        }
        
        void OffscreenBufferTest::_operators()
        {
            const OffscreenBufferOptions a;
            OffscreenBufferOptions b;
            DTK_ASSERT(a == b);
            b.color = offscreenColorDefault;
            DTK_ASSERT(a != b);
        }
    }
}

