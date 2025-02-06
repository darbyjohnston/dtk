// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

#include <dtk/gl/OffscreenBuffer.h>
#include <dtk/gl/Shader.h>

#include <dtk/core/Timer.h>

using namespace dtk;

class OffscreenWidget : public IWidget
{
protected:
    void _init(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>& parent);

    OffscreenWidget() = default;

public:
    virtual ~OffscreenWidget();

    static std::shared_ptr<OffscreenWidget> create(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<IWidget>& parent = nullptr);

    void drawEvent(const Box2I&, const DrawEvent&) override;

private:
    float _rotation = 0.F;
    std::shared_ptr<Timer> _timer;
    bool _doRender = true;
    std::shared_ptr<gl::Shader> _shader;
    std::shared_ptr<gl::OffscreenBuffer> _buffer;
};