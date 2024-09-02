// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/LayoutUtil.h>

#include <dtk/core/Math.h>

#include <iomanip>
#include <sstream>

namespace dtk
{
    Box2I align(
        const Box2I& box,
        const Size2I& sizeHint,
        Stretch       hStretch,
        Stretch       vStretch,
        HAlign        hAlign,
        VAlign        vAlign)
    {
        V2I pos;
        V2I size;

        switch (hStretch)
        {
        case Stretch::Fixed:
            switch (hAlign)
            {
            case HAlign::Left:
                pos.x = box.x();
                break;
            case HAlign::Center:
                pos.x = box.x() + box.w() / 2 - sizeHint.w / 2;
                break;
            case HAlign::Right:
                pos.x = box.x() + box.w() - sizeHint.w;
                break;
            default: break;
            }
            size.x = sizeHint.w;
            break;
        case Stretch::Expanding:
            pos.x = box.x();
            size.x = box.w();
            break;
        default: break;
        }

        switch (vStretch)
        {
        case Stretch::Fixed:
            switch (vAlign)
            {
            case VAlign::Top:
                pos.y = box.y();
                break;
            case VAlign::Center:
                pos.y = box.y() + box.h() / 2 - sizeHint.h / 2;
                break;
            case VAlign::Bottom:
                pos.y = box.y() + box.w() - sizeHint.h;
                break;
            default: break;
            }
            size.y = sizeHint.h;
            break;
        case Stretch::Expanding:
            pos.y = box.y();
            size.y = box.h();
            break;
        default: break;
        }

        return Box2I(pos.x, pos.y, size.x, size.y);
    }

    std::string format(int value)
    {
        std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(digits(value));
        ss << 0;
        return ss.str();
    }

    std::string format(float value, int precision)
    {
        std::stringstream ss;
        ss << std::setfill('0');
        ss << std::setw(digits(value));
        ss << 0;
        ss << ".";
        ss << std::setw(precision);
        ss << 0;
        return ss.str();
    }
}