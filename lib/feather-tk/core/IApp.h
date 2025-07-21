// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/LogSystem.h>

#include <memory>
#include <string>
#include <vector>

#if defined(_WINDOWS)
#define FEATHER_TK_MAIN() \
    int wmain(int argc, wchar_t* argv[])
#else // _WINDOWS
#define FEATHER_TK_MAIN() \
    int main(int argc, char* argv[])
#endif // _WINDOWS

namespace feather_tk
{
    class Context;
    class ICmdLineArg;
    class ICmdLineOption;
        
    //! Convert command line arguments.
    std::vector<std::string> convert(int argc, char** argv);

    //! Convert command line arguments.
    std::vector<std::string> convert(int argc, wchar_t* argv[]);

    //! Base class for applications.
    class IApp : public std::enable_shared_from_this<IApp>
    {
        FEATHER_TK_NON_COPYABLE(IApp);

    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::vector<std::string>& argv,
            const std::string& name,
            const std::string& summary,
            const std::vector<std::shared_ptr<ICmdLineArg> >& = {},
            const std::vector<std::shared_ptr<ICmdLineOption> >& = {});

        IApp();

    public:
        virtual ~IApp() = 0;

        //! Get the executable file name.
        const std::string& getExeName() const;

        //! Get the exit code.
        int getExit() const;

        //! Get the context.
        const std::shared_ptr<Context>& getContext() const;

        //! Run the application.
        virtual void run() {}

    protected:
        void _print(const std::string&);
        void _printError(const std::string&);

        std::shared_ptr<Context> _context;
        
    private:
        int _parseCmdLine();
        void _printCmdLineHelp();

        void _print(const std::vector<LogItem>&);

        FEATHER_TK_PRIVATE();
    };
}
