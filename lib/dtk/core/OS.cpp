// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/OS.h>

#include <dtk/core/String.h>

namespace dtk
{
    bool getEnv(const std::string& name, int& out)
    {
        std::string value;
        if (getEnv(name, value))
        {
            out = !value.empty() ? std::stoi(value) : 0;
            return true;
        }
        return false;
    }

    bool getEnv(const std::string& name, std::vector<std::string>& out)
    {
        std::string value;
        if (getEnv(name, value))
        {
            out = split(value, envListSeparator);
            return true;
        }
        return false;
    }
}