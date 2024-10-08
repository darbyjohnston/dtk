// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/core/FontSystem.h>

#include <dtk/core/Context.h>
#include <dtk/core/LRUCache.h>
#include <dtk/core/LogSystem.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <algorithm>
#include <codecvt>
#include <limits>
#include <locale>
#include <map>

namespace dtk
{
    namespace
    {
#include <Fonts/NotoSansMono-Regular.h>
#include <Fonts/NotoSans-Regular.h>
#include <Fonts/NotoSans-Bold.h>

#if defined(_WINDOWS)
        //! \bug https://social.msdn.microsoft.com/Forums/vstudio/en-US/8f40dcd8-c67f-4eba-9134-a19b9178e481/vs-2015-rc-linker-stdcodecvt-error?forum=vcgeneral
        typedef unsigned int dtk_char_t;
#else // _WINDOWS
        typedef char32_t dtk_char_t;
#endif // _WINDOWS
    }

    std::vector<uint8_t> getFontData(const std::string& name)
    {
        std::vector<uint8_t> out;
        if ("NotoSansMono-Regular" == name)
        {
            out.resize(NotoSansMono_Regular_ttf.size());
            memcpy(
                out.data(),
                NotoSansMono_Regular_ttf.data(),
                NotoSansMono_Regular_ttf.size());
        }
        else if ("NotoSans-Regular" == name)
        {
            out.resize(NotoSans_Regular_ttf.size());
            memcpy(
                out.data(),
                NotoSans_Regular_ttf.data(),
                NotoSans_Regular_ttf.size());
        }
        else if ("NotoSans-Bold" == name)
        {
            out.resize(NotoSans_Bold_ttf.size());
            memcpy(
                out.data(),
                NotoSans_Bold_ttf.data(),
                NotoSans_Bold_ttf.size());
        }
        return out;
    }

    struct FontSystem::Private
    {
        std::shared_ptr<Glyph> getGlyph(uint32_t code, const FontInfo&);
        void measure(
            const std::basic_string<dtk_char_t>& utf32,
            const FontInfo&,
            int maxLineWidth,
            Size2I&,
            std::vector<Box2I>* = nullptr);

        std::map<std::string, std::vector<uint8_t> > fontData;
        FT_Library ftLibrary = nullptr;
        std::map<std::string, FT_Face> ftFaces;
        std::wstring_convert<std::codecvt_utf8<dtk_char_t>, dtk_char_t> utf32Convert;
        LRUCache<GlyphInfo, std::shared_ptr<Glyph> > glyphCache;
    };

    FontSystem::FontSystem(const std::shared_ptr<Context>& context) :
        ISystem(context, "dtk::FontSystem"),
        _p(new Private)
    {
        DTK_P();
        try
        {
            FT_Error ftError = FT_Init_FreeType(&p.ftLibrary);
            if (ftError)
            {
                throw std::runtime_error("FreeType cannot be initialized");
            }

            ftError = FT_New_Memory_Face(
                p.ftLibrary,
                NotoSans_Regular_ttf.data(),
                NotoSans_Regular_ttf.size(),
                0,
                &p.ftFaces["NotoSans-Regular"]);
            if (ftError)
            {
                throw std::runtime_error("Cannot create font");
            }
            ftError = FT_New_Memory_Face(
                p.ftLibrary,
                NotoSans_Bold_ttf.data(),
                NotoSans_Bold_ttf.size(),
                0,
                &p.ftFaces["NotoSans-Bold"]);
            if (ftError)
            {
                throw std::runtime_error("Cannot create font");
            }
            ftError = FT_New_Memory_Face(
                p.ftLibrary,
                NotoSansMono_Regular_ttf.data(),
                NotoSansMono_Regular_ttf.size(),
                0,
                &p.ftFaces["NotoSansMono-Regular"]);
            if (ftError)
            {
                throw std::runtime_error("Cannot create font");
            }
        }
        catch (const std::exception& e)
        {
            if (auto context = _context.lock())
            {
                auto logSystem = context->getSystem<LogSystem>();
                logSystem->print("dtk::FontSystem", e.what(), LogType::Error);
            }
        }
    }

    FontSystem::~FontSystem()
    {
        DTK_P();
        if (p.ftLibrary)
        {
            for (const auto& i : p.ftFaces)
            {
                FT_Done_Face(i.second);
            }
            FT_Done_FreeType(p.ftLibrary);
        }
    }

