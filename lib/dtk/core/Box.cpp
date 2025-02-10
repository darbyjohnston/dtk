// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Box.h>

namespace dtk
{
    nlohmann::json to_json(const Box2I& value)
    {
        return { to_json(value.min), to_json(value.max) };
    }

    nlohmann::json to_json(const Box2F& value)
    {
        return { to_json(value.min), to_json(value.max) };
    }

    nlohmann::json to_json(const Box3F& value)
    {
        return { to_json(value.min), to_json(value.max) };
    }

    void from_json(const nlohmann::json& json, Box2I& value)
    {
        from_json(json.at(0), value.min);
        from_json(json.at(1), value.max);
    }

    void from_json(const nlohmann::json& json, Box2F& value)
    {
        from_json(json.at(0), value.min);
        from_json(json.at(1), value.max);
    }

    void from_json(const nlohmann::json& json, Box3F& value)
    {
        from_json(json.at(0), value.min);
        from_json(json.at(1), value.max);
    }
}
