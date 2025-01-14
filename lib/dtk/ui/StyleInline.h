// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

namespace dtk
{
    inline int Style::getSizeRole(SizeRole role, float scale) const
    {
        const auto i = _sizeRoles.find(role);
        return i != _sizeRoles.end() ? (i->second * scale) : 0;
    }

    inline Color4F Style::getColorRole(ColorRole role) const
    {
        const auto i = _colorRoles.find(role);
        return i != _colorRoles.end() ? i->second : Color4F();
    }

    inline FontInfo Style::getFontRole(FontRole role, float scale) const
    {
        FontInfo out;
        const auto i = _fontRoles.find(role);
        if (i != _fontRoles.end())
        {
            out = i->second;
            out.size *= scale;
        }
        return out;
    }
}