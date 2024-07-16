// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "dtktest.h"

#include <dtkUIAppTest/AppTest.h>

#include <dtkUITest/ActionTest.h>
#include <dtkUITest/BellowsTest.h>
#include <dtkUITest/ButtonGroupTest.h>
#include <dtkUITest/ButtonTest.h>
#include <dtkUITest/ColorWidgetTest.h>
#include <dtkUITest/ComboBoxTest.h>
#include <dtkUITest/DoubleEditTest.h>
#include <dtkUITest/DoubleEditSliderTest.h>
#include <dtkUITest/DoubleSliderTest.h>
#include <dtkUITest/DoubleModelTest.h>
#include <dtkUITest/DragAndDropTest.h>
#include <dtkUITest/DrawUtilTest.h>
#include <dtkUITest/EventTest.h>
#include <dtkUITest/FileBrowserTest.h>
#include <dtkUITest/FileEditTest.h>
#include <dtkUITest/FloatEditTest.h>
#include <dtkUITest/FloatEditSliderTest.h>
#include <dtkUITest/FloatSliderTest.h>
#include <dtkUITest/FloatModelTest.h>
#include <dtkUITest/GridLayoutTest.h>
#include <dtkUITest/GroupBoxTest.h>
#include <dtkUITest/IconTest.h>
#include <dtkUITest/IntEditTest.h>
#include <dtkUITest/IntEditSliderTest.h>
#include <dtkUITest/IntSliderTest.h>
#include <dtkUITest/IntModelTest.h>
#include <dtkUITest/LabelTest.h>
#include <dtkUITest/LayoutUtilTest.h>
#include <dtkUITest/LineEditTest.h>
#include <dtkUITest/ListWidgetTest.h>
#include <dtkUITest/MDIWidgetTest.h>
#include <dtkUITest/MenuBarTest.h>
#include <dtkUITest/MessageDialogTest.h>
#include <dtkUITest/PieChartTest.h>
#include <dtkUITest/RecentFilesModelTest.h>
#include <dtkUITest/RowLayoutTest.h>
#include <dtkUITest/ScrollAreaTest.h>
#include <dtkUITest/ScrollBarTest.h>
#include <dtkUITest/ScrollWidgetTest.h>
#include <dtkUITest/SearchBoxTest.h>
#include <dtkUITest/SplitterTest.h>
#include <dtkUITest/StackLayoutTest.h>
#include <dtkUITest/StyleTest.h>
#include <dtkUITest/TabWidgetTest.h>
#include <dtkUITest/WidgetOptionsTest.h>

#include <dtkBaseAppTest/AppTest.h>
#include <dtkBaseAppTest/CmdLineTest.h>

#if defined(dtk_API_GL_4_1) || defined(dtk_API_GLES_2)
#include <dtkGLTest/MeshTest.h>
#include <dtkGLTest/OffscreenBufferTest.h>
#include <dtkGLTest/TextureAtlasTest.h>
#include <dtkGLTest/TextureTest.h>
#include <dtkGLTest/RenderTest.h>
#include <dtkGLTest/ShaderTest.h>
#include <dtkGLTest/WindowTest.h>
#endif // dtk_API_GL_4_1

#include <dtkCoreTest/BoxPackTest.h>
#include <dtkCoreTest/BoxTest.h>
#include <dtkCoreTest/ColorTest.h>
#include <dtkCoreTest/CommandTest.h>
#include <dtkCoreTest/ErrorTest.h>
#include <dtkCoreTest/FileIOTest.h>
#include <dtkCoreTest/FileTest.h>
#include <dtkCoreTest/FontSystemTest.h>
#include <dtkCoreTest/FormatTest.h>
#include <dtkCoreTest/ImageIOTest.h>
#include <dtkCoreTest/ImageTest.h>
#include <dtkCoreTest/LRUCacheTest.h>
#include <dtkCoreTest/MathTest.h>
#include <dtkCoreTest/MatrixTest.h>
#include <dtkCoreTest/MemoryTest.h>
#include <dtkCoreTest/MeshTest.h>
#include <dtkCoreTest/NoiseTest.h>
#include <dtkCoreTest/OSTest.h>
#include <dtkCoreTest/ObservableTest.h>
#include <dtkCoreTest/PNGTest.h>
#include <dtkCoreTest/RandomTest.h>
#include <dtkCoreTest/RangeTest.h>
#include <dtkCoreTest/RenderOptionsTest.h>
#include <dtkCoreTest/RenderUtilTest.h>
#include <dtkCoreTest/SizeTest.h>
#include <dtkCoreTest/StringTest.h>
#include <dtkCoreTest/SystemTest.h>
#include <dtkCoreTest/TimeTest.h>
#include <dtkCoreTest/TimerTest.h>
#include <dtkCoreTest/VectorTest.h>

