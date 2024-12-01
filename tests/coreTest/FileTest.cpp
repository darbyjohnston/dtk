// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/FileTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/File.h>
#include <dtk/core/Format.h>

namespace dtk
{
    namespace core_test
    {
        FileTest::FileTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::FileTest")
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
                DTK_ASSERT(pieces.empty());
            }
            {
                const std::vector<std::string> pieces = split("/");
                DTK_ASSERT(1 == pieces.size());
                DTK_ASSERT("/" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("a");
                DTK_ASSERT(1 == pieces.size());
                DTK_ASSERT("a" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("/a");
                DTK_ASSERT(2 == pieces.size());
                DTK_ASSERT("/" == pieces[0]);
                DTK_ASSERT("a" == pieces[1]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c");
                DTK_ASSERT(4 == pieces.size());
                DTK_ASSERT("/" == pieces[0]);
                DTK_ASSERT("a" == pieces[1]);
                DTK_ASSERT("b" == pieces[2]);
                DTK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("/a/b/c/");
                DTK_ASSERT(4 == pieces.size());
                DTK_ASSERT("/" == pieces[0]);
                DTK_ASSERT("a" == pieces[1]);
                DTK_ASSERT("b" == pieces[2]);
                DTK_ASSERT("c" == pieces[3]);
            }
            {
                const std::vector<std::string> pieces = split("a/b/c/");
                DTK_ASSERT(3 == pieces.size());
                DTK_ASSERT("a" == pieces[0]);
                DTK_ASSERT("b" == pieces[1]);
                DTK_ASSERT("c" == pieces[2]);
            }
#if defined(_WINDOWS)
            {
                const std::vector<std::string> pieces = split("c:");
                DTK_ASSERT(1 == pieces.size());
                DTK_ASSERT("c:" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\");
                DTK_ASSERT(1 == pieces.size());
                DTK_ASSERT("c:\\" == pieces[0]);
            }
            {
                const std::vector<std::string> pieces = split("c:\\a");
                DTK_ASSERT(2 == pieces.size());
                DTK_ASSERT("c:\\" == pieces[0]);
                DTK_ASSERT("a" == pieces[1]);
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

