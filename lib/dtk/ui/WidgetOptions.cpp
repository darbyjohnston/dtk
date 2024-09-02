// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/WidgetOptions.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <algorithm>
#include <array>

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
        "Left",
        "Center",
        "Right");

    DTK_ENUM_IMPL(
        VAlign,
        "Top",
        "Center",
        "Bottom");
}
