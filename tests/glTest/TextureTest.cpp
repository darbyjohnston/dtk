// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <glTest/TextureTest.h>

#include <feather-tk/gl/Texture.h>
#include <feather-tk/gl/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

using namespace feather_tk::gl;

namespace feather_tk
{
    namespace gl_test
    {
        TextureTest::TextureTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::gl_test::TextureTest")
        {}

        TextureTest::~TextureTest()
        {}

        std::shared_ptr<TextureTest> TextureTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TextureTest>(new TextureTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "TextureTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
        }
        
        void TextureTest::run()
        {
            _members();
            _functions();
            _operators();
        }
        
        void TextureTest::_members()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
                
                struct Data
                {
                    ImageInfo info;
                    TextureOptions options;
                };
                std::vector<Data> dataList;
                for (auto imageType : getImageTypeEnums())
                {
                    dataList.push_back({
                        ImageInfo(1920, 1080, imageType),
                        TextureOptions() });
                }
                {
                    TextureOptions options;
                    options.filters.minify = ImageFilter::Nearest;
                    options.filters.magnify = ImageFilter::Nearest;
                    dataList.push_back({
                        ImageInfo(1920, 1080, ImageType::RGBA_U8),
                        options });
                }
                {
                    TextureOptions options;
                    options.pbo = true;
                    dataList.push_back({
                        ImageInfo(1920, 1080, ImageType::RGBA_U8),
                        options });
                }
                for (const auto& data : dataList)
                {
                    try
                    {
                        _print(Format("Texture: size={0} type={1}, minify={2}, magnify={3}, pbo={4}").
                            arg(data.info.size).
                            arg(data.info.type).
                            arg(data.options.filters.minify).
                            arg(data.options.filters.magnify).
                            arg(data.options.pbo));
                        auto texture = Texture::create(data.info, data.options);
                        FEATHER_TK_ASSERT(data.info == texture->getInfo());
                        FEATHER_TK_ASSERT(data.info.size == texture->getSize());
                        FEATHER_TK_ASSERT(data.info.size.w == texture->getWidth());
                        FEATHER_TK_ASSERT(data.info.size.h == texture->getHeight());
                        FEATHER_TK_ASSERT(data.info.type == texture->getType());
                        if (data.info.type != ImageType::None)
                        {
                            FEATHER_TK_ASSERT(texture->getID());
                            auto image = Image::create(data.info);
                            texture->copy(image);
                            texture->copy(image, 0, 0);
                            texture->copy(image->getData(), image->getInfo());
                            texture->bind();
                        }
                    }
                    catch (const std::exception& e)
                    {
                        _error(e.what());
                    }
                }
            }
        }
        
        void TextureTest::_functions()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
            }
        }
        
        void TextureTest::_operators()
        {
            {
                const TextureOptions a;
                TextureOptions b;
                FEATHER_TK_ASSERT(a == b);
                b.pbo = true;
                FEATHER_TK_ASSERT(a != b);
            }
        }
    }
}

