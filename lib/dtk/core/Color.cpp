// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Color.h>

namespace dtk
{
    void to_json(nlohmann::json& json, const Color1F& value)
    {
        json = { value.l };
    }

    void to_json(nlohmann::json& json, const Color2F& value)
    {
        json = { value.l, value.a };
    }

    void to_json(nlohmann::json& json, const Color3F& value)
    {
        json = { value.r, value.g, value.b };
    }

    void to_json(nlohmann::json& json, const Color4F& value)
    {
        json = { value.r, value.g, value.b, value.a };
    }

    void from_json(const nlohmann::json& json, Color1F& value)
    {
        json.at(0).get_to(value.l);
    }

    void from_json(const nlohmann::json& json, Color2F& value)
    {
        json.at(0).get_to(value.l);
        json.at(1).get_to(value.a);
    }

    void from_json(const nlohmann::json& json, Color3F& value)
    {
        json.at(0).get_to(value.r);
        json.at(1).get_to(value.g);
        json.at(2).get_to(value.b);
    }

    void from_json(const nlohmann::json& json, Color4F& value)
    {
        json.at(0).get_to(value.r);
        json.at(1).get_to(value.g);
        json.at(2).get_to(value.b);
        json.at(3).get_to(value.a);
    }
}
