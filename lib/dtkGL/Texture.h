// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/Image.h>

namespace dtk
{
    namespace gl
    {
        //! \name Textures
        ///@{
        
        //! Get the OpenGL texture format.
        unsigned int getTextureFormat(core::ImageType);

        //! Get the OpenGL internal texture format.
        unsigned int getTextureInternalFormat(core::ImageType);

        //! Get the OpenGL texture type.
        unsigned int getTextureType(core::ImageType);

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
                const core::ImageInfo&,
                const TextureOptions&);

        public:
            ~Texture();

            //! Create a new texture.
            static std::shared_ptr<Texture> create(
                const core::ImageInfo&,
                const TextureOptions& = TextureOptions());

            //! Get the image information.
            const core::ImageInfo& getInfo() const;

            //! Get the size.
            const core::Size2I& getSize() const;

            //! Get the width.
            int getWidth() const;

            //! Get the height.
            int getHeight() const;

            //! Get the image type.
            core::ImageType getType() const;

            //! Get the OpenGL texture ID.
            unsigned int getID() const;

            //! \name Copy
            //! Copy image data to the texture.
            ///@{

            void copy(const std::shared_ptr<core::Image>&);
            void copy(const std::shared_ptr<core::Image>&, int x, int y);
            void copy(const uint8_t*, const core::ImageInfo&);

            ///@}

            //! Bind the texture.
            void bind();

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
