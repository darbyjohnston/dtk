// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/ImageIO.h>

namespace dtk
{
    namespace core
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
                    const core::InMemoryFile*,
                    const Options&);
                
                virtual ~ImageReader();

                const core::ImageInfo& getInfo() const override;
                std::shared_ptr<core::Image> read() override;

            private:
                DTK_PRIVATE();
            };

            //! PNG image writer.
            class ImageWriter : public IImageWriter
            {
            public:
                ImageWriter(
                    const std::filesystem::path&,
                    const core::ImageInfo&,
                    const Options&);

                virtual ~ImageWriter();

                void write(const std::shared_ptr<core::Image>&) override;

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
                    const Options& = Options()) override;
                std::shared_ptr<IImageReader> read(
                    const std::filesystem::path&,
                    const Options& = Options()) override;
                std::shared_ptr<IImageReader> read(
                    const std::filesystem::path&,
                    const core::InMemoryFile&,
                    const Options& = Options()) override;
                bool canWrite(
                    const std::filesystem::path&,
                    const core::ImageInfo&,
                    const Options& = Options()) override;
                std::shared_ptr<IImageWriter> write(
                    const std::filesystem::path&,
                    const core::ImageInfo&,
                    const Options& = Options()) override;
            };
            
            ///@}
        }
    }
}
