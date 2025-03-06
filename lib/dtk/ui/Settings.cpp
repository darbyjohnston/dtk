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
                try
                {
                    p.settings = nlohmann::json::parse(contents);
                }
                catch (const std::exception&)
                {}
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

    const std::filesystem::path& Settings::getPath() const
    {
        return _p->path;
    }

    bool Settings::contains(const std::string& key) const
    {
        DTK_P();
        return p.settings.find(key) != p.settings.end();
    }

    bool Settings::get(const std::string& key, nlohmann::json& value) const
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, bool& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_boolean())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, int& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_number_integer())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, int64_t& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_number_integer())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, float& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_number_float())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, double& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_number_float())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, size_t& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_number_unsigned())
        {
            value = *i;
            return true;
        }
        return false;
    }

    bool Settings::get(const std::string& key, std::string& value)
    {
        DTK_P();
        const auto i = p.settings.find(key);
        if (i != p.settings.end() && i->is_string())
        {
            value = *i;
            return true;
        }
        return false;
    }

    void Settings::set(const std::string& key, const nlohmann::json& value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, bool value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, int value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, int64_t value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, float value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, double value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, size_t value)
    {
        DTK_P();
        p.settings[key] = value;
    }

    void Settings::set(const std::string& key, const std::string& value)
    {
        DTK_P();
        p.settings[key] = value;
    }
}