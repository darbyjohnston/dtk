// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace dtk
{
    std::vector<std::string> getFontResources();
    std::vector<uint8_t> getFontResource(const std::string&);

    std::vector<std::string> getIconResources();
    std::vector<uint8_t> getIconResource(const std::string&);
}
