// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/core/Matrix.h>

namespace dtk
{
    nlohmann::json to_json(const M33F& value)
    {
        return
        {
            value.get(0, 0), value.get(0, 1), value.get(0, 2),
            value.get(1, 0), value.get(1, 1), value.get(1, 2),
            value.get(2, 0), value.get(2, 1), value.get(2, 2)
        };
    }

    nlohmann::json to_json(const M44F& value)
    {
        return
        {
            value.get(0, 0), value.get(0, 1), value.get(0, 2), value.get(0, 3),
            value.get(1, 0), value.get(1, 1), value.get(1, 2), value.get(1, 3),
            value.get(2, 0), value.get(2, 1), value.get(2, 2), value.get(2, 3),
            value.get(3, 0), value.get(3, 1), value.get(3, 2), value.get(3, 3)
        };
    }

    bool from_json(const nlohmann::json& json, M33F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 9)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (json.at(i).is_number())
                {
                    value[i] = json.at(i).get<float>();
                }
            }
            out = true;
        }
        return out;
    }

    bool from_json(const nlohmann::json& json, M44F& value)
    {
        bool out = false;
        if (json.is_array() &&
            json.size() == 16)
        {
            for (int i = 0; i < 16; ++i)
            {
                if (json.at(i).is_number())
                {
                    value[i] = json.at(i).get<float>();
                }
            }
            out = true;
        }
        return out;
    }
}
