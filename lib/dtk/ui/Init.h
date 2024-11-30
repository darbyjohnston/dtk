// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace dtk
{
    class Context;
    class Settings;

    //! Initialize the UI library.
    void uiInit(
        const std::shared_ptr<Context>&,
        const std::shared_ptr<Settings>& = nullptr);
}

