// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <iostream>
#include <string>
#include <vector>

namespace dtk
{
    //! Orientation.
    enum class Orientation
    {
        Horizontal,
        Vertical,

        Count,
        First = Horizontal
    };
    DTK_ENUM(Orientation);

    //! Layout stretch.
    enum class Stretch
    {
        Fixed,
        Expanding,

        Count,
        First = Fixed
    };
    DTK_ENUM(Stretch);

    //! Horizontal alignment.
    enum class HAlign
    {
        Fill,
        Left,
        Center,
        Right,

        Count,
        First = Left
    };
    DTK_ENUM(HAlign);

    //! Vertical alignment.
    enum class VAlign
    {
        Fill,
        Top,
        Center,
        Bottom,

        Count,
        First = Top
    };
    DTK_ENUM(VAlign);

    //! Updates.
    enum class Update
    {
        None = 0,
        Size = 1,
        Draw = 2
    };
}