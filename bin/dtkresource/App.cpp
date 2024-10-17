// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

#include <dtk/core/CmdLine.h>

#include <dtk/core/FileIO.h>
#include <dtk/core/Format.h>
#include <dtk/core/String.h>

namespace dtk
{
    namespace resource
    {
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            IApp::_init(
                context,
                argv,
                "tlresource",
                "Convert a resource file to a source file.",
                {
                    CmdLineValueArg<std::string>::create(
                        _input,
                        "input",
                        "The input resource file."),
                    CmdLineValueArg<std::string>::create(
                        _output,
                        "output",
                        "The output source code file."),
                    CmdLineValueArg<std::string>::create(
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

            size_t size = 0;
            std::vector<uint8_t> data;
            {
                _print(Format("Input: {0}").arg(_input));
                auto io = FileIO::create(_input, FileMode::Read);
                size = io->getSize();
                data.resize(size);
                io->readU8(data.data(), size);
            }

            {
                _print(Format("Output: {0}").arg(_output));
                auto io = FileIO::create(_output, FileMode::Write);
                io->write(Format("const std::vector<uint8_t> {0} = {\n").arg(_varName));
                const size_t columns = 15;
                for (size_t i = 0; i < size; i += columns)
                {
                    io->write("    ");
                    for (size_t j = i; j < i + columns && j < size; ++j)
                    {
                        io->write(Format("{0}, ").arg(static_cast<int>(data[j])));
                    }
                    io->write("\n");
                }
                io->write("};\n");
            }

            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - _startTime;
            _print(Format("Seconds elapsed: {0}").arg(diff.count(), 2));
        }
    }
}

