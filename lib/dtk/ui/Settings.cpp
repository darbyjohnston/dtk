// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Settings.h>

#include <dtk/core/File.h>
#include <dtk/core/FileIO.h>

#include <map>

namespace dtk
{
    std::filesystem::path getSettingsPath(
        const std::string& directory,
        const std::string& fileName)
    {
        return getUserPath(UserPath::Documents) / directory / fileName;
    }

    struct Settings::Private
    {
        std::filesystem::path path;
        nlohmann::json settings;
    };

    Settings::Settings(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        bool reset) :
        _p(new Private)
    {
        DTK_P();

        p.path = path;

        if (!p.path.empty())
        {
            if (p.path.has_parent_path())
            {
                std::filesystem::create_directories(p.path.parent_path());
            }
            if (std::filesystem::exists(p.path) && !reset)
            {
                const std::string contents = read(FileIO::create(p.path, FileMode::Read));
                p.settings = nlohmann::json::parse(contents);
            }
        }
    }

    Settings::~Settings()
    {
        DTK_P();
        if (!p.path.empty())
        {
            try
            {
                FileIO::create(p.path, FileMode::Write)->write(p.settings.dump(4));
            }
            catch (const std::exception&)
            {}
        }
    }

    std::shared_ptr<Settings> Settings::create(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path,
        bool reset)
    {
        return std::shared_ptr<Settings>(new Settings(context, path, reset));
    }

    nlohmann::json Settings::get(const std::string& key)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i == p.settings.end())
        {
            p.settings[key] = nlohmann::json();
        }
        return p.settings[key];
    }

    void Settings::set(const std::string& key, const nlohmann::json& value)
    {
        DTK_P();
        p.settings[key] = value;
    }
}