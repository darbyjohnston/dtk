// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/WidgetOptions.h>

#include <dtkCore/Error.h>
#include <dtkCore/String.h>

#include <algorithm>
#include <array>

namespace dtk
{
    namespace ui
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
}

