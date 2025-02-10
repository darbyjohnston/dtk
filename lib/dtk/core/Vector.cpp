// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Vector.h>

namespace dtk
{
    nlohmann::json to_json(const V2I& value)
    {
        return { value.x, value.y };
    }

    nlohmann::json to_json(const V2F& value)
    {
        return { value.x, value.y };
    }

    nlohmann::json to_json(const V3F& value)
    {
        return { value.x, value.y, value.z };
    }

    nlohmann::json to_json(const V4F& value)
    {
        return { value.x, value.y, value.z, value.w };
    }

    bool from_json(const nlohmann::json& json, V2I& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            json.at(0).get_to(value.x);
            json.at(1).get_to(value.y);
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, V2F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            json.at(0).get_to(value.x);
            json.at(1).get_to(value.y);
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, V3F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 3 &&
            json.at(0).is_number() &&
            json.at(1).is_number() &&
            json.at(2).is_number())
        {
            json.at(0).get_to(value.x);
            json.at(1).get_to(value.y);
            json.at(2).get_to(value.z);
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, V4F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 4 &&
            json.at(0).is_number() &&
            json.at(1).is_number() &&
            json.at(2).is_number() &&
            json.at(3).is_number())
        {
            json.at(0).get_to(value.x);
            json.at(1).get_to(value.y);
            json.at(2).get_to(value.z);
            json.at(3).get_to(value.w);
            out = true;
        }
        return out;
    }
}
