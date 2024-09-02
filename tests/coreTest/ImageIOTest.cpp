// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/ImageIOTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Context.h>
#include <dtk/core/Format.h>
#include <dtk/core/ImageIO.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        ImageIOTest::ImageIOTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::ImageIOTest")
        {}

        ImageIOTest::~ImageIOTest()
        {}

        std::shared_ptr<ImageIOTest> ImageIOTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageIOTest>(new ImageIOTest(context));
        }
        
        void ImageIOTest::run()
        {
            _members();
            _functions();
        }
        
        namespace
        {
            class DummyPlugin : public IImagePlugin
            {
            protected:
                DummyPlugin() :
                    IImagePlugin("Dummy")
                {}

            public:
                virtual ~DummyPlugin()
                {}
                
                static std::shared_ptr<DummyPlugin> create()
                {
                    return std::shared_ptr<DummyPlugin>(new DummyPlugin);
                }
            };
        }
        
        void ImageIOTest::_members()
        {
            if (auto context = _context.lock())
            {
                auto io = context->getSystem<ImageIO>();
                auto dummy = DummyPlugin::create();
                io->addPlugin(dummy);
                for (const auto& plugin : io->getPlugins())
                {
                    _print(Format("Plugin: {0}").arg(plugin->getName()));
                }
            }
        }
        
        void ImageIOTest::_functions()
        {
            Options options;
            options["Layer"] = "1";
            Options options2;
            options2["Compression"] = "RLE";
            Options options3 = merge(options, options2);
            DTK_ASSERT(2 == options3.size());
            DTK_ASSERT(options3["Layer"] == "1");
            DTK_ASSERT(options3["Compression"] == "RLE");
        }
    }
}

