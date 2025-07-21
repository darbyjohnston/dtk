// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <coreTest/AppTest.h>

#include <feather-tk/core/IApp.h>
#include <feather-tk/core/CmdLine.h>

#include <feather-tk/core/Assert.h>

namespace feather_tk
{
    namespace core_test
    {
        AppTest::AppTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::app_test::AppTest")
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
                
                const std::optional<std::string>& getArg() const { return _arg->getValue(); }
                const std::optional<int>& getOption() const { return _option->getValue(); }

                void run() override;
                
            private:
                std::shared_ptr<CmdLineValueArg<std::string> > _arg;
                std::shared_ptr<CmdLineValueOption<int> > _option;
            };

            void App::_init(
                const std::shared_ptr<Context>& context,
                std::vector<std::string>& argv)
            {
                _arg = CmdLineValueArg<std::string>::create(
                    "arg",
                    "This is an argument");
                _option = CmdLineValueOption<int>::create(
                    { "-option" },
                    "This is an option");
                IApp::_init(
                    context,
                    argv,
                    "feather_tk::app_test::App",
                    "Test application",
                    { _arg },
                    { _option });
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
                FEATHER_TK_ASSERT("a" == r[0]);
                FEATHER_TK_ASSERT("b" == r[1]);
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
                FEATHER_TK_ASSERT("a" == r[0]);
                FEATHER_TK_ASSERT("b" == r[1]);
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
                FEATHER_TK_ASSERT("arg" == app->getArg());
                FEATHER_TK_ASSERT(42 == app->getOption());
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

