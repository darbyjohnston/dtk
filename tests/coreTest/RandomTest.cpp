// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/RandomTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Random.h>

#include <sstream>

namespace feather_tk
{
    namespace core_test
    {
        RandomTest::RandomTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::RandomTest")
        {}

        RandomTest::~RandomTest()
        {}

        std::shared_ptr<RandomTest> RandomTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<RandomTest>(new RandomTest(context));
        }
        
        void RandomTest::run()
        {
            {
                Random random;
                std::stringstream ss;
                ss << "0.0 - 1.0: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getF() << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                random.setSeed(1);
                std::stringstream ss;
                ss << "0.0 - 1.0: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getF() << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                random.setSeed();
                std::stringstream ss;
                ss << "0.0 - 1.0: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getF() << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                std::stringstream ss;
                ss << "0.0 - 10.0: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getF(10.0) << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                std::stringstream ss;
                ss << "-10.0 - 10.0: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getF(-10.0, 10.0) << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                std::stringstream ss;
                ss << "0 - 10: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getI(0, 10) << " ";
                }
                _print(ss.str());
            }
            {
                Random random;
                std::stringstream ss;
                ss << "-10 - 10: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getI(-10, 10) << " ";
                }
                _print(ss.str());
            }
            {
                const std::vector<char> data = { 'a', 'b', 'c', 'd' };
                Random random;
                std::stringstream ss;
                ss << "items: ";
                for (int i = 0; i < 10; ++i)
                {
                    ss << random.getItem(data) << " ";
                }
                _print(ss.str());
            }
        }
    }
}

