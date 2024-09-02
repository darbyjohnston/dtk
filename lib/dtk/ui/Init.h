// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace dtk
{
    namespace core
    {
        class Context;
    }

    //! User interface
    namespace ui
    {
        //! Initialize the library.
        void init(const std::shared_ptr<core::Context>&);
    }
}

