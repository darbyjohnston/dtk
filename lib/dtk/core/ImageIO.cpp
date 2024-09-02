// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/ImageIO.h>

#include <dtk/core/PNG.h>

#include <algorithm>

namespace dtk
{
    ImageIOOptions merge(const ImageIOOptions& a, const ImageIOOptions& b)
    {
        ImageIOOptions out = b;
        for (const auto& i : a)
        {
            out[i.first] = i.second;
        }
        return out;
    }

    IImageReader::IImageReader(
        const std::filesystem::path& path,
        const InMemoryFile*,
        const ImageIOOptions&) :
        _path(path)
    {}

    IImageReader::~IImageReader()
    {}

    IImageWriter::IImageWriter(
        const std::filesystem::path& path,
        const ImageIOOptions&) :
        _path(path)
    {}

    IImageWriter::~IImageWriter()
    {}

    IImagePlugin::IImagePlugin(const std::string& name) :
        _name(name)
    {}

    IImagePlugin::~IImagePlugin()
    {}

    const std::string& IImagePlugin::getName() const
    {
        return _name;
    }

    bool IImagePlugin::canRead(
        const std::filesystem::path&,
        const ImageIOOptions&)
    {
        return false;
    }

    std::shared_ptr<IImageReader> IImagePlugin::read(
        const std::filesystem::path&,
        const ImageIOOptions&)
    {
        return nullptr;
    }

    std::shared_ptr<IImageReader> IImagePlugin::read(
        const std::filesystem::path&,
        const InMemoryFile&,
        const ImageIOOptions&)
    {
        return nullptr;
    }

    bool IImagePlugin::canWrite(
        const std::filesystem::path&,
        const ImageInfo&,
        const ImageIOOptions&)
    {
        return false;
    }

    std::shared_ptr<IImageWriter> IImagePlugin::write(
        const std::filesystem::path&,
        const ImageInfo&,
        const ImageIOOptions&)
    {
        return nullptr;
    }

    ImageIO::ImageIO(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::ImageIO")
    {
        _plugins.push_front(std::shared_ptr<IImagePlugin>(new png::ImagePlugin));
    }

    ImageIO::~ImageIO()
    {}

    std::shared_ptr<ImageIO> ImageIO::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<ImageIO>(new ImageIO(context));
    }

    const std::list<std::shared_ptr<IImagePlugin> >& ImageIO::getPlugins() const
    {
        return _plugins;
    }

    void ImageIO::addPlugin(const std::shared_ptr<IImagePlugin>& plugin)
    {
        _plugins.push_front(plugin);
    }

    std::shared_ptr<IImageReader> ImageIO::read(
        const std::filesystem::path& path,
        const ImageIOOptions& options)
    {
        std::shared_ptr<IImageReader> out;
        for (const auto& plugin : _plugins)
        {
            if (plugin->canRead(path, options))
            {
                out = plugin->read(path, options);
                break;
            }
        }
        return out;
    }

    std::shared_ptr<IImageReader> ImageIO::read(
        const std::filesystem::path& path,
        const InMemoryFile& memory,
        const ImageIOOptions& options)
    {
        std::shared_ptr<IImageReader> out;
        for (const auto& plugin : _plugins)
        {
            if (plugin->canRead(path, options))
            {
                out = plugin->read(path, memory, options);
                break;
            }
        }
        return out;
    }

    std::shared_ptr<IImageWriter> ImageIO::write(
        const std::filesystem::path& path,
        const ImageInfo& info,
        const ImageIOOptions& options)
    {
        std::shared_ptr<IImageWriter> out;
        for (const auto& plugin : _plugins)
        {
            if (plugin->canWrite(path, info, options))
            {
                out = plugin->write(path, info, options);
                break;
            }
        }
        return out;
    }
}