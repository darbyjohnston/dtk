// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Size.h>

namespace dtk
{
    nlohmann::json to_json(const Size2I& value)
    {
        return { value.w, value.h };
    }

    nlohmann::json to_json(const Size2F& value)
    {
        return { value.w, value.h };
    }

    nlohmann::json to_json(const Size3F& value)
    {
        return { value.w, value.h , value.d };
    }

    bool from_json(const nlohmann::json& json, Size2I& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            json.at(0).get_to(value.w);
            json.at(1).get_to(value.h);
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, Size2F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            json.at(0).get_to(value.w);
            json.at(1).get_to(value.h);
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, Size3F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 3 &&
            json.at(0).is_number() &&
            json.at(1).is_number() &&
            json.at(2).is_number())
        {
            json.at(0).get_to(value.w);
            json.at(1).get_to(value.h);
            json.at(2).get_to(value.d);
            out = true;
        }
        return out;
    }
}
