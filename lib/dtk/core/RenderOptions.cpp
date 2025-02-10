// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/RenderOptions.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <algorithm>
#include <array>
#include <sstream>

namespace dtk
{
    DTK_ENUM_IMPL(
        ChannelDisplay,
        "Color",
        "Red",
        "Green",
        "Blue",
        "Alpha");

    DTK_ENUM_IMPL(
        InputVideoLevels,
        "FromFile",
        "FullRange",
        "LegalRange");

    DTK_ENUM_IMPL(
        AlphaBlend,
        "None",
        "Straight",
        "Premultiplied");

    DTK_ENUM_IMPL(
        ImageFilter,
        "Nearest",
        "Linear");
}
