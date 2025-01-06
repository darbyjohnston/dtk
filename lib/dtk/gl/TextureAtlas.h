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
            BoxPackID id = boxPackInvalidID;
            Size2I size;
            RangeF u;
            RangeF v;
        };

        //! Texture atlas.
        class TextureAtlas : public std::enable_shared_from_this<TextureAtlas>
        {
            DTK_NON_COPYABLE(TextureAtlas);

        protected:
            void _init(
                int size,
                ImageType type,
                TextureFilter filter,
                int border);

            TextureAtlas();

        public:
            ~TextureAtlas();

            //! Create a new texture atlas.
            static std::shared_ptr<TextureAtlas> create(
                int size,
                ImageType type,
                TextureFilter filter = TextureFilter::Linear,
                int border = 1);

            //! Get the texture atlas size.
            int getSize() const;

            //! Get the texture atlas type.
            ImageType getType() const;

            //! Get the texture atlas ID.
            unsigned int getTexture() const;

            //! Get a texture atlas item.
            bool getItem(BoxPackID, TextureAtlasItem&);

            //! Add a texture atlas item.
            bool addItem(const std::shared_ptr<Image>&, TextureAtlasItem&);

            //! Get the percentage of the texture atlas that is in use.
            float getPercentageUsed() const;

        private:
            void _toItem(const std::shared_ptr<BoxPackNode>&, TextureAtlasItem&);

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
