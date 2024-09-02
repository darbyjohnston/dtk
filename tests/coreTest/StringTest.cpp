// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <coreTest/StringTest.h>

#include <dtk/core/Assert.h>
#include <dtk/core/String.h>

using namespace dtk::core;

namespace dtk
{
    namespace core_test
    {
        StringTest::StringTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::core_test::StringTest")
        {}

        StringTest::~StringTest()
        {}

        std::shared_ptr<StringTest> StringTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<StringTest>(new StringTest(context));
        }
        
        void StringTest::run()
        {
            _split();
            _format();
            _compare();
            _convert();
        }
        
        void StringTest::_split()
        {
            {
                DTK_ASSERT(
                    split("a,b,c", ',') ==
                    std::vector<std::string>({ "a", "b", "c" }));
                DTK_ASSERT(
                    split("a,,c", ',', SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                DTK_ASSERT(
                    split("a,,c", ',', SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                DTK_ASSERT(
                    split("a,b.c", { ',', '.' } ) ==
                    std::vector<std::string>({ "a", "b", "c" }));
                DTK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                DTK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                DTK_ASSERT(join({ "a", "b", "c" }, ',') == "a,b,c");
                DTK_ASSERT(join({ "a", "b", "c" }, ",.") == "a,.b,.c");
            }
        }
        
        void StringTest::_format()
        {
            {
                DTK_ASSERT(toUpper("abc") == "ABC");
                DTK_ASSERT(toLower("ABC") == "abc");
            }
            {
                std::string s = "abc";
                removeTrailingNewlines(s);
                DTK_ASSERT("abc" == s);
                s = "abc\n";
                removeTrailingNewlines(s);
                DTK_ASSERT("abc" == s);
                s = "abc\n\r";
                removeTrailingNewlines(s);
                DTK_ASSERT("abc" == s);
            }
            {
                const std::string s("abcdef");
                DTK_ASSERT("abcdef" == elide(s, 6));
                DTK_ASSERT("abc..." == elide(s, 3));
                DTK_ASSERT("..." == elide(s, 0));
            }
        }
        
        void StringTest::_compare()
        {
            {
                DTK_ASSERT(!compare("abc", "ABC", Compare::CaseSensitive));
                DTK_ASSERT(compare("abc", "ABC", Compare::CaseInsensitive));
            }
            {
                DTK_ASSERT(!contains("abc", "AB", Compare::CaseSensitive));
                DTK_ASSERT(contains("abc", "AB", Compare::CaseInsensitive));
            }
        }
        
        void StringTest::_convert()
        {
            {
                const std::string s("abc");
                const std::wstring w = toWide(s);
                DTK_ASSERT(s == fromWide(w));
            }
        }
    }
}