    std::shared_ptr<FontSystem> FontSystem::create(const std::shared_ptr<Context>& context)
    {
        return std::shared_ptr<FontSystem>(new FontSystem(context));
    }

    void FontSystem::addFont(const std::string& name, const uint8_t* data, size_t size)
    {
        DTK_P();
        p.fontData[name] = std::vector<uint8_t>(size);
        memcpy(p.fontData[name].data(), data, size);
        FT_Error ftError = FT_New_Memory_Face(
            p.ftLibrary,
            p.fontData[name].data(),
            size,
            0,
            &p.ftFaces[name]);
        if (ftError)
        {
            throw std::runtime_error("Cannot create font");
        }
    }

    size_t FontSystem::getGlyphCacheSize() const
    {
        return _p->glyphCache.getSize();
    }

    float FontSystem::getGlyphCachePercentage() const
    {
        return _p->glyphCache.getPercentage();
    }

    FontMetrics FontSystem::getMetrics(const FontInfo& info)
    {
        DTK_P();
        FontMetrics out;
        const auto ftFaceIt = p.ftFaces.find(info.family);
        if (ftFaceIt != p.ftFaces.end())
        {
            FT_Error ftError = FT_Set_Pixel_Sizes(ftFaceIt->second, 0, info.size);
            out.ascender = ftFaceIt->second->size->metrics.ascender / 64;
            out.descender = ftFaceIt->second->size->metrics.descender / 64;
            out.lineHeight = ftFaceIt->second->size->metrics.height / 64;
        }
        return out;
    }

    Size2I FontSystem::getSize(
        const std::string& text,
        const FontInfo& fontInfo,
        int maxLineWidth)
    {
        DTK_P();
        Size2I out;
        try
        {
            const auto utf32 = p.utf32Convert.from_bytes(text);
            p.measure(utf32, fontInfo, maxLineWidth, out);
        }
        catch (const std::exception&)
        {
        }
        return out;
    }

    std::vector<Box2I> FontSystem::getBox(
        const std::string& text,
        const FontInfo& fontInfo,
        int maxLineWidth)
    {
        DTK_P();
        std::vector<Box2I> out;
        try
        {
            const auto utf32 = p.utf32Convert.from_bytes(text);
            Size2I size;
            p.measure(utf32, fontInfo, maxLineWidth, size, &out);
        }
        catch (const std::exception&)
        {
        }
        return out;
    }

    std::vector<std::shared_ptr<Glyph> > FontSystem::getGlyphs(
        const std::string& text,
        const FontInfo& fontInfo)
    {
        DTK_P();
        std::vector<std::shared_ptr<Glyph> > out;
        try
        {
            const auto utf32 = p.utf32Convert.from_bytes(text);
            for (const auto& i : utf32)
            {
                out.push_back(p.getGlyph(i, fontInfo));
            }
        }
        catch (const std::exception&)
        {
        }
        return out;
    }

    std::shared_ptr<Glyph> FontSystem::Private::getGlyph(uint32_t code, const FontInfo& fontInfo)
    {
        std::shared_ptr<Glyph> out;
        if (!glyphCache.get(GlyphInfo(code, fontInfo), out))
        {
            out = std::make_shared<Glyph>();
            out->info = GlyphInfo(code, fontInfo);

            const auto ftFaceIt = ftFaces.find(fontInfo.family);
            if (ftFaceIt != ftFaces.end())
            {
                FT_Error ftError = FT_Set_Pixel_Sizes(
                    ftFaceIt->second,
                    0,
                    static_cast<int>(fontInfo.size));
                if (ftError)
                {
                    throw std::runtime_error("Cannot set pixel sizes");
                }
                if (auto ftGlyphIndex = FT_Get_Char_Index(ftFaceIt->second, code))
                {
                    ftError = FT_Load_Glyph(ftFaceIt->second, ftGlyphIndex, FT_LOAD_FORCE_AUTOHINT);
                    if (ftError)
                    {
                        throw std::runtime_error("Cannot load glyph");
                    }
                    FT_Render_Mode renderMode = FT_RENDER_MODE_NORMAL;
                    uint8_t renderModeChannels = 1;
                    ftError = FT_Render_Glyph(ftFaceIt->second->glyph, renderMode);
                    if (ftError)
                    {
                        throw std::runtime_error("Cannot render glyph");
                    }

                    auto ftBitmap = ftFaceIt->second->glyph->bitmap;
                    const ImageInfo imageInfo(ftBitmap.width, ftBitmap.rows, ImageType::L_U8);
                    out->image = Image::create(imageInfo);
                    for (size_t y = 0; y < ftBitmap.rows; ++y)
                    {
                        uint8_t* dataP = out->image->getData() + ftBitmap.width * y;
                        const unsigned char* bitmapP = ftBitmap.buffer + y * ftBitmap.pitch;
                        for (size_t x = 0; x < ftBitmap.width; ++x)
                        {
                            dataP[x] = bitmapP[x];
                        }
                    }
                    out->offset = V2I(ftFaceIt->second->glyph->bitmap_left, ftFaceIt->second->glyph->bitmap_top);
                    out->advance = ftFaceIt->second->glyph->advance.x / 64;
                    out->lsbDelta = ftFaceIt->second->glyph->lsb_delta;
                    out->rsbDelta = ftFaceIt->second->glyph->rsb_delta;
                }
            }

            glyphCache.add(out->info, out);
        }
        return out;
    }

