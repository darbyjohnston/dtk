// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/ImageTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Image.h>

namespace dtk
{
    namespace core_test
    {
        ImageTest::ImageTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::ImageTest")
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
            DTK_TEST_ENUM(ImageType);
            DTK_TEST_ENUM(VideoLevels);
            DTK_TEST_ENUM(YUVCoefficients);
        }
        
        void ImageTest::_info()
        {
            {
                const ImageInfo info;
                DTK_ASSERT(!info.isValid());
                DTK_ASSERT(0 == info.getByteCount());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), ImageType::RGB_U8);
                DTK_ASSERT(info.isValid());
                DTK_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo info(1920, 1080, ImageType::RGB_U8);
                DTK_ASSERT(info.isValid());
                DTK_ASSERT(1920 * 1080 * 3 == info.getByteCount());
            }
            {
                const ImageInfo a;
                ImageInfo b;
                DTK_ASSERT(a == b);
                b.size.w = 1920;
                b.size.h = 1080;
                DTK_ASSERT(a != b);                
            }
        }
        
        void ImageTest::_members()
        {
            {
                auto image = Image::create(ImageInfo());
                DTK_ASSERT(!image->isValid());
            }
            {
                auto image = Image::create(Size2I(1920, 1080), ImageType::RGB_U8);
                DTK_ASSERT(image->isValid());                
            }
            {
                auto image = Image::create(1920, 1080, ImageType::RGB_U8);
                DTK_ASSERT(image->isValid());
            }
            {
                const ImageInfo info(Size2I(1920, 1080), ImageType::RGB_U8);
                auto image = Image::create(info);
                image->zero();
                DTK_ASSERT(info == image->getInfo());
                DTK_ASSERT(info.size == image->getSize());
                DTK_ASSERT(info.size.w == image->getWidth());
                DTK_ASSERT(info.size.h == image->getHeight());
                const float aspect = image->getAspect();
                DTK_ASSERT(info.type == image->getType());
                DTK_ASSERT(image->isValid());
                ImageTags tags;
                tags["Layer"] = "1";
                image->setTags(tags);
                DTK_ASSERT(tags == image->getTags());
                DTK_ASSERT(1920 * 1080 * 3 == image->getByteCount());
                DTK_ASSERT(image->getData());
                const std::shared_ptr<const Image> image2 = image;
                DTK_ASSERT(image2->getData());
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

