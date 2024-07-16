// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/RenderOptions.h>

#include <dtkCore/Error.h>
#include <dtkCore/String.h>

#include <algorithm>
#include <array>

namespace dtk
{
    namespace core
    {
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
}
