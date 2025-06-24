// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/CmdLineTest.h>

#include <feather-tk/core/CmdLine.h>

#include <feather-tk/core/Assert.h>

namespace feather_tk
{
    namespace core_test
    {
        CmdLineTest::CmdLineTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::app_test::CmdLineTest")
        {}

        CmdLineTest::~CmdLineTest()
        {}

        std::shared_ptr<CmdLineTest> CmdLineTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<CmdLineTest>(new CmdLineTest(context));
        }
        
        void CmdLineTest::run()
        {
            bool flag = false;
            bool boolOption = false;
            int intOption = 0;
            int intArg = 0;
            std::string stringArg;
            std::vector<std::string> listArg;

            std::vector<std::string> argv =
            {
                "-flag",
                "-boolOption", "1",
                "-intOption", "10",
                "100",
                "string",
                "list0",
                "list1",
                "list2"
            };

            auto flagCmdLineOption = CmdLineFlagOption::create(
                flag,
                { "-flag" },
                "This is a flag option");
            _print(join(flagCmdLineOption->getHelp(), '\n'));
            flagCmdLineOption->parse(argv);
            FEATHER_TK_ASSERT(flag);
            FEATHER_TK_ASSERT(!flagCmdLineOption->getMatchedName().empty());

            auto boolCmdLineOption = CmdLineValueOption<bool>::create(
                boolOption,
                { "-boolOption" },
                "This is a boolean option",
                "0",
                join({ "0", "1" }, ", "));
            _print(join(boolCmdLineOption->getHelp(), '\n'));
            boolCmdLineOption->parse(argv);
            FEATHER_TK_ASSERT(boolOption);

            auto intCmdLineOption = CmdLineValueOption<int>::create(
                intOption,
                { "-intOption" },
                "This is an integer option",
                "0");
            _print(join(intCmdLineOption->getHelp(), '\n'));
            intCmdLineOption->parse(argv);
            FEATHER_TK_ASSERT(10 == intOption);

            auto intCmdLineArg = CmdLineValueArg<int>::create(
                intArg,
                "int",
                "This is an integer argument");
            FEATHER_TK_ASSERT(!intCmdLineArg->getName().empty());
            FEATHER_TK_ASSERT(!intCmdLineArg->isOptional());
            _print(intCmdLineArg->getHelp());
            intCmdLineArg->parse(argv);
            FEATHER_TK_ASSERT(100 == intArg);

            auto stringCmdLineArg = CmdLineValueArg<std::string>::create(
                stringArg,
                "string",
                "This is a string argument");
            FEATHER_TK_ASSERT(!stringCmdLineArg->getName().empty());
            FEATHER_TK_ASSERT(!stringCmdLineArg->isOptional());
            _print(stringCmdLineArg->getHelp());
            stringCmdLineArg->parse(argv);
            FEATHER_TK_ASSERT("string" == stringArg);

            auto listCmdLineArg = CmdLineListArg<std::string>::create(
                listArg,
                "list",
                "This is a list argument");
            FEATHER_TK_ASSERT(!listCmdLineArg->getName().empty());
            FEATHER_TK_ASSERT(!listCmdLineArg->isOptional());
            _print(listCmdLineArg->getHelp());
            listCmdLineArg->parse(argv);
            FEATHER_TK_ASSERT(3 == listArg.size());
            FEATHER_TK_ASSERT("list0" == listArg[0]);
            FEATHER_TK_ASSERT("list1" == listArg[1]);
            FEATHER_TK_ASSERT("list2" == listArg[2]);

            try
            {
                intCmdLineArg->parse(argv);
                FEATHER_TK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            try
            {
                stringCmdLineArg->parse(argv);
                FEATHER_TK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            argv.push_back("-intOption");
            try
            {
                intCmdLineOption->parse(argv);
                FEATHER_TK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
        }
    }
}

