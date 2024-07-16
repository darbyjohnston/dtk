// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/FileIO.h>
#include <dtkCore/ISystem.h>
#include <dtkCore/Image.h>

#include <list>

namespace dtk
{
    namespace core
    {
        //! \name Image I/O
        ///@{

        //! Image I/O options.
        typedef std::map<std::string, std::string> Options;

        //! Merge image I/O options.
        Options merge(const Options&, const Options&);
        
        //! Base class for image readers.
        class IImageReader
        {
        public:
            IImageReader(
                const std::filesystem::path&,
                const core::InMemoryFile*,
                const Options&);
            
            virtual ~IImageReader() = 0;

            //! Get information about the image.
            virtual const core::ImageInfo& getInfo() const = 0;

            //! Read the image.
            virtual std::shared_ptr<core::Image> read() = 0;

        protected:
            std::filesystem::path _path;
        };

        //! Base class for image writers.
        class IImageWriter
        {
        public:
            IImageWriter(
                const std::filesystem::path&,
                const Options&);

            virtual ~IImageWriter() = 0;
            
            //! Write the image.
            virtual void write(const std::shared_ptr<core::Image>&) = 0;

        protected:
            std::filesystem::path _path;
        };
        
        //! Base class for image I/O plugins.
        class IImagePlugin : std::enable_shared_from_this<IImagePlugin>
        {
            DTK_NON_COPYABLE(IImagePlugin);

        protected:
            IImagePlugin(const std::string& name);

        public:
            virtual ~IImagePlugin() = 0;
            
            const std::string& getName() const;
            
            virtual bool canRead(
                const std::filesystem::path&,
                const Options& = Options());

            virtual std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const Options& = Options());
            
            virtual std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const core::InMemoryFile&,
                const Options& = Options());

            virtual bool canWrite(
                const std::filesystem::path&,
                const core::ImageInfo&,
                const Options& = Options());

            virtual std::shared_ptr<IImageWriter> write(
                const std::filesystem::path&,
                const core::ImageInfo&,
                const Options& = Options());
                
        private:
            std::string _name;
        };
        
        //! Image I/O system.
        class ImageIO : public core::ISystem
        {
        protected:
            ImageIO(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ImageIO();

            //! Create a new system.
            static std::shared_ptr<ImageIO> create(const std::shared_ptr<core::Context>&);

            //! Get the plugins.
            const std::list<std::shared_ptr<IImagePlugin> >& getPlugins() const;
            
            //! Add a plugin.
            void addPlugin(const std::shared_ptr<IImagePlugin>&);
            
            //! Get an image reader.
            std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const Options& = Options());

            //! Get an image reader.
            std::shared_ptr<IImageReader> read(
                const std::filesystem::path&,
                const core::InMemoryFile&,
                const Options& = Options());
            
            //! Get an image writer.
            std::shared_ptr<IImageWriter> write(
                const std::filesystem::path&,
                const core::ImageInfo&,
                const Options& = Options());

        private:
            std::list<std::shared_ptr<IImagePlugin> > _plugins;
        };
        
        ///@}
    }
}