#include <dtkUI/Init.h>

#include <dtkBaseApp/CmdLine.h>

#if defined(dtk_API_GL_4_1) || defined(dtk_API_GLES_2)
#include <dtkGL/Init.h>
#endif // dtk_API_GL_4_1

#include <dtkCore/Context.h>
#include <dtkCore/Format.h>
#include <dtkCore/Time.h>

#include <iostream>

using namespace dtk;
using namespace dtk::core;

namespace dtk
{
    namespace tests
    {
        struct App::Private
        {
            std::string testName;
            std::vector<std::shared_ptr<test::ITest> > tests;
            std::chrono::steady_clock::time_point startTime;
        };
        
        void App::_init(
            const std::shared_ptr<Context>& context,
            std::vector<std::string>& argv)
        {
            app::IApp::_init(
                context,
                argv,
                "dtktest",
                "Test application",
                {
                    app::CmdLineValueArg<std::string>::create(
                        _p->testName,
                        "Test",
                        "Name of the test to run.",
                        true)
                });
            DTK_P();
            p.startTime = std::chrono::steady_clock::now();                
#if defined(dtk_API_GL_4_1) || defined(dtk_API_GLES_2)
            gl::init(context);
#endif // dtk_API_GL_4_1
            ui::init(context);

            p.tests.push_back(core_test::BoxPackTest::create(context));
            p.tests.push_back(core_test::BoxTest::create(context));
            p.tests.push_back(core_test::ColorTest::create(context));
            p.tests.push_back(core_test::CommandTest::create(context));
            p.tests.push_back(core_test::ErrorTest::create(context));
            p.tests.push_back(core_test::FileIOTest::create(context));
            p.tests.push_back(core_test::FileTest::create(context));
            p.tests.push_back(core_test::FontSystemTest::create(context));
            p.tests.push_back(core_test::FormatTest::create(context));
            p.tests.push_back(core_test::ImageIOTest::create(context));
            p.tests.push_back(core_test::ImageTest::create(context));
            p.tests.push_back(core_test::LRUCacheTest::create(context));
            p.tests.push_back(core_test::MathTest::create(context));
            p.tests.push_back(core_test::MatrixTest::create(context));
            p.tests.push_back(core_test::MemoryTest::create(context));
            p.tests.push_back(core_test::MeshTest::create(context));
            p.tests.push_back(core_test::NoiseTest::create(context));
            p.tests.push_back(core_test::OSTest::create(context));
            p.tests.push_back(core_test::ObservableTest::create(context));
            p.tests.push_back(core_test::PNGTest::create(context));
            p.tests.push_back(core_test::RandomTest::create(context));
            p.tests.push_back(core_test::RangeTest::create(context));
            p.tests.push_back(core_test::RenderOptionsTest::create(context));
            p.tests.push_back(core_test::RenderUtilTest::create(context));
            p.tests.push_back(core_test::SizeTest::create(context));
            p.tests.push_back(core_test::StringTest::create(context));
            p.tests.push_back(core_test::SystemTest::create(context));
            p.tests.push_back(core_test::TimeTest::create(context));
            p.tests.push_back(core_test::TimerTest::create(context));
            p.tests.push_back(core_test::VectorTest::create(context));

#if defined(dtk_API_GL_4_1) || defined(dtk_API_GLES_2)
            p.tests.push_back(gl_test::MeshTest::create(context));
            p.tests.push_back(gl_test::OffscreenBufferTest::create(context));
            p.tests.push_back(gl_test::TextureAtlasTest::create(context));
            p.tests.push_back(gl_test::TextureTest::create(context));
            p.tests.push_back(gl_test::RenderTest::create(context));
            p.tests.push_back(gl_test::ShaderTest::create(context));
            p.tests.push_back(gl_test::WindowTest::create(context));
#endif // dtk_API_GL_4_1

            p.tests.push_back(app_test::AppTest::create(context));
            p.tests.push_back(app_test::CmdLineTest::create(context));

            p.tests.push_back(ui_test::ActionTest::create(context));
            p.tests.push_back(ui_test::BellowsTest::create(context));
            p.tests.push_back(ui_test::ButtonTest::create(context));
            p.tests.push_back(ui_test::ButtonGroupTest::create(context));
            p.tests.push_back(ui_test::ColorWidgetTest::create(context));
            p.tests.push_back(ui_test::ComboBoxTest::create(context));
            p.tests.push_back(ui_test::DoubleEditTest::create(context));
            p.tests.push_back(ui_test::DoubleEditSliderTest::create(context));
            p.tests.push_back(ui_test::DoubleSliderTest::create(context));
            p.tests.push_back(ui_test::DoubleModelTest::create(context));
            p.tests.push_back(ui_test::DragAndDropTest::create(context));
            p.tests.push_back(ui_test::DrawUtilTest::create(context));
            p.tests.push_back(ui_test::EventTest::create(context));
            p.tests.push_back(ui_test::FileBrowserTest::create(context));
            p.tests.push_back(ui_test::FileEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditTest::create(context));
            p.tests.push_back(ui_test::FloatEditSliderTest::create(context));
            p.tests.push_back(ui_test::FloatSliderTest::create(context));
            p.tests.push_back(ui_test::FloatModelTest::create(context));
            p.tests.push_back(ui_test::GridLayoutTest::create(context));
            p.tests.push_back(ui_test::GroupBoxTest::create(context));
            p.tests.push_back(ui_test::IconTest::create(context));
            p.tests.push_back(ui_test::IntEditTest::create(context));
            p.tests.push_back(ui_test::IntEditSliderTest::create(context));
            p.tests.push_back(ui_test::IntSliderTest::create(context));
            p.tests.push_back(ui_test::IntModelTest::create(context));
            p.tests.push_back(ui_test::LabelTest::create(context));
            p.tests.push_back(ui_test::LayoutUtilTest::create(context));
            p.tests.push_back(ui_test::LineEditTest::create(context));
            p.tests.push_back(ui_test::ListWidgetTest::create(context));
            p.tests.push_back(ui_test::MDIWidgetTest::create(context));
            p.tests.push_back(ui_test::MenuBarTest::create(context));
            p.tests.push_back(ui_test::MessageDialogTest::create(context));
            p.tests.push_back(ui_test::PieChartTest::create(context));
            p.tests.push_back(ui_test::RecentFilesModelTest::create(context));
            p.tests.push_back(ui_test::RowLayoutTest::create(context));
            p.tests.push_back(ui_test::ScrollAreaTest::create(context));
            p.tests.push_back(ui_test::ScrollBarTest::create(context));
            p.tests.push_back(ui_test::ScrollWidgetTest::create(context));
            p.tests.push_back(ui_test::SearchBoxTest::create(context));
            p.tests.push_back(ui_test::SplitterTest::create(context));
            p.tests.push_back(ui_test::StackLayoutTest::create(context));
            p.tests.push_back(ui_test::StyleTest::create(context));
            p.tests.push_back(ui_test::TabWidgetTest::create(context));
            p.tests.push_back(ui_test::WidgetOptionsTest::create(context));

            p.tests.push_back(ui_test::AppTest::create(context));
        }

        App::App() :
            _p(new Private)
        {}

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
        {
            DTK_P();

            // Get the tests to run.
            std::vector<std::shared_ptr<test::ITest> > runTests;
            for (const auto& test : p.tests)
            {
                if (p.testName.empty() ||
                    (!p.testName.empty() && contains(test->getName(), p.testName)))
                {
                    runTests.push_back(test);
                }
            }                
            
            // Run the tests.
            for (const auto& test : runTests)
            {
                _context->tick();
                _print(Format("Running test: {0}").arg(test->getName()));
                test->run();
            }
                
            const auto now = std::chrono::steady_clock::now();
            const std::chrono::duration<float> diff = now - p.startTime;
            _print(Format("Seconds elapsed: {0}").arg(diff.count(), 2));
        }
    }
}

DTK_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = app::convert(argc, argv);
        auto app = tests::App::create(context, args);
        r = app->getExit();
        if (0 == r)
        {
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

