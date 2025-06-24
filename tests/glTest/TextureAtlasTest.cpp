// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <glTest/TextureAtlasTest.h>

#include <feather-tk/gl/TextureAtlas.h>
#include <feather-tk/gl/Window.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>

using namespace feather_tk::gl;

namespace feather_tk
{
    namespace gl_test
    {
        TextureAtlasTest::TextureAtlasTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::gl_test::TextureAtlasTest")
        {}

        TextureAtlasTest::~TextureAtlasTest()
        {}

        std::shared_ptr<TextureAtlasTest> TextureAtlasTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<TextureAtlasTest>(new TextureAtlasTest(context));
        }
        
        namespace
        {
            std::shared_ptr<Window> createWindow(
                const std::shared_ptr<Context>& context)
            {
                return Window::create(
                    context,
                    "TextureAtlasTest",
                    Size2I(100, 100),
                    static_cast<int>(WindowOptions::MakeCurrent));
            }
            
            std::string format(const TextureAtlasItem& item)
            {
                return Format(
                    "Item: size={0}, u={1}-{2}, v={3}-{4}").
                    arg(item.size).
                    arg(item.u.min()).
                    arg(item.u.max()).
                    arg(item.v.min()).
                    arg(item.v.max());
            }
        }
        
        void TextureAtlasTest::run()
        {
            if (auto context = _context.lock())
            {
                auto window = createWindow(context);
                
                auto atlas = TextureAtlas::create(
                    1024,
                    ImageType::L_U8,
                    ImageFilter::Linear,
                    0);
                FEATHER_TK_ASSERT(1024 == atlas->getSize());
                FEATHER_TK_ASSERT(ImageType::L_U8 == atlas->getType());
                FEATHER_TK_ASSERT(atlas->getTexture());
                
                for (size_t i = 0; i < 10; ++i)
                {
                    auto image = Image::create(512, 512, ImageType::L_U8);
                    TextureAtlasItem item;
                    FEATHER_TK_ASSERT(atlas->addItem(image, item));
                    FEATHER_TK_ASSERT(atlas->getItem(item.id, item));
                    _print(format(item));
                    _print(Format("Percentage: {0}").arg(atlas->getPercentageUsed()));
                }
            }
        }
    }
}

