// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/StringTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/String.h>

namespace feather_tk
{
    namespace core_test
    {
        StringTest::StringTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::StringTest")
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
            _filler();
        }
        
        void StringTest::_split()
        {
            {
                FEATHER_TK_ASSERT(
                    split("a,b,c", ',') ==
                    std::vector<std::string>({ "a", "b", "c" }));
                FEATHER_TK_ASSERT(
                    split("a,,c", ',', SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                FEATHER_TK_ASSERT(
                    split("a,,c", ',', SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                FEATHER_TK_ASSERT(
                    split("a,b.c", { ',', '.' } ) ==
                    std::vector<std::string>({ "a", "b", "c" }));
                FEATHER_TK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::DiscardEmpty) ==
                    std::vector<std::string>({ "a", "c" }));
                FEATHER_TK_ASSERT(
                    split("a,.c", { ',', '.' }, SplitOptions::KeepEmpty) ==
                    std::vector<std::string>({ "a", "", "c" }));
            }
            {
                FEATHER_TK_ASSERT(join({ "a", "b", "c" }, ',') == "a,b,c");
                FEATHER_TK_ASSERT(join({ "a", "b", "c" }, ",.") == "a,.b,.c");
            }
        }
        
        void StringTest::_format()
        {
            {
                FEATHER_TK_ASSERT(toUpper("abc") == "ABC");
                FEATHER_TK_ASSERT(toLower("ABC") == "abc");
            }
            {
                std::string s = "abc";
                removeTrailingNewlines(s);
                FEATHER_TK_ASSERT("abc" == s);
                s = "abc\n";
                removeTrailingNewlines(s);
                FEATHER_TK_ASSERT("abc" == s);
                s = "abc\n\r";
                removeTrailingNewlines(s);
                FEATHER_TK_ASSERT("abc" == s);
            }
            {
                const std::string s("abcdef");
                FEATHER_TK_ASSERT("abcdef" == elide(s, 6));
                FEATHER_TK_ASSERT("abc..." == elide(s, 3));
                FEATHER_TK_ASSERT("..." == elide(s, 0));
            }
        }
        
        void StringTest::_compare()
        {
            {
                FEATHER_TK_ASSERT(!compare("abc", "ABC", CaseCompare::Sensitive));
                FEATHER_TK_ASSERT(compare("abc", "ABC", CaseCompare::Insensitive));
            }
            {
                FEATHER_TK_ASSERT(!contains("abc", "AB", CaseCompare::Sensitive));
                FEATHER_TK_ASSERT(contains("abc", "AB", CaseCompare::Insensitive));
            }
        }
        
        void StringTest::_convert()
        {
            {
                const std::string s("abc");
                const std::wstring w = toWide(s);
                FEATHER_TK_ASSERT(s == fromWide(w));
            }
        }

        void StringTest::_filler()
        {
            {
                _print(getLoremIpsum(100));
            }
        }
    }
}

