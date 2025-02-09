// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <nlohmann/json.hpp>

#include <filesystem>
#include <memory>

namespace dtk
{
    class Context;

    //! Get a settings path.
    std::filesystem::path getSettingsPath(
        const std::string& directory,
        const std::string& fileName);

    //! Settings.
    class Settings : public std::enable_shared_from_this<Settings>
    {
    protected:
        Settings(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            bool reset);

    public:
        ~Settings();

        //! Create new settings.
        static std::shared_ptr<Settings> create(
            const std::shared_ptr<Context>&,
            const std::filesystem::path&,
            bool reset = false);

        //! Get a value.
        nlohmann::json get(const std::string& key);

        //! Set a value.
        void set(const std::string& key, const nlohmann::json& value);

    private:
        DTK_PRIVATE();
    };
}
