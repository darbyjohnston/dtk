// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/FileTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/File.h>
#include <feather-tk/core/Format.h>

namespace feather_tk
{
    namespace core_test
    {
        FileTest::FileTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::FileTest")
        {}

        FileTest::~FileTest()
        {}

        std::shared_ptr<FileTest> FileTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileTest>(new FileTest(context));
        }
        
        void FileTest::run()
        {
            _split();
            _drives();
            _userPaths();
        }

        void FileTest::_split()
        {
            {
                const std::vector<std::string> pieces = split("");
                FEATHER_TK_ASSERT(pieces.empty());
            }
            {
                const std::vector<std::string> pieces = split("/");
                FEATHER_TK_ASSERT(1 == pieces.size());
                FEATHER_TK_ASSERT("/" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("a");
                FEATHER_TK_ASSERT(1 == pieces.size());
                FEATHER_TK_ASSERT("a" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("/a");
                FEATHER_TK_ASSERT(2 == pieces.size());
                FEATHER_TK_ASSERT("/" == pieces[0]);
                FEATHER_TK_ASSERT("a" == pieces[1]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c");
                FEATHER_TK_ASSERT(4 == pieces.size());
                FEATHER_TK_ASSERT("/" == pieces[0]);
                FEATHER_TK_ASSERT("a" == pieces[1]);
                FEATHER_TK_ASSERT("b" == pieces[2]);
                FEATHER_TK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c/");
                FEATHER_TK_ASSERT(4 == pieces.size());
                FEATHER_TK_ASSERT("/" == pieces[0]);
                FEATHER_TK_ASSERT("a" == pieces[1]);
                FEATHER_TK_ASSERT("b" == pieces[2]);
                FEATHER_TK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("a/b/c/");
                FEATHER_TK_ASSERT(3 == pieces.size());
                FEATHER_TK_ASSERT("a" == pieces[0]);
                FEATHER_TK_ASSERT("b" == pieces[1]);
                FEATHER_TK_ASSERT("c" == pieces[2]);
            }
#if defined(_WINDOWS)
            {
                const std::vector<std::string> pieces = split("c:");
                FEATHER_TK_ASSERT(1 == pieces.size());
                FEATHER_TK_ASSERT("c:" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\");
                FEATHER_TK_ASSERT(1 == pieces.size());
                FEATHER_TK_ASSERT("c:\\" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\a");
                FEATHER_TK_ASSERT(2 == pieces.size());
                FEATHER_TK_ASSERT("c:\\" == pieces[0]);
                FEATHER_TK_ASSERT("a" == pieces[1]);
            }
#endif // _WINDOWS
        }

        void FileTest::_drives()
        {
            for (const auto& drive : getDrives())
            {
                _print(Format("Drive: {0}").arg(drive));
            }
        }

        void FileTest::_userPaths()
        {
            for (auto path : getUserPathEnums())
            {
                _print(Format("{0}: {1}").arg(path).arg(getUserPath(path)));
            }
        }
    }
}

