// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dtk
{
    //! Get the list of font resources.
    std::vector<std::string> getFontResources();

    //! Get a font resource.
    std::vector<uint8_t> getFontResource(const std::string&);

    //! Get the list of icon resources.
    std::vector<std::string> getIconResources();

    //! Get an icon resource.
    std::vector<uint8_t> getIconResource(const std::string&);
}
