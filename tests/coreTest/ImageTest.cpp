// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/ImageTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Image.h>

namespace feather_tk
{
    namespace core_test
    {
        ImageTest::ImageTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::ImageTest")
        {}

        ImageTest::~ImageTest()
        {}

        std::shared_ptr<ImageTest> ImageTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageTest>(new ImageTest(context));
        }
        
        void ImageTest::run()
        {
            _enums();
            _info();
            _members();
            _functions();
        }
        
        void ImageTest::_enums()
        {
            FEATHER_TK_TEST_ENUM(ImageType);
            FEATHER_TK_TEST_ENUM(VideoLevels);
            FEATHER_TK_TEST_ENUM(YUVCoefficients);
        }
        
        void ImageTest::_info()
        {
            {
                const ImageInfo info;
                FEATHER_TK_ASSERT(!info.isValid());
                FEATHER_TK_ASSERT(0 == info.getByteCount());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), ImageType::RGB_U8);
                FEATHER_TK_ASSERT(info.isValid());
                FEATHER_TK_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo info(1920, 1080, ImageType::RGB_U8);
                FEATHER_TK_ASSERT(info.isValid());
                FEATHER_TK_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo a;
                ImageInfo b;
                FEATHER_TK_ASSERT(a == b);
                b.size.w = 1920;
                b.size.h = 1080;
                FEATHER_TK_ASSERT(a != b);                
            }
        }
        
        void ImageTest::_members()
        {
            {
                auto image = Image::create(ImageInfo());
                FEATHER_TK_ASSERT(!image->isValid());
            }
            {
                auto image = Image::create(Size2I(1920, 1080), ImageType::RGB_U8);
                FEATHER_TK_ASSERT(image->isValid());                
            }
            {
                auto image = Image::create(1920, 1080, ImageType::RGB_U8);
                FEATHER_TK_ASSERT(image->isValid());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), ImageType::RGB_U8);
                auto image = Image::create(info);
                image->zero();
                FEATHER_TK_ASSERT(info == image->getInfo());
                FEATHER_TK_ASSERT(info.size == image->getSize());
                FEATHER_TK_ASSERT(info.size.w == image->getWidth());
                FEATHER_TK_ASSERT(info.size.h == image->getHeight());
                const float aspect = image->getAspect();
                FEATHER_TK_ASSERT(info.type == image->getType());
                FEATHER_TK_ASSERT(image->isValid());
                ImageTags tags;
                tags["Layer"] = "1";
                image->setTags(tags);
                FEATHER_TK_ASSERT(tags == image->getTags());
                FEATHER_TK_ASSERT(1920 * 1080 * 3 == image->getByteCount());
                FEATHER_TK_ASSERT(image->getData());
                const std::shared_ptr<const Image> image2 = image;
                FEATHER_TK_ASSERT(image2->getData());
            }
        }
        
        void ImageTest::_functions()
        {
            for (auto i : getImageTypeEnums())
            {
                _print(Format("{0}: channels={1}, bitDepth={2}").
                    arg(i).
                    arg(getChannelCount(i)).
                    arg(getBitDepth(i)));
            }
            for (auto i : getYUVCoefficientsEnums())
            {
                _print(Format("{0}: {1}").
                    arg(i).
                    arg(getYUVCoefficients(i)));
            }
        }
    }
}

