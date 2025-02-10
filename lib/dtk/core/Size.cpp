// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Size.h>

namespace dtk
{
    void to_json(nlohmann::json& json, const Size2I& value)
    {
        json = { value.w, value.h };
    }

    void to_json(nlohmann::json& json, const Size2F& value)
    {
        json = { value.w, value.h };
    }

    void to_json(nlohmann::json& json, const Size3F& value)
    {
        json = { value.w, value.h , value.d };
    }

    void from_json(const nlohmann::json& json, Size2I& value)
    {
        json.at(0).get_to(value.w);
        json.at(1).get_to(value.h);
    }

    void from_json(const nlohmann::json& json, Size2F& value)
    {
        json.at(0).get_to(value.w);
        json.at(1).get_to(value.h);
    }

    void from_json(const nlohmann::json& json, Size3F& value)
    {
        json.at(0).get_to(value.w);
        json.at(1).get_to(value.h);
        json.at(2).get_to(value.d);
    }
}
