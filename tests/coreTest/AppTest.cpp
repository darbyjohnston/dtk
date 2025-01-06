// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/AppTest.h>

#include <dtk/core/IApp.h>
#include <dtk/core/CmdLine.h>

#include <dtk/core/Assert.h>

namespace dtk
{
    namespace core_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::app_test::AppTest")
        {}

        AppTest::~AppTest()
        {}

        std::shared_ptr<AppTest> AppTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<AppTest>(new AppTest(context));
        }

        namespace
        {
            class App : public IApp
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    std::vector<std::string>& argv);

                App() = default;

            public:
                virtual ~App();
                
                static std::shared_ptr<App> create(
                    const std::shared_ptr<Context>&,
                    std::vector<std::string>& argv);
                
                const std::string& getArg() const { return _arg; }
                int getOption() const { return _option; }

                void run() override;
                
            private:
                std::string _arg;
                int _option = 0;
            };

            void App::_init(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                IApp::_init(
                    context,
                    argv,
                    "dtk::app_test::App",
                    "Test application",
                    {
                        CmdLineValueArg<std::string>::create(
                            _arg,
                            "arg",
                            "This is an argument")
                    },
                    {
                        CmdLineValueOption<int>::create(
                            _option,
                            { "-option" },
                            "This is an option")
                    });
            }

            App::~App()
            {}
            
            std::shared_ptr<App> App::create(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                auto out = std::shared_ptr<App>(new App);
                out->_init(context, argv);
                return out;
            }
            
            void App::run()
            {}
        }
                
        void AppTest::run()
        {
            {
                char* argv[2];
                argv[0] = new char[2];
                argv[0][0] = 'a';
                argv[0][1] = 0;
                argv[1] = new char[2];
                argv[1][0] = 'b';
                argv[1][1] = 0;
                auto r = convert(2, argv);
                DTK_ASSERT("a" == r[0]);
                DTK_ASSERT("b" == r[1]);
                delete [] argv[0];
                delete [] argv[1];
            }
            {
                wchar_t* argv[2];
                argv[0] = new wchar_t[2];
                argv[0][0] = L'a';
                argv[0][1] = 0;
                argv[1] = new wchar_t[2];
                argv[1][0] = L'b';
                argv[1][1] = 0;
                auto r = convert(2, argv);
                DTK_ASSERT("a" == r[0]);
                DTK_ASSERT("b" == r[1]);
                delete [] argv[0];
                delete [] argv[1];
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "-h" };
                auto app = App::create(context, argv);
                _print(app->getExeName());
                app->run();
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "arg", "-option", "42" };
                auto app = App::create(context, argv);
                app->run();
                DTK_ASSERT("arg" == app->getArg());
                DTK_ASSERT(42 == app->getOption());
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app"};
                try
                {
                    auto app = App::create(context, argv);
                }
                catch (const std::exception&)
                {}
            }
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv = { "app", "arg", "-option" };
                try
                {
                    auto app = App::create(context, argv);
                }
                catch (const std::exception&)
                {}
            }
        }
    }
}

