// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/ImageIO.h>

namespace dtk
{
    namespace png
    {
        //! \name PNG
        ///@{

        //! PNG image reader.
        class ImageReader : public IImageReader
        {
        public:
            ImageReader(
                const std::filesystem::path&,
                const InMemoryFile*,
                const ImageIOOptions&);
                
            virtual ~ImageReader();

            const ImageInfo& getInfo() const override;
            std::shared_ptr<Image> read() override;

        private:
            DTK_PRIVATE();
        };

        //! PNG image writer.
        class ImageWriter : public IImageWriter
        {
        public:
            ImageWriter(
                const std::filesystem::path&,
                const ImageInfo&,
                const ImageIOOptions&);

            virtual ~ImageWriter();

            void write(const std::shared_ptr<Image>&) override;

        private:
            DTK_PRIVATE();
        };
            
        //! PNG image I/O plugin.
        class ImagePlugin : public IImagePlugin
        {
        public:
            ImagePlugin();

            virtual ~ImagePlugin();

            bool canRead(
                const std::filesystem::path&,
                const ImageIOOptions& = ImageIOOptions()) override;
            std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const ImageIOOptions& = ImageIOOptions()) override;
            std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const InMemoryFile&,
                const ImageIOOptions& = ImageIOOptions()) override;
            bool canWrite(
                const std::filesystem::path&,
                const ImageInfo&,
                const ImageIOOptions& = ImageIOOptions()) override;
            std::shared_ptr<IImageWriter> write(
                const std::filesystem::path&,
                const ImageInfo&,
                const ImageIOOptions& = ImageIOOptions()) override;
        };
            
        ///@}
    }
}
