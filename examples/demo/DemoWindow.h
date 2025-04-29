// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/Action.h>
#include <dtk/ui/App.h>
#include <dtk/ui/MainWindow.h>

using namespace dtk;

class DemoWindow : public MainWindow
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&);

    DemoWindow() = default;

public:
    virtual ~DemoWindow();

    static std::shared_ptr<DemoWindow> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<App>&);

    void update(
        const std::shared_ptr<FontSystem>&,
        const std::shared_ptr<IconSystem>&,
        const std::shared_ptr<Style>&) override;

private:
    void _screenshot();
    void _screenshot(const std::filesystem::path&);

    std::map<std::string, std::shared_ptr<Action> > _actions;
    std::filesystem::path _screenshotPath = "screenshot.png";
    bool _doScreenshot = true;
};