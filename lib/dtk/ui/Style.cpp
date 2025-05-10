// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/Style.h>

#include <dtk/core/Error.h>
#include <dtk/core/String.h>

#include <algorithm>
#include <sstream>

namespace dtk
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
        "Swatch",
        "SwatchLarge",
        "Shadow",
        "DragLength");

    std::map<SizeRole, int> getDefaultSizeRoles()
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
        out[SizeRole::Icon] = 20;
        out[SizeRole::Border] = 1;
        out[SizeRole::LabelPad] = 4;
        out[SizeRole::ScrollArea] = 200;
        out[SizeRole::Slider] = 100;
        out[SizeRole::Handle] = 8;
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

        "VideoClip",
        "VideoGap",
        "AudioClip",
        "AudioGap",

        "Red",
        "Green",
        "Blue",
        "Cyan",
        "Magenta",
        "Yellow");

    std::map<ColorRole, Color4F> getDefaultColorRoles()
    {
        std::map<ColorRole, Color4F> out;
        out[ColorRole::None] = Color4F();

        out[ColorRole::Window] = Color4F(.15F, .15F, .15F);
        out[ColorRole::Base] = Color4F(.12F, .12F, .12F);
        out[ColorRole::Button] = Color4F(.2F, .2F, .2F);
        out[ColorRole::Text] = Color4F(1.F, 1.F, 1.F);
        out[ColorRole::TextDisabled] = Color4F(.5F, .5F, .5F);
        out[ColorRole::Border] = Color4F(.25F, .25F, .25F);
        out[ColorRole::Hover] = Color4F(1.F, 1.F, 1.F, .1F);
        out[ColorRole::Pressed] = Color4F(1.F, 1.F, 1.F, .2F);
        out[ColorRole::Checked] = Color4F(.56F, .36F, .15F);
        out[ColorRole::KeyFocus] = Color4F(.8F, .6F, .3F);
        out[ColorRole::Overlay] = Color4F(0.F, 0.F, 0.F, .5F);
        out[ColorRole::TooltipWindow] = Color4F(1.F, .95F, .7F);
        out[ColorRole::TooltipText] = Color4F(0.F, 0.F, 0.F);

        out[ColorRole::VideoClip] = Color4F(.2F, .4F, .4F);
        out[ColorRole::VideoGap] = Color4F(.25F, .31F, .31F);
        out[ColorRole::AudioClip] = Color4F(.3F, .25F, .4F);
        out[ColorRole::AudioGap] = Color4F(.25F, .24F, .3F);

        out[ColorRole::Red] = Color4F(.6F, .3F, .3F);
        out[ColorRole::Green] = Color4F(.3F, .6F, .3F);
        out[ColorRole::Blue] = Color4F(.3F, .3F, .6F);
        out[ColorRole::Cyan] = Color4F(.3F, .6F, .6F);
        out[ColorRole::Magenta] = Color4F(.6F, .3F, .6F);
        out[ColorRole::Yellow] = Color4F(.6F, .6F, .3F);

        return out;
    }

    std::map<ColorRole, Color4F> getLightColorRoles()
    {
        std::map<ColorRole, Color4F> out = getDefaultColorRoles();

        out[ColorRole::Window] = Color4F(.8F, .8F, .8F);
        out[ColorRole::Base] = Color4F(.9F, .9F, .9F);
        out[ColorRole::Button] = Color4F(.7F, .7F, .7F);
        out[ColorRole::Text] = Color4F(0.F, 0.F, 0.F);
        out[ColorRole::TextDisabled] = Color4F(.5F, .5F, .5F);
        out[ColorRole::Border] = Color4F(.6F, .6F, .6F);
        out[ColorRole::Hover] = Color4F(0.F, 0.F, 0.F, .1F);
        out[ColorRole::Pressed] = Color4F(0.F, 0.F, 0.F, .2F);
        out[ColorRole::Checked] = Color4F(.6F, .7F, .85F);
        out[ColorRole::KeyFocus] = Color4F(0.F, .5F, 1.F);
        out[ColorRole::Overlay] = Color4F(1.F, 1.F, 1.F, .5F);

        out[ColorRole::VideoClip] = Color4F(.5F, .7F, .7F);
        out[ColorRole::VideoGap] = Color4F(.55F, .61F, .61F);
        out[ColorRole::AudioClip] = Color4F(.6F, .55F, .7F);
        out[ColorRole::AudioGap] = Color4F(.55F, .54F, .6F);

        return out;
    }

    bool ColorControls::operator == (const ColorControls& other) const
    {
        return
            brightness == other.brightness &&
            contrast == other.contrast;
    }

    bool ColorControls::operator != (const ColorControls& other) const
    {
        return !(*this == other);
    }

    DTK_ENUM_IMPL(
        FontRole,
        "None",
        "Label",
        "Mono",
        "Title");

    std::map<FontRole, FontInfo> getDefaultFontRoles()
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
        std::map<SizeRole, int> sizeRoles;
        std::map<ColorRole, Color4F> colorRoles;
        ColorControls colorControls;
        M44F colorMatrix;
        std::map<FontRole, FontInfo> fontRoles;
        std::shared_ptr<ObservableValue<bool> > changed;
    };

    void Style::_init(
        const std::shared_ptr<Context>& context)
    {
        DTK_P();

        p.context = context;
        p.sizeRoles = getDefaultSizeRoles();
        p.colorRoles = getDefaultColorRoles();
        p.fontRoles = getDefaultFontRoles();
        p.changed = ObservableValue<bool>::create();

        _colorUpdate();
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

    int Style::getSizeRole(SizeRole role, float scale) const
    {
        DTK_P();
        const auto i = p.sizeRoles.find(role);
        return i != p.sizeRoles.end() ? (i->second * scale) : 0;
    }

    void Style::setSizeRole(SizeRole role, int value)
    {
        DTK_P();
        if (value == p.sizeRoles[role])
            return;
        p.sizeRoles[role] = value;
        p.changed->setAlways(true);
    }

    void Style::setSizeRoles(const std::map<SizeRole, int>& value)
    {
        DTK_P();
        if (value == p.sizeRoles)
            return;
        p.sizeRoles = value;
        p.changed->setAlways(true);
    }

    Color4F Style::getColorRole(ColorRole role) const
    {
        DTK_P();
        const auto i = p.colorRoles.find(role);
        Color4F c;
        if (i != p.colorRoles.end())
        {
            c = i->second;
        }
        const V3F v = V3F(c.r, c.g, c.b) * p.colorMatrix;
        return Color4F(v.x, v.y, v.z, c.a);
    }

    void Style::setColorRole(ColorRole role, const Color4F& value)
    {
        DTK_P();
        if (value == p.colorRoles[role])
            return;
        p.colorRoles[role] = value;
        p.changed->setAlways(true);
    }

    void Style::setColorRoles(const std::map<ColorRole, Color4F>& value)
    {
        DTK_P();
        if (value == p.colorRoles)
            return;
        p.colorRoles = value;
        p.changed->setAlways(true);
    }

    const ColorControls& Style::getColorControls() const
    {
        return _p->colorControls;
    }

    void Style::setColorControls(const ColorControls& value)
    {
        DTK_P();
        if (value == p.colorControls)
            return;
        p.colorControls = value;
        _colorUpdate();
        p.changed->setAlways(true);
    }

    FontInfo Style::getFontRole(FontRole role, float scale) const
    {
        DTK_P();
        FontInfo out;
        const auto i = p.fontRoles.find(role);
        if (i != p.fontRoles.end())
        {
            out = i->second;
            out.size *= scale;
        }
        return out;
    }

    void Style::setFontRole(FontRole role, const FontInfo& value)
    {
        DTK_P();
        if (value == p.fontRoles[role])
            return;
        p.fontRoles[role] = value;
        p.changed->setAlways(true);
    }

    void Style::setFontRoles(const std::map<FontRole, FontInfo>& value)
    {
        DTK_P();
        if (value == p.fontRoles)
            return;
        p.fontRoles = value;
        p.changed->setAlways(true);
    }

    std::shared_ptr<IObservableValue<bool> > Style::observeChanged() const
    {
        return _p->changed;
    }

    void Style::_colorUpdate()
    {
        DTK_P();
        p.colorMatrix =
            brightness(V3F(p.colorControls.brightness, p.colorControls.brightness, p.colorControls.brightness)) *
            contrast(V3F(p.colorControls.contrast, p.colorControls.contrast, p.colorControls.contrast));
    }

    void to_json(nlohmann::json& json, const ColorControls& value)
    {
        json["Brightness"] = value.brightness;
        json["Contrast"] = value.contrast;
    }

    void from_json(const nlohmann::json& json, ColorControls& out)
    {
        json.at("Brightness").get_to(out.brightness);
        json.at("Contrast").get_to(out.contrast);
    }
}