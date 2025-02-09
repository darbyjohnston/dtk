// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace dtk
{
    template<typename T>
    inline void Settings::get(const std::string& key, T& value) const
    {
        nlohmann::json json = get(key);
        from_json(json, value);
    }

    template<typename T>
    inline void Settings::set(const std::string& key, const T& value)
    {
        nlohmann::json json;
        to_json(json, value);
        set(key, json);
    }
}
