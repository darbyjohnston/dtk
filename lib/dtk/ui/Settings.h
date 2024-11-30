// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <any>
#include <filesystem>
#include <memory>
#include <string>

namespace dtk
{
    //! Get a settings path.
    std::filesystem::path getSettingsPath(
        const std::string& directory,
        const std::string& fileName);

    //! Settings.
    class Settings : public std::enable_shared_from_this<Settings>
    {
    protected:
        Settings(const std::filesystem::path&);

    public:
        ~Settings();

        //! Create a new settings.
        static std::shared_ptr<Settings> create(const std::filesystem::path&);

        //! Get a value.
        std::any get(const std::string& key);

        //! Set a value.
        void set(const std::string& key, const std::any& value);

    private:
        DTK_PRIVATE();
    };
}
