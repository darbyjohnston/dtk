// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <memory>

namespace dtk
{
    class Context;

    //! Initialize the core library.
    void coreInit(const std::shared_ptr<Context>&);
}

