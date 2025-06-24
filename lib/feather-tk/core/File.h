// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Util.h>

#include <filesystem>
#include <iostream>
#include <vector>

namespace feather_tk
{
    //! \name Files
    ///@{

    //! Split a path.
    std::vector<std::string> split(std::filesystem::path);

    //! Get the list of file system drives.
    std::vector<std::filesystem::path> getDrives();

    //! User paths.
    enum class UserPath
    {
        Home,
        Desktop,
        Documents,
        Downloads,

        Count,
        First = Home
    };
    FEATHER_TK_ENUM(UserPath);

    //! Get a user path.
    std::filesystem::path getUserPath(UserPath);
        
    ///@}
}
