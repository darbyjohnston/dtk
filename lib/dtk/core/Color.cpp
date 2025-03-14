// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Color.h>

namespace dtk
{
    M44F brightness(const V3F& value)
    {
        return M44F(
            value.x, 0.F, 0.F, 0.F,
            0.F, value.y, 0.F, 0.F,
            0.F, 0.F, value.z, 0.F,
            0.F, 0.F, 0.F, 1.F);
    }

    M44F contrast(const V3F& value)
    {
        return
            M44F(
                1.F, 0.F, 0.F, 0.F,
                0.F, 1.F, 0.F, 0.F,
                0.F, 0.F, 1.F, 0.F,
                .5F, .5F, .5F, 1.F) *
            M44F(
                value.x, 0.F, 0.F, 0.F,
                0.F, value.y, 0.F, 0.F,
                0.F, 0.F, value.z, 0.F,
                0.F, 0.F, 0.F, 1.F) *
            M44F(
                1.F, 0.F, 0.F, 0.F,
                0.F, 1.F, 0.F, 0.F,
                0.F, 0.F, 1.F, 0.F,
                -.5F, -.5F, -.5F, 1.F);
    }

    M44F saturation(const V3F& value)
    {
        const V3F s(
            (1.F - value.x) * .3086F,
            (1.F - value.y) * .6094F,
            (1.F - value.z) * .0820F);
        return M44F(
            s.x + value.x, s.x, s.x, 0.F,
            s.y, s.y + value.y, s.y, 0.F,
            s.z, s.z, s.z + value.z, 0.F,
            0.F, 0.F, 0.F, 1.F);
    }

    M44F tint(float v)
    {
        const float c = cos(v * pi * 2.F);
        const float c2 = 1.F - c;
        const float c3 = 1.F / 3.F * c2;
        const float s = sin(v * pi * 2.F);
        const float sq = sqrtf(1.F / 3.F);
        return M44F(
            c + c2 / 3.F, c3 - sq * s, c3 + sq * s, 0.F,
            c3 + sq * s, c + c3, c3 - sq * s, 0.F,
            c3 - sq * s, c3 + sq * s, c + c3, 0.F,
            0.F, 0.F, 0.F, 1.F);
    }

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
