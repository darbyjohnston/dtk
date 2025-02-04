// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Image.h>
#include <dtk/core/RenderOptions.h>

namespace dtk
{
    namespace gl
    {
        //! \name Textures
        ///@{
        
        //! Get the OpenGL texture format.
        unsigned int getTextureFormat(ImageType);

        //! Get the OpenGL internal texture format.
        unsigned int getTextureInternalFormat(ImageType);

        //! Get the OpenGL texture type.
        unsigned int getTextureType(ImageType);

        //! Texture filtering.
        enum class TextureFilter
        {
            Nearest,
            Linear,

            Count,
            First = Nearest
        };
        DTK_ENUM(TextureFilter);

        //! Texture filters.
        struct TextureFilters
        {
            TextureFilter minify  = TextureFilter::Linear;
            TextureFilter magnify = TextureFilter::Linear;

            bool operator == (const TextureFilters&) const;
            bool operator != (const TextureFilters&) const;
        };

        //! Get the texture filter.
        unsigned int getTextureFilter(TextureFilter);

        //! Convert an image filter to a texture filter.
        TextureFilter toTextureFilter(ImageFilter);

        //! Convert image filters to texture filters.
        TextureFilters toTextureFilters(const ImageFilters&);

        //! Texture options.
        struct TextureOptions
        {
            TextureFilters filters;
            bool pbo = false;

            bool operator == (const TextureOptions&) const;
            bool operator != (const TextureOptions&) const;
        };

        //! Texture.
        class Texture : public std::enable_shared_from_this<Texture>
        {
            DTK_NON_COPYABLE(Texture);

        protected:
            Texture(
                const ImageInfo&,
                const TextureOptions&);

        public:
            ~Texture();

            //! Create a new texture.
            static std::shared_ptr<Texture> create(
                const ImageInfo&,
                const TextureOptions& = TextureOptions());

            //! Get the image information.
            const ImageInfo& getInfo() const;

            //! Get the size.
            const Size2I& getSize() const;

            //! Get the width.
            int getWidth() const;

            //! Get the height.
            int getHeight() const;

            //! Get the image type.
            ImageType getType() const;

            //! Get the OpenGL texture ID.
            unsigned int getID() const;

            //! \name Copy
            //! Copy image data to the texture.
            ///@{

            void copy(const std::shared_ptr<Image>&);
            void copy(const std::shared_ptr<Image>&, int x, int y);
            void copy(const uint8_t*, const ImageInfo&);

            ///@}

            //! Bind the texture.
            void bind();

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
