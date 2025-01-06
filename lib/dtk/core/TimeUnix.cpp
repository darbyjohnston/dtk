// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Time.h>

#include <thread>

namespace dtk
{
    void sleep(const std::chrono::microseconds& value)
    {
        std::this_thread::sleep_for(value);
    }
}
