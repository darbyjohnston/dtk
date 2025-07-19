// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FileBrowserTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <feather-tk/ui/FileBrowserPrivate.h>
#include <feather-tk/ui/RecentFilesModel.h>
#include <feather-tk/ui/RowLayout.h>

#include <feather-tk/core/Assert.h>
#include <feather-tk/core/Format.h>
#include <feather-tk/core/Time.h>

namespace feather_tk
{
    namespace ui_test
    {
        FileBrowserTest::FileBrowserTest(const std::shared_ptr<Context>& context) :
            ITest(context, "feather_tk::ui_test::FileBrowserTest")
        {}

        FileBrowserTest::~FileBrowserTest()
        {}

        std::shared_ptr<FileBrowserTest> FileBrowserTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileBrowserTest>(new FileBrowserTest(context));
        }
                
        void FileBrowserTest::run()
        {
            _enums();
            _shortcuts();
            _view();
            _widget();
            _dialog();
        }

        void FileBrowserTest::_enums()
        {
            FEATHER_TK_TEST_ENUM(FileBrowserSort);
        }

        void FileBrowserTest::_shortcuts()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, app, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto model = FileBrowserModel::create(context);
                auto panel = FileBrowserPanel::create(context, model, window);
                auto recentFilesModel = RecentFilesModel::create(context);
                recentFilesModel->addRecent(std::filesystem::current_path());
                panel->setRecentFilesModel(recentFilesModel);

                //! \bug Sleep a bit to wait for the drives model.
                sleep(std::chrono::milliseconds(500));
                window->setCursorEnter(true);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                app->tick(1000);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                app->tick(1000);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
            }
        }

        void FileBrowserTest::_view()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, app, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto model = FileBrowserModel::create(context);
                auto view = FileBrowserView::create(context, FileBrowserMode::File, model, window);
                std::filesystem::path path = std::filesystem::current_path();
                model->setPath(path);
                model->setPath(path);
                FEATHER_TK_ASSERT(path == model->getPath());
                view->reload();
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                model->setOptions(options);
                FEATHER_TK_ASSERT(options == model->getOptions());
                view->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                options.sort = FileBrowserSort::Extension;
                model->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Size;
                model->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Time;
                model->setOptions(options);
                app->tick();

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Down);
                window->setKey(Key::Up);
                window->setKey(Key::End);
                window->setKey(Key::Home);
                window->setKey(Key::Escape);
            }
        }

        void FileBrowserTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, app, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::filesystem::path path = std::filesystem::current_path();
                auto model = FileBrowserModel::create(context);
                auto fileBrowserWidget = FileBrowserWidget::create(
                    context,
                    path,
                    FileBrowserMode::File,
                    model,
                    window);
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                model->setOptions(options);
                FEATHER_TK_ASSERT(options == model->getOptions());
                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowserWidget->setRecentFilesModel(recentFilesModel);
                fileBrowserWidget->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                bool cancel = false;
                fileBrowserWidget->setCancelCallback(
                    [&cancel]
                    {
                        cancel = true;
                    });

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab);
                window->setKey(Key::Escape);

                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Down);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Down);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setText("Filter");
                window->setText("");
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
            }
        }

        void FileBrowserTest::_dialog()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileBrowserTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileBrowserTest",
                    "File browser test.");
                auto window = Window::create(context, app, "FileBrowserTest");
                app->addWindow(window);
                window->show();
                app->tick();

                std::filesystem::path path = std::filesystem::current_path();
                auto model = FileBrowserModel::create(context);
                auto fileBrowser = FileBrowser::create(context, path, FileBrowserMode::File, model);
                FileBrowserOptions options;
                options.reverseSort = true;
                model->setOptions(options);
                FEATHER_TK_ASSERT(model->getOptions() == options);
                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowser->setRecentFilesModel(recentFilesModel);
                FEATHER_TK_ASSERT(recentFilesModel == fileBrowser->getRecentFilesModel());
                fileBrowser->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                bool close = false;
                fileBrowser->setCloseCallback(
                    [&close]
                    {
                        close = true;
                    });

                fileBrowser->open(window);
                app->tick();
                FEATHER_TK_ASSERT(fileBrowser->isOpen());
                fileBrowser->close();
                app->tick();
                FEATHER_TK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                FEATHER_TK_ASSERT(fileBrowser->isOpen());
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                FEATHER_TK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                FEATHER_TK_ASSERT(fileBrowser->isOpen());
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                FEATHER_TK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
            }
        }
    }
}

