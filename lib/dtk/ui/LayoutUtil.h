// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/WidgetOptions.h>

#include <dtk/core/Box.h>

namespace dtk
{
    //! \name Layouts
    ///@{
        
    //! Align within the given box.
    Box2I align(
        const Box2I&  box,
        const Size2I& sizeHint,
        Stretch             hStretch,
        Stretch             vStretch,
        HAlign              hAlign,
        VAlign              vAlign);

    //! Get a format string for the given number.
    std::string format(int);

    //! Get a format string for the given number.
    std::string format(float, int precision);
        
    ///@}
}
