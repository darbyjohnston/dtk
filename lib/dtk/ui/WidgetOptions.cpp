// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/WidgetOptions.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <algorithm>
#include <array>
#include <sstream>

namespace dtk
{
    DTK_ENUM_IMPL(
        Orientation,
        "Horizontal",
        "Vertical");

    DTK_ENUM_IMPL(
        Stretch,
        "Fixed",
        "Expanding");

    DTK_ENUM_IMPL(
        HAlign,
        "Fill",
        "Left",
        "Center",
        "Right");

    DTK_ENUM_IMPL(
        VAlign,
        "Fill",
        "Top",
        "Center",
        "Bottom");
}
