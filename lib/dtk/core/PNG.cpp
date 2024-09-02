// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/PNGPrivate.h>

#include <filesystem>

namespace dtk
{
    namespace core
    {
        namespace png
        {
            ImagePlugin::ImagePlugin() :
                IImagePlugin("PNG")
            {}

            ImagePlugin::~ImagePlugin()
            {}
            
            bool ImagePlugin::canRead(
                const std::filesystem::path& path,
                const Options&)
            {
                return compare(
                    path.extension().string(),
                    ".png",
                    Compare::CaseInsensitive);
            }

            std::shared_ptr<IImageReader> ImagePlugin::read(
                const std::filesystem::path& path,
                const Options& options)
            {
                return std::shared_ptr<ImageReader>(
                    new ImageReader(path, nullptr, options));
            }

            std::shared_ptr<IImageReader> ImagePlugin::read(
                const std::filesystem::path& path,
                const InMemoryFile& memory,
                const Options& options)
            {
                return std::shared_ptr<ImageReader>(
                    new ImageReader(path, &memory, options));
            }

            bool ImagePlugin::canWrite(
                const std::filesystem::path& path,
                const ImageInfo& info,
                const Options&)
            {
                return compare(
                    path.extension().string(),
                    ".png",
                    Compare::CaseInsensitive) &&
                    (
                        info.type == ImageType::L_U8 ||
                        info.type == ImageType::L_U16 ||
                        info.type == ImageType::LA_U8 ||
                        info.type == ImageType::LA_U16 ||
                        info.type == ImageType::RGB_U8 ||
                        info.type == ImageType::RGB_U16 ||
                        info.type == ImageType::RGBA_U8 ||
                        info.type == ImageType::RGBA_U16
                    );
            }

            std::shared_ptr<IImageWriter> ImagePlugin::write(
                const std::filesystem::path& path,
                const core::ImageInfo& info,
                const Options& options)
            {
                return std::shared_ptr<ImageWriter>(
                    new ImageWriter(path, info, options));
            }
        }
    }
}

extern "C"
{
    void pngErrorFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<dtk::core::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
        longjmp(png_jmpbuf(in), 1);
    }

    void pngWarningFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<dtk::core::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
    }
}

