// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/WidgetOptions.h>

#include <feather-tk/core/Box.h>

namespace feather_tk
{
    //! \name Layouts
    ///@{
        
    //! Align within the given box.
    Box2I align(
        const Box2I&  box,
        const Size2I& sizeHint,
        HAlign        hAlign,
        VAlign        vAlign);

    //! Get a format string for the given number.
    std::string format(int);

    //! Get a format string for the given number.
    std::string format(float, int precision);
        
    ///@}
}
