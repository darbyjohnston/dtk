// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "dialogs.h"

#include <dtk/ui/App.h>
#include <dtk/ui/DialogSystem.h>
#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/FileEdit.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/Settings.h>

#include <dtk/core/Format.h>

void MainWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    Window::_init(context, name, size);

    // Create the layout.
    _layout = VerticalLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    // Message dialog.
    auto button = PushButton::create(context, "Message Dialog", _layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->message(
                    "Message",
                    "Hello world!",
                    std::dynamic_pointer_cast<MainWindow>(shared_from_this()));
            }
        });

    // Confirmation dialog.
    button = PushButton::create(context, "Confirmation Dialog", _layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->confirm(
                    "Confirm",
                    "Hello world?",
                    std::dynamic_pointer_cast<MainWindow>(shared_from_this()),
                    [](bool value)
                    {
                        std::cout << "Hello world: " << value << std::endl;
                    });
            }
        });

    // Progress dialog.
    _progressTimer = Timer::create(context);
    _progressTimer->setRepeating(true);
    button = PushButton::create(context, "Progress Dialog", _layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                const double inc = 0.005;
                const double max = 1.0;
                _progressDialog = ProgressDialog::create(
                    context,
                    "Progress",
                    "In progress:");
                _progressDialog->setMessage(Format("{0} / {1}").arg(0).arg(int(max / inc)));
                _progressDialog->setCloseCallback(
                    [this]
                    {
                        _progressTimer->stop();
                        _progressDialog.reset();
                    });
                _progressDialog->open(std::dynamic_pointer_cast<IWindow>(shared_from_this()));
                _progressTimer->start(
                    std::chrono::microseconds(500),
                    [this, max, inc]
                    {
                        double v = _progressDialog->getValue();
                        v += 0.005;
                        if (v < 1.0)
                        {
                            _progressDialog->setValue(v);
                            _progressDialog->setMessage(
                                Format("{0} / {1}").arg(v * (max / inc)).arg(int(max / inc)));
                        }
                        else
                        {
                            _progressDialog->close();
                        }
                    });
            }
        });

    // File browser.
    auto recentFilesModel = RecentFilesModel::create(context);
    auto fileEdit = FileEdit::create(context, _layout);
    fileEdit->setRecentFilesModel(recentFilesModel);
    fileEdit->setPath("File Browser");
}

MainWindow::MainWindow()
{}

MainWindow::~MainWindow()
{}

std::shared_ptr<Window> MainWindow::create(
    const std::shared_ptr<Context>& context,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<MainWindow>(new MainWindow);
    out->_init(context, name, size);
    return out;
}

DTK_MAIN()
{
    try
    {
        auto context = Context::create();
        auto args = convert(argc, argv);
        auto app = App::create(
            context,
            args,
            "dialogs",
            "Dialogs example",
            {},
            {},
            getSettingsPath("dtk", "dialogs.settings").string());
        if (app->getExit() != 0)
            return app->getExit();

        // Disable the native file dialog.
        context->getSystem<dtk::FileBrowserSystem>()->setNativeFileDialog(false);

        // Create the window.
        auto window = MainWindow::create(
            context,
            "dialogs",
            Size2I(1280, 960));
        app->addWindow(window);

        window->show();
        app->run();
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

