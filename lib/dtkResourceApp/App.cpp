// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkResourceApp/App.h>

#include <dtkBaseApp/CmdLine.h>

#include <dtkCore/FileIO.h>
#include <dtkCore/Format.h>
#include <dtkCore/String.h>

using namespace dtk::core;

namespace dtk
{
    namespace resource
    {
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            app::IApp::_init(
                context,
                argv,
                "tlresource",
                "Convert a resource file to a source file.",
                {
                    app::CmdLineValueArg<std::string>::create(
                        _input,
                        "input",
                        "The input resource file."),
                    app::CmdLineValueArg<std::string>::create(
                        _output,
                        "output",
                        "The output source code file."),
                    app::CmdLineValueArg<std::string>::create(
                        _varName,
                        "variable name",
                        "The resource variable name.")
                });
        }

        App::App()
        {}

        App::~App()
        {}
        
        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, argv);
            return out;
        }
        
        void App::run()
        {
            _startTime = std::chrono::steady_clock::now();

            auto inputIO = FileIO::create(_input, FileMode::Read);
            const size_t size = inputIO->getSize();
            std::vector<uint8_t> data;
            data.resize(size);
            inputIO->readU8(data.data(), size);

            auto outputIO = FileIO::create(_output, FileMode::Write);
            outputIO->write(Format("const std::vector<uint8_t> {0} = {\n").arg(_varName));
            const size_t columns = 15;
            for (size_t i = 0; i < size; i += columns)
            {
                outputIO->write("    ");
                for (size_t j = i; j < i + columns && j < size; ++j)
                {
                    outputIO->write(Format("{0}, ").arg(static_cast<int>(data[j])));
                }
                outputIO->write("\n");
            }
            outputIO->write("};\n");

            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - _startTime;
            _print(Format("Seconds elapsed: {0}").arg(diff.count(), 2));
        }
    }
}

