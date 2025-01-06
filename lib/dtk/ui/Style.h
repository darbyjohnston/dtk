// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Color.h>
#include <dtk/core/Context.h>
#include <dtk/core/FontSystem.h>
#include <dtk/core/ObservableValue.h>

namespace dtk
{
    //! \name Style
    ///@{

    //! Size roles.
    enum class SizeRole
    {
        None,
        Margin,
        MarginSmall,
        MarginLarge,
        MarginInside,
        MarginDialog,
        Spacing,
        SpacingSmall,
        SpacingLarge,
        SpacingTool,
        Icon,
        Border,
        LabelPad,
        ScrollArea,
        Slider,
        Handle,
        HandleSmall,
        Swatch,
        SwatchLarge,
        Shadow,
        DragLength,

        Count,
        First = None
    };
    DTK_ENUM(SizeRole);

    //! Get the default size roles.
    std::map<SizeRole, int> defaultSizeRoles();

    //! Color roles.
    enum class ColorRole
    {
        None,

        Window,
        Base,
        Button,
        Text,
        TextDisabled,
        Trough,
        Border,
        Hover,
        Pressed,
        Checked,
        KeyFocus,
        Overlay,
        TooltipWindow,
        TooltipText,

        Red,
        Green,
        Blue,
        Cyan,
        Magenta,
        Yellow,

        Count,
        First = None
    };
    DTK_ENUM(ColorRole);

    //! Get default color roles.
    std::map<ColorRole, Color4F> defaultColorRoles();

    //! Font roles.
    enum class FontRole
    {
        None,
        Label,
        Mono,
        Title,

        Count,
        First = None
    };
    DTK_ENUM(FontRole);

    //! Get default font roles.
    std::map<FontRole, FontInfo> defaultFontRoles();

    //! Style.
    class Style : public std::enable_shared_from_this<Style>
    {
        DTK_NON_COPYABLE(Style);

    protected:
        void _init(const std::shared_ptr<Context>&);

        Style();

    public:
        ~Style();

        //! Create a new style.
        static std::shared_ptr<Style> create(
            const std::shared_ptr<Context>&);

        //! Get a size role.
        int getSizeRole(SizeRole, float scale) const;

        //! Set a size role.
        void setSizeRole(SizeRole, int);

        //! Set the size roles.
        void setSizeRoles(const std::map<SizeRole, int>&);

        //! Get a color role.
        Color4F getColorRole(ColorRole) const;

        //! Set a color role.
        void setColorRole(ColorRole, const Color4F&);

        //! Set the color roles.
        void setColorRoles(const std::map<ColorRole, Color4F>&);

        //! Get a font role.
        FontInfo getFontRole(FontRole, float scale) const;

        //! Set a font role.
        void setFontRole(FontRole, const FontInfo&);

        //! Set the font roles.
        void setFontRoles(const std::map<FontRole, FontInfo>&);

        //! Observe style changes.
        std::shared_ptr<IObservableValue<bool> > observeChanged() const;

    private:
        std::map<SizeRole, int> _sizeRoles;
        std::map<ColorRole, Color4F> _colorRoles;
        std::map<FontRole, FontInfo> _fontRoles;

        DTK_PRIVATE();
    };

    ///@}
}

#include <dtk/ui/StyleInline.h>
