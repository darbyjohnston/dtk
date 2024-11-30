// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/ProgressDialog.h>
#include <dtk/ui/RowLayout.h>
#include <dtk/ui/Settings.h>
#include <dtk/ui/Window.h>

#include <dtk/core/Timer.h>

using namespace dtk;

class MainWindow : public Window
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::string& name,
        const Size2I&,
        const std::shared_ptr<Settings>&);

    MainWindow();

public:
    virtual ~MainWindow();

    static std::shared_ptr<Window> create(
        const std::shared_ptr<Context>&,
        const std::string& name,
        const Size2I&,
        const std::shared_ptr<Settings>&);

private:
    std::shared_ptr<VerticalLayout> _layout;
    std::shared_ptr<Timer> _progressTimer;
    std::shared_ptr<ProgressDialog> _progressDialog;
};