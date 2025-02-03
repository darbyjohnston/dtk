// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "dialogs.h"

#include <dtk/ui/DialogSystem.h>
#include <dtk/ui/Divider.h>
#include <dtk/ui/FileBrowser.h>
#include <dtk/ui/FileEdit.h>
#include <dtk/ui/MenuBar.h>
#include <dtk/ui/PushButton.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Settings.h>

#include <dtk/core/Format.h>

void DialogsWindow::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app,
    const std::string& name,
    const Size2I& size)
{
    MainWindow::_init(context, app, name, size);

    // Create the menus.
    auto menu = getMenuBar()->getMenu("File");
    menu->clear();
    menu->addItem(std::make_shared<Action>(
        "Open",
        Key::O,
        static_cast<int>(commandKeyModifier),
        [this]
        {
            if (auto context = getContext())
            {
                if (auto fileBrowserSystem = context->getSystem<FileBrowserSystem>())
                {
                    fileBrowserSystem->open(
                        getWindow(),
                        [this](const std::filesystem::path& value)
                        {
                            std::cout << value.u8string() << std::endl;
                        });
                }
            }
        }));
    auto action = std::make_shared<Action>(
        "Close",
        Key::E,
        static_cast<int>(commandKeyModifier),
        [] {});
    menu->addItem(action);
    menu->setItemEnabled(action, false);
    menu->addDivider();
    menu->addItem(std::make_shared<Action>(
        "Exit",
        Key::Q,
        static_cast<int>(commandKeyModifier),
        [this]
        {
            _getApp()->exit();
        }));

    // Create the layout.
    auto layout = VerticalLayout::create(context);
    layout->setMarginRole(SizeRole::Margin);
    setWidget(layout);

    // Message dialog.
    auto button = PushButton::create(context, "Message Dialog", layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->message(
                    "Message",
                    "Hello world!",
                    std::dynamic_pointer_cast<DialogsWindow>(shared_from_this()));
            }
        });

    // Confirmation dialog.
    button = PushButton::create(context, "Confirmation Dialog", layout);
    button->setClickedCallback(
        [this]
        {
            if (auto context = getContext())
            {
                context->getSystem<DialogSystem>()->confirm(
                    "Confirm",
                    "Hello world?",
                    std::dynamic_pointer_cast<DialogsWindow>(shared_from_this()),
                    [](bool value)
                    {
                        std::cout << "Hello world: " << value << std::endl;
                    });
            }
        });

    // Progress dialog.
    _progressTimer = Timer::create(context);
    _progressTimer->setRepeating(true);
    button = PushButton::create(context, "Progress Dialog", layout);
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
    auto fileEdit = FileEdit::create(context, layout);
    fileEdit->setRecentFilesModel(recentFilesModel);
    fileEdit->setPath("File Browser");
}

DialogsWindow::DialogsWindow()
{}

DialogsWindow::~DialogsWindow()
{}

std::shared_ptr<Window> DialogsWindow::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<App>& app,
    const std::string& name,
    const Size2I& size)
{
    auto out = std::shared_ptr<DialogsWindow>(new DialogsWindow);
    out->_init(context, app, name, size);
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
            getSettingsPath("dtk", "dialogs.settings").u8string());
        if (app->getExit() != 0)
            return app->getExit();

        // Disable the native file dialog.
        context->getSystem<dtk::FileBrowserSystem>()->setNativeFileDialog(false);

        // Create the window.
        auto window = DialogsWindow::create(
            context,
            app,
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

