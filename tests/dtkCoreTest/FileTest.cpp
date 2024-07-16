// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCoreTest/FileTest.h>

#include <dtkCore/Assert.h>
#include <dtkCore/File.h>
#include <dtkCore/Format.h>

using namespace dtk::core;

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
            for (const auto& drive : getDrives())
            {
                _print(Format("Drive: {0}").arg(drive));
            }
            for (auto path : getUserPathEnums())
            {
                _print(Format("{0}: {1}").arg(path).arg(getUserPath(path)));
            }
        }
    }
}

