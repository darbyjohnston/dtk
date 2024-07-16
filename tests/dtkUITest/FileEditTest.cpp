// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUITest/FileEditTest.h>

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkUI/FileBrowser.h>
#include <dtkUI/FileEdit.h>
#include <dtkUI/RowLayout.h>

#include <dtkCore/Assert.h>
#include <dtkCore/Format.h>

using namespace dtk::core;
using namespace dtk::ui;

namespace dtk
{
    namespace ui_test
    {
        FileEditTest::FileEditTest(const std::shared_ptr<Context>& context) :
            ITest(context, "dtk::ui_test::FileEditTest")
        {}

        FileEditTest::~FileEditTest()
        {}

        std::shared_ptr<FileEditTest> FileEditTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<FileEditTest>(new FileEditTest(context));
        }

        void FileEditTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("FileEditTest");
                auto app = App::create(
                    context,
                    argv,
                    "FileEditTest",
                    "File edit test.");
                auto window = Window::create(context, app, "FileEditTest");
                auto layout = VerticalLayout::create(context, window);
                layout->setMarginRole(SizeRole::MarginLarge);
                app->addWindow(window);
                window->show();
                app->tick();

                auto edit = FileEdit::create(context, layout);
                std::filesystem::path path = std::filesystem::current_path();
                edit->setPath(path);
                edit->setPath(path);
                DTK_ASSERT(path == edit->getPath());
                edit->setCallback(
                    [&path](const std::filesystem::path& value)
                    {
                        path = value;
                    });

                auto system = context->getSystem<FileBrowserSystem>();
                system->setNativeFileDialog(false);
                DTK_ASSERT(!system->isNativeFileDialog());
                system->setPath(path);
                DTK_ASSERT(path == system->getPath());
                FileBrowserOptions options;
                options.reverseSort = true;
                system->setOptions(options);
                DTK_ASSERT(options == system->getOptions());
                DTK_ASSERT(system->getRecentFilesModel());

                window->setCursorEnter(true);
                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);

                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
                window->setKey(Key::Tab, static_cast<int>(KeyModifier::Shift));
                window->setKey(Key::Enter);

                window->setKey(Key::Tab);
                window->setKey(Key::Tab);
                window->setKey(Key::Enter);
            }
        }
    }
}

