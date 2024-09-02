// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/gl/Texture.h>

#include <dtk/core/BoxPack.h>
#include <dtk/core/Image.h>
#include <dtk/core/Range.h>

namespace dtk
{
    namespace gl
    {
        //! \name Texture Atlas
        ///@{
        
        //! Texture atlas item.
        struct TextureAtlasItem
        {
            core::BoxPackID id = core::boxPackInvalidID;
            core::Size2I size;
            core::RangeF textureU;
            core::RangeF textureV;
        };

        //! Texture atlas.
        class TextureAtlas : public std::enable_shared_from_this<TextureAtlas>
        {
            DTK_NON_COPYABLE(TextureAtlas);

        protected:
            void _init(
                int textureSize,
                core::ImageType textureType,
                TextureFilter filter,
                int border);

            TextureAtlas();

        public:
            ~TextureAtlas();

            //! Create a new texture atlas.
            static std::shared_ptr<TextureAtlas> create(
                int textureSize,
                core::ImageType textureType,
                TextureFilter filter = TextureFilter::Linear,
                int border = 1);

            int getTextureSize() const;
            core::ImageType getTextureType() const;
            unsigned int getTexture() const;

            bool getItem(core::BoxPackID, TextureAtlasItem&);

            bool addItem(
                const std::shared_ptr<core::Image>&,
                TextureAtlasItem&);

            float getPercentageUsed() const;

        private:
            void _toTextureAtlasItem(
                const std::shared_ptr<core::BoxPackNode>&,
                TextureAtlasItem&);

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