    namespace
    {
        constexpr bool isSpace(dtk_char_t c)
        {
            return ' ' == c || '\t' == c;
        }
    }

    void FontSystem::Private::measure(
        const std::basic_string<dtk_char_t>& utf32,
        const FontInfo& fontInfo,
        int maxLineWidth,
        Size2I& size,
        std::vector<Box2I>* glyphGeom)
    {
        const auto ftFaceIt = ftFaces.find(fontInfo.family);
        if (ftFaceIt != ftFaces.end())
        {
            V2I pos;
            FT_Error ftError = FT_Set_Pixel_Sizes(
                ftFaceIt->second,
                0,
                static_cast<int>(fontInfo.size));
            if (ftError)
            {
                throw std::runtime_error("Cannot set pixel sizes");
            }

            const int h = ftFaceIt->second->size->metrics.height / 64;
            pos.y = h;
            auto textLine = utf32.end();
            int textLineX = 0;
            int32_t rsbDeltaPrev = 0;
            for (auto utf32It = utf32.begin(); utf32It != utf32.end(); ++utf32It)
            {
                const auto glyph = getGlyph(*utf32It, fontInfo);

                if (glyphGeom)
                {
                    Box2I box;
                    if (glyph)
                    {
                        box = Box2I(
                            pos.x,
                            pos.y - h,
                            glyph->advance,
                            h);
                    }
                    glyphGeom->push_back(box);
                }

                int32_t x = 0;
                V2I posAndSize;
                if (glyph)
                {
                    x = glyph->advance;
                    if (rsbDeltaPrev - glyph->lsbDelta > 32)
                    {
                        x -= 1;
                    }
                    else if (rsbDeltaPrev - glyph->lsbDelta < -31)
                    {
                        x += 1;
                    }
                    rsbDeltaPrev = glyph->rsbDelta;
                }
                else
                {
                    rsbDeltaPrev = 0;
                }

                if ('\n' == *utf32It)
                {
                    size.w = std::max(size.w, pos.x);
                    pos.x = 0;
                    pos.y += h;
                    rsbDeltaPrev = 0;
                    auto crIt = utf32It + 1;
                    if (crIt != utf32.end() && '\r' == *crIt)
                    {
                        ++utf32It;
                    }
                }
                else if (
                    maxLineWidth > 0 &&
                    pos.x > 0 &&
                    pos.x + (!isSpace(*utf32It) ? x : 0) >= maxLineWidth)
                {
                    if (textLine != utf32.end())
                    {
                        utf32It = textLine;
                        textLine = utf32.end();
                        size.w = std::max(size.w, textLineX);
                        pos.x = 0;
                        pos.y += h;
                    }
                    else
                    {
                        size.w = std::max(size.w, pos.x);
                        pos.x = x;
                        pos.y += h;
                    }
                    rsbDeltaPrev = 0;
                }
                else
                {
                    if (isSpace(*utf32It) && utf32It != utf32.begin())
                    {
                        textLine = utf32It;
                        textLineX = pos.x;
                    }
                    pos.x += x;
                }
            }
            size.w = std::max(size.w, pos.x);
            size.h = pos.y;
        }
    }
}