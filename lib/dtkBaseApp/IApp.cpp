// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkBaseApp/IApp.h>

#include <dtkBaseApp/CmdLine.h>

#include <dtkCore/Context.h>
#include <dtkCore/Init.h>
#include <dtkCore/Format.h>
#include <dtkCore/String.h>

#include <iostream>

namespace dtk
{
    namespace app
    {
        std::vector<std::string> convert(int argc, char** argv)
        {
            std::vector<std::string> out;
            for (int i = 0; i < argc; ++i)
            {
                out.push_back(argv[i]);
            }
            return out;
        }

        std::vector<std::string> convert(int argc, wchar_t* argv[])
        {
            std::vector<std::string> out;
            for (int i = 0; i < argc; ++i)
            {
                out.push_back(core::fromWide(argv[i]));
            }
            return out;
        }

        struct IApp::Private
        {
            std::vector<std::string> argv;
            std::string name;
            std::string summary;
            Options options;
            std::vector<std::shared_ptr<ICmdLineArg> > cmdLineArgs;
            std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptions;
            std::shared_ptr<core::ListObserver<core::LogItem> > logObserver;
            int exit = 0;
        };
        
        void IApp::_init(
            const std::shared_ptr<core::Context>& context,
                std::vector<std::string>& argv,
                const std::string& name,
                const std::string& summary,
                const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
                const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
        {
            DTK_P();
            core::init(context);

            _context = context;
            
            p.name = name;
            p.summary = summary;
            for (size_t i = 1; i < argv.size(); ++i)
            {
                p.argv.push_back(argv[i]);
            }

            p.cmdLineArgs = cmdLineArgs;
            p.cmdLineOptions = cmdLineOptions;
            p.cmdLineOptions.push_back(CmdLineFlagOption::create(
                p.options.log,
                { "-log" },
                "Print the log to the console."));
            p.cmdLineOptions.push_back(CmdLineFlagOption::create(
                p.options.help,
                { "-help", "-h", "--help", "--h" },
                "Show this message."));
            p.exit = _parseCmdLine();

            auto logSystem = context->getSystem<core::LogSystem>();
            p.logObserver = core::ListObserver<core::LogItem>::create(
                logSystem->observeLogItems(),
                [this](const std::vector<core::LogItem>& value)
                {
                    _print(value);
                });
            logSystem->print(name, "Starting...");
        }

        IApp::IApp() :
            _p(new Private)
        {}

        IApp::~IApp()
        {
            DTK_P();
            auto logSystem = _context->getSystem<core::LogSystem>();
            logSystem->print(p.name, "Exiting...");
            logSystem->tick();
        }
        
        int IApp::getExit() const
        {
            return _p->exit;
        }

        void IApp::_print(const std::string& value)
        {
            std::cout << value << std::endl;
        }

        void IApp::_printError(const std::string& value)
        {
            std::cerr << "ERROR: " << value << std::endl;
        }

        int IApp::_parseCmdLine()
        {
            DTK_P();
            for (const auto& i : p.cmdLineOptions)
            {
                try
                {
                    i->parse(p.argv);
                }
                catch (const std::exception& e)
                {
                    throw std::runtime_error(core::Format("Cannot parse option \"{0}\": {1}").
                        arg(i->getMatchedName()).
                        arg(e.what()));
                }
            }
            size_t requiredArgs = 0;
            size_t optionalArgs = 0;
            for (const auto& i : p.cmdLineArgs)
            {
                if (!i->isOptional())
                {
                    ++requiredArgs;
                }
                else
                {
                    ++optionalArgs;
                }
            }
            if (p.argv.size() < requiredArgs ||
                p.argv.size() > requiredArgs + optionalArgs ||
                p.options.help)
            {
                _printCmdLineHelp();
                return 1;
            }
            for (const auto& i : p.cmdLineArgs)
            {
                try
                {
                    if (!(p.argv.empty() && i->isOptional()))
                    {
                        i->parse(p.argv);
                    }
                }
                catch (const std::exception& e)
                {
                    throw std::runtime_error(core::Format("Cannot parse argument \"{0}\": {1}").
                        arg(i->getName()).
                        arg(e.what()));
                }
            }
            return 0;
        }

        void IApp::_printCmdLineHelp()
        {
            DTK_P();
            _print("\n" + p.name + "\n");
            _print("    " + p.summary + "\n");
            _print("Usage:\n");
            {
                std::stringstream ss;
                ss << "    " + p.name;
                if (p.cmdLineArgs.size())
                {
                    std::vector<std::string> args;
                    for (const auto& i : p.cmdLineArgs)
                    {
                        const bool optional = i->isOptional();
                        args.push_back(
                            (optional ? "[" : "(") +
                            core::toLower(i->getName()) +
                            (optional ? "]" : ")"));
                    }
                    ss << " " << core::join(args, " ");
                }
                if (p.cmdLineOptions.size())
                {
                    ss << " [option],...";
                }
                _print(ss.str());
                _print("");
            }
            _print("Arguments:\n");
            for (const auto& i : p.cmdLineArgs)
            {
                _print("    " + i->getName());
                _print("        " + i->getHelp());
                _print("");
            }
            _print("Options:\n");
            for (const auto& i : p.cmdLineOptions)
            {
                bool first = true;
                for (const auto& j : i->getHelp())
                {
                    if (first)
                    {
                        first = false;
                        _print("    " + j);
                    }
                    else
                    {
                        _print("        " + j);
                    }
                }
                _print("");
            }
        }

        void IApp::_print(const std::vector<core::LogItem>& value)
        {
            DTK_P();
            if (_p->options.log)
            {
                for (const auto& item : value)
                {
                    std::cout << "LOG: " << core::toString(item) << std::endl;
                }
            }
        }
    }
}

