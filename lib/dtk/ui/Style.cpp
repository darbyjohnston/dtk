// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/Style.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <algorithm>
#include <sstream>

namespace dtk
{
    namespace ui
    {
        DTK_ENUM_IMPL(
            SizeRole,
            "None",
            "Margin",
            "MarginSmall",
            "MarginLarge",
            "MarginInside",
            "MarginDialog",
            "Spacing",
            "SpacingSmall",
            "SpacingLarge",
            "SpacingTool",
            "Border",
            "BorderFocus",
            "ScrollArea",
            "Slider",
            "Handle",
            "HandleSmall",
            "Swatch",
            "SwatchLarge",
            "Shadow",
            "DragLength");

        std::map<SizeRole, int> defaultSizeRoles()
        {
            std::map<SizeRole, int> out;
            out[SizeRole::Margin] = 10;
            out[SizeRole::MarginSmall] = 5;
            out[SizeRole::MarginLarge] = 20;
            out[SizeRole::MarginInside] = 2;
            out[SizeRole::MarginDialog] = 40;
            out[SizeRole::Spacing] = 10;
            out[SizeRole::SpacingSmall] = 5;
            out[SizeRole::SpacingLarge] = 20;
            out[SizeRole::SpacingTool] = 2;
            out[SizeRole::Border] = 1;
            out[SizeRole::BorderFocus] = 2;
            out[SizeRole::ScrollArea] = 200;
            out[SizeRole::Slider] = 100;
            out[SizeRole::Handle] = 8;
            out[SizeRole::HandleSmall] = 6;
            out[SizeRole::Swatch] = 20;
            out[SizeRole::SwatchLarge] = 40;
            out[SizeRole::Shadow] = 15;
            out[SizeRole::DragLength] = 10;
            return out;
        }

        DTK_ENUM_IMPL(
            ColorRole,
            "None",

            "Window",
            "Base",
            "Button",
            "Text",
            "TextDisabled",
            "Border",
            "Hover",
            "Pressed",
            "Checked",
            "KeyFocus",
            "Overlay",
            "TooltipWindow",
            "TooltipText",

            "Red",
            "Green",
            "Blue",
            "Cyan",
            "Magenta",
            "Yellow");

        std::map<ColorRole, Color4F> defaultColorRoles()
        {
            std::map<ColorRole, Color4F> out;
            out[ColorRole::None] = Color4F();

            out[ColorRole::Window] = Color4F(.2F, .2F, .2F);
            out[ColorRole::Base] = Color4F(.17F, .17F, .17F);
            out[ColorRole::Button] = Color4F(.3F, .3F, .3F);
            out[ColorRole::Text] = Color4F(1.F, 1.F, 1.F);
            out[ColorRole::TextDisabled] = Color4F(.5F, .5F, .5F);
            out[ColorRole::Border] = Color4F(.13F, .13F, .13F);
            out[ColorRole::Hover] = Color4F(1.F, 1.F, 1.F, .1F);
            out[ColorRole::Pressed] = Color4F(1.F, 1.F, 1.F, .2F);
            out[ColorRole::Checked] = Color4F(.56F, .36F, .15F);
            out[ColorRole::KeyFocus] = Color4F(.8F, .6F, .3F);
            out[ColorRole::Overlay] = Color4F(0.F, 0.F, 0.F, .5F);
            out[ColorRole::TooltipWindow] = Color4F(1.F, .95F, .7F);
            out[ColorRole::TooltipText] = Color4F(0.F, 0.F, 0.F);

            out[ColorRole::Red] = Color4F(.6F, .3F, .3F);
            out[ColorRole::Green] = Color4F(.3F, .6F, .3F);
            out[ColorRole::Blue] = Color4F(.3F, .3F, .6F);
            out[ColorRole::Cyan] = Color4F(.3F, .6F, .6F);
            out[ColorRole::Magenta] = Color4F(.6F, .3F, .6F);
            out[ColorRole::Yellow] = Color4F(.6F, .6F, .3F);

            return out;
        }

        DTK_ENUM_IMPL(
            FontRole,
            "None",
            "Label",
            "Mono",
            "Title");

        std::map<FontRole, FontInfo> defaultFontRoles()
        {
            std::map<FontRole, FontInfo> out;
            out[FontRole::Label] = FontInfo("NotoSans-Regular", 12 * 1);
            out[FontRole::Mono] = FontInfo("NotoSansMono-Regular", 12 * 1);
            out[FontRole::Title] = FontInfo("NotoSans-Regular", 16 * 1);
            return out;
        }

        struct Style::Private
        {
            std::weak_ptr<Context> context;
            std::shared_ptr<ObservableValue<bool> > changed;
        };

        void Style::_init(
            const std::shared_ptr<Context>& context)
        {
            DTK_P();
            p.context = context;
            _sizeRoles = defaultSizeRoles();
            _colorRoles = defaultColorRoles();
            _fontRoles = defaultFontRoles();
            p.changed = ObservableValue<bool>::create();
        }

        Style::Style() :
            _p(new Private)
        {}

        Style::~Style()
        {}

        std::shared_ptr<Style> Style::create(
            const std::shared_ptr<Context>& context)
        {
            auto out = std::shared_ptr<Style>(new Style);
            out->_init(context);
            return out;
        }

        void Style::setSizeRole(SizeRole role, int value)
        {
            DTK_P();
            if (_sizeRoles[role] == value)
                return;
            _sizeRoles[role] = value;
            p.changed->setAlways(true);
        }

        void Style::setSizeRoles(const std::map<SizeRole, int>& value)
        {
            DTK_P();
            if (_sizeRoles == value)
                return;
            _sizeRoles = value;
            p.changed->setAlways(true);
        }

        void Style::setColorRole(ColorRole role, const Color4F& value)
        {
            DTK_P();
            if (_colorRoles[role] == value)
                return;
            _colorRoles[role] = value;
            p.changed->setAlways(true);
        }

        void Style::setColorRoles(const std::map<ColorRole, Color4F>& value)
        {
            DTK_P();
            if (_colorRoles == value)
                return;
            _colorRoles = value;
            p.changed->setAlways(true);
        }

        void Style::setFontRole(FontRole role, const FontInfo& value)
        {
            DTK_P();
            if (_fontRoles[role] == value)
                return;
            _fontRoles[role] = value;
            p.changed->setAlways(true);
        }

        void Style::setFontRoles(const std::map<FontRole, FontInfo>& value)
        {
            DTK_P();
            if (_fontRoles == value)
                return;
            _fontRoles = value;
            p.changed->setAlways(true);
        }

        std::shared_ptr<IObservableValue<bool> > Style::observeChanged() const
        {
            return _p->changed;
        }
    }
}
