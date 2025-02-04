// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace dtk
{
    inline bool RenderOptions::operator == (const RenderOptions& other) const
    {
        return
            colorBuffer == other.colorBuffer &&
            clear == other.clear &&
            clearColor == other.clearColor &&
            textureCacheByteCount == other.textureCacheByteCount &&
            glyphAtlasSize == other.glyphAtlasSize &&
            log == other.log;
    }

    inline bool RenderOptions::operator != (const RenderOptions& other) const
    {
        return !(*this == other);
    }

    inline bool LineOptions::operator == (const LineOptions& other) const
    {
        return width == other.width;
    }

    inline bool LineOptions::operator != (const LineOptions& other) const
    {
        return !(*this == other);
    }

    inline bool ImageFilters::operator == (const ImageFilters& other) const
    {
        return
            minify == other.minify &&
            magnify == other.magnify;
    }

    inline bool ImageFilters::operator != (const ImageFilters& other) const
    {
        return !(*this == other);
    }

    inline bool ImageOptions::operator == (const ImageOptions& other) const
    {
        return
            channelDisplay == other.channelDisplay &&
            videoLevels == other.videoLevels &&
            alphaBlend == other.alphaBlend &&
            imageFilters == other.imageFilters &&
            cache == other.cache;
    }

    inline bool ImageOptions::operator != (const ImageOptions& other) const
    {
        return !(*this == other);
    }
}
