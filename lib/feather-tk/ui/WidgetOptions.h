// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Util.h>

#include <iostream>
#include <string>
#include <vector>

namespace feather_tk
{
    //! Orientation.
    enum class Orientation
    {
        Horizontal,
        Vertical,

        Count,
        First = Horizontal
    };
    FEATHER_TK_ENUM(Orientation);

    //! Layout stretch.
    enum class Stretch
    {
        Fixed,
        Expanding,

        Count,
        First = Fixed
    };
    FEATHER_TK_ENUM(Stretch);

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
    FEATHER_TK_ENUM(HAlign);

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
    FEATHER_TK_ENUM(VAlign);

    //! Updates.
    enum class Update
    {
        None = 0,
        Size = 1,
        Draw = 2
    };
}