// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Util.h>

#include <nlohmann/json.hpp>

#include <filesystem>
#include <memory>

namespace feather_tk
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

        //! Get the settings path.
        const std::filesystem::path& getPath() const;

        //! Do the settings contain the given value?
        bool contains(const std::string& key) const;

        //! \name Get Values
        ///@{

        bool get(const std::string& key, nlohmann::json&) const;

        bool get(const std::string& key, bool&);
        bool get(const std::string& key, int&);
        bool get(const std::string& key, int64_t&);
        bool get(const std::string& key, float&);
        bool get(const std::string& key, double&);
        bool get(const std::string& key, size_t&);
        bool get(const std::string& key, std::string&);

        template<typename T>
        bool getT(const std::string& key, T&) const;

        ///@}

        //! \name Set Values
        ///@{

        void set(const std::string& key, const nlohmann::json&);

        void set(const std::string& key, bool);
        void set(const std::string& key, int);
        void set(const std::string& key, int64_t);
        void set(const std::string& key, float);
        void set(const std::string& key, double);
        void set(const std::string& key, size_t);
        void set(const std::string& key, const std::string&);

        template<typename T>
        void setT(const std::string& key, const T&);

        ///@}

    private:
        FEATHER_TK_PRIVATE();
    };
}

#include <feather-tk/ui/SettingsInline.h>