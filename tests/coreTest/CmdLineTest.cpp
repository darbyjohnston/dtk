// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/CmdLineTest.h>

#include <dtk/core/CmdLine.h>

#include <dtk/core/Assert.h>

namespace dtk
{
    namespace core_test
    {
        CmdLineTest::CmdLineTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::app_test::CmdLineTest")
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
            DTK_ASSERT(flag);
            DTK_ASSERT(!flagCmdLineOption->getMatchedName().empty());

            auto boolCmdLineOption = CmdLineValueOption<bool>::create(
                boolOption,
                { "-boolOption" },
                "This is a boolean option",
                "0",
                join({ "0", "1" }, ", "));
            _print(join(boolCmdLineOption->getHelp(), '\n'));
            boolCmdLineOption->parse(argv);
            DTK_ASSERT(boolOption);

            auto intCmdLineOption = CmdLineValueOption<int>::create(
                intOption,
                { "-intOption" },
                "This is an integer option",
                "0");
            _print(join(intCmdLineOption->getHelp(), '\n'));
            intCmdLineOption->parse(argv);
            DTK_ASSERT(10 == intOption);

            auto intCmdLineArg = CmdLineValueArg<int>::create(
                intArg,
                "int",
                "This is an integer argument");
            DTK_ASSERT(!intCmdLineArg->getName().empty());
            DTK_ASSERT(!intCmdLineArg->isOptional());
            _print(intCmdLineArg->getHelp());
            intCmdLineArg->parse(argv);
            DTK_ASSERT(100 == intArg);

            auto stringCmdLineArg = CmdLineValueArg<std::string>::create(
                stringArg,
                "string",
                "This is a string argument");
            DTK_ASSERT(!stringCmdLineArg->getName().empty());
            DTK_ASSERT(!stringCmdLineArg->isOptional());
            _print(stringCmdLineArg->getHelp());
            stringCmdLineArg->parse(argv);
            DTK_ASSERT("string" == stringArg);

            auto listCmdLineArg = CmdLineListArg<std::string>::create(
                listArg,
                "list",
                "This is a list argument");
            DTK_ASSERT(!listCmdLineArg->getName().empty());
            DTK_ASSERT(!listCmdLineArg->isOptional());
            _print(listCmdLineArg->getHelp());
            listCmdLineArg->parse(argv);
            DTK_ASSERT(3 == listArg.size());
            DTK_ASSERT("list0" == listArg[0]);
            DTK_ASSERT("list1" == listArg[1]);
            DTK_ASSERT("list2" == listArg[2]);

            try
            {
                intCmdLineArg->parse(argv);
                DTK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            try
            {
                stringCmdLineArg->parse(argv);
                DTK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
            argv.push_back("-intOption");
            try
            {
                intCmdLineOption->parse(argv);
                DTK_ASSERT(false);
            }
            catch (const std::exception&)
            {}
        }
    }
}

