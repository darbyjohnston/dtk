// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/ui/IClipboard.h>

namespace feather_tk
{
    void IClipboard::_init(const std::shared_ptr<Context>& context)
    {
        _context = context;
    }

    IClipboard::IClipboard()
    {}

    IClipboard::~IClipboard()
    {}
}
