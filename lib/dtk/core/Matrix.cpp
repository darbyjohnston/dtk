// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Matrix.h>

namespace dtk
{
    void to_json(nlohmann::json& json, const M33F& value)
    {
        json =
        {
            { value.get(0, 0), value.get(0, 1), value.get(0, 2) },
            { value.get(1, 0), value.get(1, 1), value.get(1, 2) },
            { value.get(2, 0), value.get(2, 1), value.get(2, 2) }
        };
    }

    void to_json(nlohmann::json& json, const M44F& value)
    {
        json =
        {
            { value.get(0, 0), value.get(0, 1), value.get(0, 2), value.get(0, 3) },
            { value.get(1, 0), value.get(1, 1), value.get(1, 2), value.get(1, 3) },
            { value.get(2, 0), value.get(2, 1), value.get(2, 2), value.get(2, 3) },
            { value.get(3, 0), value.get(3, 1), value.get(3, 2), value.get(3, 3) }
        };
    }

    void from_json(const nlohmann::json& json, M33F& value)
    {
        for (int r = 0; r < 3; ++r)
        {
            for (int c = 0; c < 3; ++c)
            {
                float v = 0.F;
                json.at(r).at(c).get_to(v);
                value.set(r, c, v);
            }
        }
    }

    void from_json(const nlohmann::json& json, M44F& value)
    {
        for (int r = 0; r < 4; ++r)
        {
            for (int c = 0; c < 4; ++c)
            {
                float v = 0.F;
                json.at(r).at(c).get_to(v);
                value.set(r, c, v);
            }
        }
    }
}
