// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <filesystem>
#include <memory>

namespace dtk
{
    class Context;

    //! Initialize the UI library.
    void uiInit(
        const std::shared_ptr<Context>&,
        const std::filesystem::path& settingsPath = std::filesystem::path());
}

