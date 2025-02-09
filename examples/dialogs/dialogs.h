// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/App.h>
#include <dtk/ui/ProgressDialog.h>
#include <dtk/ui/MainWindow.h>
#include <dtk/ui/RecentFilesModel.h>
#include <dtk/ui/Settings.h>

#include <dtk/core/Timer.h>

using namespace dtk;

class DialogsWindow : public MainWindow
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&,
        const std::string& name,
        const Size2I&);

    DialogsWindow() = default;

public:
    virtual ~DialogsWindow();

    static std::shared_ptr<Window> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&,
        const std::string& name,
        const Size2I&);

private:
    std::shared_ptr<Settings> _settings;
    std::shared_ptr<Timer> _progressTimer;
    std::shared_ptr<ProgressDialog> _progressDialog;
    std::shared_ptr<RecentFilesModel> _recentFilesModel;
};