// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/SystemTest.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Context.h>
#include <feather-tk/core/ISystem.h>
#include <feather-tk/core/LogSystem.h>

namespace feather_tk
{
    namespace core_test
    {
        namespace
        {
            class System1 : public ISystem
            {
            protected:
                System1(const std::shared_ptr<Context>& context) :
                    ISystem(context, "feather_tk::core_test::System1")
                {}

            public:
                virtual ~System1()
                {}

                static std::shared_ptr<System1> create(
                    const std::shared_ptr<Context>& context)
                {
                    return std::shared_ptr<System1>(new System1(context));
                }
            };
            
            class System2 : public ISystem
            {
            protected:
                System2(const std::shared_ptr<Context>& context) :
                    ISystem(context, "feather_tk::core_test::System2")
                {}

            public:
                virtual ~System2()
                {}

                static std::shared_ptr<System2> create(
                    const std::shared_ptr<Context>& context)
                {
                    return std::shared_ptr<System2>(new System2(context));
                }

                std::chrono::milliseconds getTickTime() const override
                {
                    return std::chrono::milliseconds(100);
                }
            };
        }
        
        SystemTest::SystemTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::core_test::SystemTest")
        {
            auto system = System1::create(context);
            FEATHER_TK_ASSERT(system->getContext().lock());
            FEATHER_TK_ASSERT(!system->getName().empty());
            context->addSystem(system);
            context->addSystem(System2::create(context));
        }

        SystemTest::~SystemTest()
        {}

        std::shared_ptr<SystemTest> SystemTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<SystemTest>(new SystemTest(context));
        }
        
        void SystemTest::run()
        {
            {
                LogItem a;
                LogItem b;
                FEATHER_TK_ASSERT(a == b);
                b.time = 1.F;
                FEATHER_TK_ASSERT(a != b);
            }
            if (auto context = _context.lock())
            {
                auto logSystem = context->getSystem<LogSystem>();
                logSystem->print(
                    "feather_tk::core_test::SystemTest",
                    "This is a message",
                    LogType::Message);
                logSystem->print(
                    "feather_tk::core_test::SystemTest",
                    "This is a warning!",
                    LogType::Warning);
                logSystem->print(
                    "feather_tk::core_test::SystemTest",
                    "This is an error!",
                    LogType::Error);
            }
        }
    }
}

