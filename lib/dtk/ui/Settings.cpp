// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Settings.h>

#include <dtk/core/File.h>
#include <dtk/core/FileIO.h>

#include <nlohmann/json.hpp>

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
        std::map<std::string, std::any> settings;
    };

    Settings::Settings(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path) :
        ISystem(context, "dtk::Settings"),
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
            nlohmann::json json;
            if (std::filesystem::exists(p.path))
            {
                const std::string contents = read(FileIO::create(p.path, FileMode::Read));
                json = nlohmann::json::parse(contents);
            }
            if (json.is_object())
            {
                for (auto i = json.begin(); i != json.end(); ++i)
                {
                    p.settings[i.key()] = i.value();
                }
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
                nlohmann::json json;
                for (const auto& i : p.settings)
                {
                    json[i.first] = std::any_cast<nlohmann::json>(i.second);
                }

                FileIO::create(p.path, FileMode::Write)->write(json.dump(4));
            }
            catch (const std::exception&)
            {
            }
        }
    }

    std::shared_ptr<Settings> Settings::create(
        const std::shared_ptr<Context>& context,
        const std::filesystem::path& path)
    {
        auto out = std::shared_ptr<Settings>(new Settings(context, path));
        return out;
    }

    std::any Settings::get(const std::string& key)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i == p.settings.end())
        {
            p.settings[key] = nlohmann::json();
        }
        return p.settings[key];
    }

    void Settings::set(const std::string& key, const std::any& value)
    {
        DTK_P();
        p.settings[key] = value;
    }
}