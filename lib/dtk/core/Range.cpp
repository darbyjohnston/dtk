// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Range.h>

namespace dtk
{
    void to_json(nlohmann::json& json, const RangeI& value)
    {
        json = { value.min(), value.max() };
    }

    void to_json(nlohmann::json& json, const RangeSizeT& value)
    {
        json = { value.min(), value.max() };
    }

    void to_json(nlohmann::json& json, const RangeF& value)
    {
        json = { value.min(), value.max() };
    }

    void to_json(nlohmann::json& json, const RangeD& value)
    {
        json = { value.min(), value.max() };
    }

    void from_json(const nlohmann::json& json, RangeI& value)
    {
        value = RangeI(json.at(0).get<int>(), json.at(1).get<int>());
    }

    void from_json(const nlohmann::json& json, RangeSizeT& value)
    {
        value = RangeSizeT(json.at(0).get<int>(), json.at(1).get<int>());
    }

    void from_json(const nlohmann::json& json, RangeF& value)
    {
        value = RangeF(json.at(0).get<float>(), json.at(1).get<float>());
    }

    void from_json(const nlohmann::json& json, RangeD& value)
    {
        value = RangeD(json.at(0).get<double>(), json.at(1).get<double>());
    }
}
