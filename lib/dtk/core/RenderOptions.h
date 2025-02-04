// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Color.h>
#include <dtk/core/Image.h>
#include <dtk/core/Memory.h>

#include <iostream>
#include <string>
#include <vector>

namespace dtk
{
    //! \name Rendering
    ///@{

    //! Render options.
    struct RenderOptions
    {
        //! Colot buffer type.
        ImageType colorBuffer = ImageType::RGBA_U8;

        //! Clear the canvas before rendering.
        bool clear = true;

        //! Clear color.
        Color4F clearColor = Color4F(0.F, 0.F, 0.F, 0.F);

        //! Texture cache byte count.
        size_t textureCacheByteCount = gigabyte / 4;

        //! Glyph texture atlas size.
        int glyphAtlasSize =
#if defined(dtk_API_GLES_2)
            2048;
#else // dtk_API_GLES_2
            4096;
#endif // dtk_API_GLES_2

        //! Enable logging.
        bool log = true;

        bool operator == (const RenderOptions&) const;
        bool operator != (const RenderOptions&) const;
    };

    //! Line drawing options.
    struct LineOptions
    {
        float width = 1.F;

        bool operator == (const LineOptions&) const;
        bool operator != (const LineOptions&) const;
    };

    //! Channel display.
    enum class ChannelDisplay
    {
        Color,
        Red,
        Green,
        Blue,
        Alpha,

        Count,
        First = Color
    };
    DTK_ENUM(ChannelDisplay);

    //! Input video levels.
    enum class InputVideoLevels
    {
        FromFile,
        FullRange,
        LegalRange,

        Count,
        First = FromFile
    };
    DTK_ENUM(InputVideoLevels);

    //! Alpha channel blending.
    //!
    //! References:
    //! - https://microsoft.github.io/Win2D/html/PremultipliedAlpha.htm
    enum class AlphaBlend
    {
        None,
        Straight,
        Premultiplied,

        Count,
        First = None
    };
    DTK_ENUM(AlphaBlend);

    //! Image filtering.
    enum class ImageFilter
    {
        Nearest,
        Linear,

        Count,
        First = Nearest
    };
    DTK_ENUM(ImageFilter);

    //! Image filters.
    struct ImageFilters
    {
        ImageFilter minify  = ImageFilter::Linear;
        ImageFilter magnify = ImageFilter::Linear;

        bool operator == (const ImageFilters&) const;
        bool operator != (const ImageFilters&) const;
    };

    //! Image options.
    struct ImageOptions
    {
        ChannelDisplay   channelDisplay = ChannelDisplay::Color;
        InputVideoLevels videoLevels    = InputVideoLevels::FromFile;
        AlphaBlend       alphaBlend     = AlphaBlend::Straight;
        ImageFilters     imageFilters;
        bool             cache          = true;

        bool operator == (const ImageOptions&) const;
        bool operator != (const ImageOptions&) const;
    };
        
    ///@}
}

#include <dtk/core/RenderOptionsInline.h>

