// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Range.h>

namespace dtk
{
    nlohmann::json to_json(const RangeI& value)
    {
        return { value.min(), value.max() };
    }

    nlohmann::json to_json(const RangeSizeT& value)
    {
        return { value.min(), value.max() };
    }

    nlohmann::json to_json(const RangeF& value)
    {
        return { value.min(), value.max() };
    }

    nlohmann::json to_json(const RangeD& value)
    {
        return { value.min(), value.max() };
    }

    bool from_json(const nlohmann::json& json, RangeI& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            value = RangeI(json.at(0).get<int>(), json.at(1).get<int>());
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, RangeSizeT& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            value = RangeSizeT(json.at(0).get<int>(), json.at(1).get<int>());
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, RangeF& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            value = RangeF(json.at(0).get<float>(), json.at(1).get<float>());
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, RangeD& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 2 &&
            json.at(0).is_number() &&
            json.at(1).is_number())
        {
            value = RangeD(json.at(0).get<double>(), json.at(1).get<double>());
            out = true;
        }
        return out;
    }
}
