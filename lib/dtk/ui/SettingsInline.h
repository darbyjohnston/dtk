// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace dtk
{
    template<typename T>
    inline bool Settings::getT(const std::string& key, T& value) const
    {
        return get(key, json) && from_json(json, value);
    }

    template<typename T>
    inline void Settings::setT(const std::string& key, const T& value)
    {
        set(key, to_json(value));
    }
}
