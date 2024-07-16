// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/IClipboard.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
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
}
