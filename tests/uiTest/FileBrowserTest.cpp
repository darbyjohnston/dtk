// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <uiTest/FileBrowserTest.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/FileBrowserPrivate.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/RowLayout.h>

#include <dtk/core/Assert.h>
#include <dtk/core/Format.h>
#include <dtk/core/Time.h>

namespace dtk
{
    namespace ui_test
    {
        FileBrowserTest::FileBrowserTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FileBrowserTest")
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
            DTK_TEST_ENUM(FileBrowserSort);
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

                auto widget = FileBrowserShortcuts::create(context, window);
                std::filesystem::path path;
                widget->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });
                auto recentFilesModel = RecentFilesModel::create(context);
                recentFilesModel->addRecent(std::filesystem::current_path());
                widget->setRecentFilesModel(recentFilesModel);

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

                auto view = FileBrowserView::create(context, FileBrowserMode::File, window);
                std::filesystem::path path = std::filesystem::current_path();
                view->setPath(path);
                view->setPath(path);
                DTK_ASSERT(path == view->getPath());
                view->reload();
                FileBrowserOptions options;
                options.reverseSort = true;
                view->setOptions(options);
                view->setOptions(options);
                DTK_ASSERT(options == view->getOptions());
                view->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                options.sort = FileBrowserSort::Extension;
                view->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Size;
                view->setOptions(options);
                app->tick();
                options.sort = FileBrowserSort::Time;
                view->setOptions(options);
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
                auto fileBrowserWidget = FileBrowserWidget::create(context, path, FileBrowserMode::File, window);
                DTK_ASSERT(path == fileBrowserWidget->getPath());
                FileBrowserOptions options;
                options.reverseSort = true;
                fileBrowserWidget->setOptions(options);
                fileBrowserWidget->setOptions(options);
                DTK_ASSERT(options == fileBrowserWidget->getOptions());
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
                auto fileBrowser = FileBrowser::create(context, path);
                DTK_ASSERT(path == fileBrowser->getPath());
                FileBrowserOptions options;
                options.reverseSort = true;
                fileBrowser->setOptions(options);
                DTK_ASSERT(fileBrowser->getOptions() == options);
                auto recentFilesModel = RecentFilesModel::create(context);
                fileBrowser->setRecentFilesModel(recentFilesModel);
                DTK_ASSERT(recentFilesModel == fileBrowser->getRecentFilesModel());
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
                DTK_ASSERT(fileBrowser->isOpen());
                fileBrowser->close();
                app->tick();
                DTK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                DTK_ASSERT(fileBrowser->isOpen());
                window->setKey(Key::Escape);
                window->setKey(Key::Escape);
                DTK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                DTK_ASSERT(fileBrowser->isOpen());
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
                DTK_ASSERT(!fileBrowser->isOpen());

                fileBrowser->open(window);
                app->tick();
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);
            }
        }
    }
}

