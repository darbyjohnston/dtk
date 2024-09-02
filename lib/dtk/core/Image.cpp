// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/Image.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <array>
#include <cstring>

namespace dtk
{
    namespace core
    {
        DTK_ENUM_IMPL(
            ImageType,
            "None",
            "L_U8",
            "L_U16",
            "L_U32",
            "L_F16",
            "L_F32",
            "LA_U8",
            "LA_U16",
            "LA_U32",
            "LA_F16",
            "LA_F32",
            "RGB_U8",
            "RGB_U10",
            "RGB_U16",
            "RGB_U32",
            "RGB_F16",
            "RGB_F32",
            "RGBA_U8",
            "RGBA_U16",
            "RGBA_U32",
            "RGBA_F16",
            "RGBA_F32",
            "YUV_420P_U8",
            "YUV_422P_U8",
            "YUV_444P_U8",
            "YUV_420P_U16",
            "YUV_422P_U16",
            "YUV_444P_U16",
            "ARGB_4444_Premult");

        int getChannelCount(ImageType value)
        {
            const std::array<int, static_cast<size_t>(ImageType::Count)> values =
            {
                0,
                1, 1, 1, 1, 1,
                2, 2, 2, 2, 2,
                3, 3, 3, 3, 3, 3,
                4, 4, 4, 4, 4,
                3, 3, 3,
                3, 3, 3,
                4
            };
            return values[static_cast<size_t>(value)];
        }

        int getBitDepth(ImageType value)
        {
            const std::array<int, static_cast<size_t>(ImageType::Count)> values =
            {
                0,
                8, 16, 32, 16, 32,
                8, 16, 32, 16, 32,
                8, 10, 16, 32, 16, 32,
                8, 16, 32, 16, 32,
                8, 8, 8,
                16, 16, 16,
                4
            };
            return values[static_cast<size_t>(value)];
        }

        DTK_ENUM_IMPL(
            YUVCoefficients,
            "REC709",
            "BT2020");

        V4F getYUVCoefficients(YUVCoefficients value)
        {
            const std::array<V4F, static_cast<size_t>(YUVCoefficients::Count)> data =
            {
                V4F(1.79274F, 2.1124F, .213242F, .532913F),
                V4F(1.67867F, 2.14177F, .187332F, .650421F)
            };
            return data[static_cast<size_t>(value)];
        }

        DTK_ENUM_IMPL(
            VideoLevels,
            "FullRange",
            "LegalRange");

        size_t ImageInfo::getByteCount() const
        {
            std::size_t out = 0;
            const size_t w = size.w;
            const size_t h = size.h;
            const size_t alignment = layout.alignment;
            switch (type)
            {
            case ImageType::L_U8:     out = getAlignedByteCount(w, alignment) * h; break;
            case ImageType::L_U16:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case ImageType::L_U32:    out = getAlignedByteCount(w * 4, alignment) * h; break;
            case ImageType::L_F16:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case ImageType::L_F32:    out = getAlignedByteCount(w * 4, alignment) * h; break;

            case ImageType::LA_U8:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case ImageType::LA_U16:   out = getAlignedByteCount(w * 2 * 2, alignment) * h; break;
            case ImageType::LA_U32:   out = getAlignedByteCount(w * 2 * 4, alignment) * h; break;
            case ImageType::LA_F16:   out = getAlignedByteCount(w * 2 * 2, alignment) * h; break;
            case ImageType::LA_F32:   out = getAlignedByteCount(w * 2 * 4, alignment) * h; break;

            case ImageType::RGB_U8:   out = getAlignedByteCount(w * 3, alignment) * h; break;
            case ImageType::RGB_U10:  out = getAlignedByteCount(w * 4, alignment) * h; break;
            case ImageType::RGB_U16:  out = getAlignedByteCount(w * 3 * 2, alignment) * h; break;
            case ImageType::RGB_U32:  out = getAlignedByteCount(w * 3 * 4, alignment) * h; break;
            case ImageType::RGB_F16:  out = getAlignedByteCount(w * 3 * 2, alignment) * h; break;
            case ImageType::RGB_F32:  out = getAlignedByteCount(w * 3 * 4, alignment) * h; break;

            case ImageType::RGBA_U8:  out = getAlignedByteCount(w * 4, alignment) * h; break;
            case ImageType::RGBA_U16: out = getAlignedByteCount(w * 4 * 2, alignment) * h; break;
            case ImageType::RGBA_U32: out = getAlignedByteCount(w * 4 * 4, alignment) * h; break;
            case ImageType::RGBA_F16: out = getAlignedByteCount(w * 4 * 2, alignment) * h; break;
            case ImageType::RGBA_F32: out = getAlignedByteCount(w * 4 * 4, alignment) * h; break;

            //! \todo Is YUV data aligned?
            case ImageType::YUV_420P_U8:  out = w * h + (w / 2 * h / 2) + (w / 2 * h / 2); break;
            case ImageType::YUV_422P_U8:  out = w * h + (w / 2 * h) + (w / 2 * h); break;
            case ImageType::YUV_444P_U8:  out = w * h * 3; break;
            case ImageType::YUV_420P_U16: out = (w * h + (w / 2 * h / 2) + (w / 2 * h / 2)) * 2; break;
            case ImageType::YUV_422P_U16: out = (w * h + (w / 2 * h) + (w / 2 * h)) * 2; break;
            case ImageType::YUV_444P_U16: out = (w * h * 3) * 2; break;

            case ImageType::ARGB_4444_Premult: out = w * h * 4 * 2; break;

            default: break;
            }
            return out;
        }
        
        Image::Image(const ImageInfo& info, uint8_t* externalData) :
            _info(info)
        {
            _byteCount = info.getByteCount();
            if (externalData)
            {
                _dataP = externalData;
            }
            else
            {
                _data.reserve(_byteCount);
                _dataP = _data.data();
            }
        }

        Image::~Image()
        {}

        std::shared_ptr<Image> Image::create(const ImageInfo & info)
        {
            return std::shared_ptr<Image>(new Image(info));
        }

        std::shared_ptr<Image> Image::create(const ImageInfo& info, uint8_t* externalData)
        {
            return std::shared_ptr<Image>(new Image(info, externalData));
        }

        std::shared_ptr<Image> Image::create(const Size2I& size, ImageType type)
        {
            return std::shared_ptr<Image>(new Image(ImageInfo(size, type)));
        }

        std::shared_ptr<Image> Image::create(int w, int h, ImageType type)
        {
            return std::shared_ptr<Image>(new Image(ImageInfo(w, h, type)));
        }

        void Image::setTags(const ImageTags& tags)
        {
            _tags = tags;
        }
        
        void Image::zero()
        {
            memset(_dataP, 0, _byteCount);
        }
    }
}

