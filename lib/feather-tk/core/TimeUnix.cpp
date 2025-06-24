// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <feather-tk/core/Time.h>

#include <thread>

namespace feather-tk
{
    void sleep(const std::chrono::microseconds& value)
    {
        std::this_thread::sleep_for(value);
    }
}
