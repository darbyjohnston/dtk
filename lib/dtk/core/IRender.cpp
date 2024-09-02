// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/IRender.h>

namespace dtk
{
    void IRender::_init(const std::shared_ptr<Context>& context)
    {
        _context = context;
    }

    IRender::~IRender()
    {}
}
