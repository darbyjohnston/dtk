// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/File.h>

#include <dtkCore/Error.h>
#include <dtkCore/String.h>

#include <algorithm>
#include <array>

namespace dtk
{
    namespace core
    {
        DTK_ENUM_IMPL(
            UserPath,
            "Home",
            "Desktop",
            "Documents",
            "Downloads");
    }
}

