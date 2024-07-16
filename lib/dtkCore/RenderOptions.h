// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/Color.h>
#include <dtkCore/Image.h>
#include <dtkCore/Memory.h>

#include <iostream>
#include <string>
#include <vector>

namespace dtk
{
    namespace core
    {
        //! \name Rendering
        ///@{

        //! Render options.
        struct RenderOptions
        {
            //! Clear the canvas before rendering.
            bool clear = true;

            //! Clear color.
            Color4F clearColor = Color4F(0.F, 0.F, 0.F, 0.F);

            //! Texture cache byte count.
            size_t textureCacheByteCount = gigabyte / 4;
            
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
            InputVideoLevels videoLevels  = InputVideoLevels::FromFile;
            AlphaBlend       alphaBlend   = AlphaBlend::Straight;
            ImageFilters     imageFilters;
            bool             cache        = true;

            bool operator == (const ImageOptions&) const;
            bool operator != (const ImageOptions&) const;
        };
        
        ///@}
    }
}

#include <dtkCore/RenderOptionsInline.h>

