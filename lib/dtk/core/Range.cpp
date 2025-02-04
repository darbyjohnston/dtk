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
        int min = 0;
        int max = 0;
        json.at(0).get_to(min);
        json.at(1).get_to(max);
        value = RangeI(min, max);
    }

    void from_json(const nlohmann::json& json, RangeSizeT& value)
    {
        size_t min = 0;
        size_t max = 0;
        json.at(0).get_to(min);
        json.at(1).get_to(max);
        value = RangeSizeT(min, max);
    }

    void from_json(const nlohmann::json& json, RangeF& value)
    {
        float min = 0.F;
        float max = 0.F;
        json.at(0).get_to(min);
        json.at(1).get_to(max);
        value = RangeF(min, max);
    }

    void from_json(const nlohmann::json& json, RangeD& value)
    {
        double min = 0.0;
        double max = 0.0;
        json.at(0).get_to(min);
        json.at(1).get_to(max);
        value = RangeD(min, max);
    }
}
