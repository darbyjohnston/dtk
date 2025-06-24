// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/IApp.h>

#include <feather-tk/core/CmdLine.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/String.h>

#include <iostream>

namespace feather_tk
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
            out.push_back(fromWide(argv[i]));
        }
        return out;
    }

    struct IApp::Private
    {
        std::vector<std::string> argv;
        std::string exeName;
        std::string name;
        std::string summary;
        Options options;
        std::vector<std::shared_ptr<ICmdLineArg> > cmdLineArgs;
        std::vector<std::shared_ptr<ICmdLineOption> > cmdLineOptions;
        std::shared_ptr<ListObserver<LogItem> > logObserver;
        int exit = 0;
    };

    void IApp::_init(
        const std::shared_ptr<Context>& context,
        const std::vector<std::string>& argv,
        const std::string& name,
        const std::string& summary,
        const std::vector<std::shared_ptr<ICmdLineArg> >& cmdLineArgs,
        const std::vector<std::shared_ptr<ICmdLineOption> >& cmdLineOptions)
    {
        FEATHER_TK_P();

        _context = context;

        p.exeName = argv[0];
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

        auto logSystem = context->getSystem<LogSystem>();
        p.logObserver = ListObserver<LogItem>::create(
            logSystem->observeLogItems(),
            [this](const std::vector<LogItem>& value)
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
        FEATHER_TK_P();
        auto logSystem = _context->getSystem<LogSystem>();
        logSystem->print(p.name, "Exiting...");
        logSystem->tick();
    }

    const std::string& IApp::getExeName() const
    {
        return _p->exeName;
    }

    int IApp::getExit() const
    {
        return _p->exit;
    }

    const std::shared_ptr<Context>& IApp::getContext() const
    {
        return _context;
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
        FEATHER_TK_P();
        for (const auto& i : p.cmdLineOptions)
        {
            try
            {
                i->parse(p.argv);
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error(Format("Cannot parse option \"{0}\": {1}").
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
                throw std::runtime_error(Format("Cannot parse argument \"{0}\": {1}").
                    arg(i->getName()).
                    arg(e.what()));
            }
        }
        if (!p.argv.empty())
        {
            _printCmdLineHelp();
            return 1;
        }
        return 0;
    }

    void IApp::_printCmdLineHelp()
    {
        FEATHER_TK_P();
        _print("\n" + p.name + "\n");
        _print("    " + p.summary + "\n");
        _print("Usage:\n");
        {
            std::stringstream ss;
            ss << "    " + p.name;
            if (!p.cmdLineArgs.empty())
            {
                std::vector<std::string> args;
                for (const auto& i : p.cmdLineArgs)
                {
                    const bool optional = i->isOptional();
                    args.push_back(
                        (optional ? "[" : "(") +
                        toLower(i->getName()) +
                        (optional ? "]" : ")"));
                }
                ss << " " << join(args, " ");
            }
            if (!p.cmdLineOptions.empty())
            {
                ss << " [option],...";
            }
            _print(ss.str());
            _print("");
        }
        if (!p.cmdLineArgs.empty())
        {
            _print("Arguments:\n");
            for (const auto& i : p.cmdLineArgs)
            {
                _print("    " + i->getName() + " - " + i->getHelp());
                _print("");
            }
        }
        if (!p.cmdLineOptions.empty())
        {
            _print("Options:\n");
            for (const auto& i : p.cmdLineOptions)
            {
                for (const auto& j : i->getHelp())
                {
                    _print("    " + j);
                }
                _print("");
            }
        }
    }

    void IApp::_print(const std::vector<LogItem>& value)
    {
        FEATHER_TK_P();
        if (_p->options.log)
        {
            for (const auto& item : value)
            {
                std::cout << "LOG: " << toString(item) << std::endl;
            }
        }
    }
}
