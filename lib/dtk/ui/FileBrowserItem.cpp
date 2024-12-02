// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/FileBrowserPrivate.h>

#include <dtk/ui/DrawUtil.h>

#include <dtk/core/Format.h>

#include <ctime>
#include <filesystem>
//#include <format>

namespace dtk
{
    struct FileBrowserItem::Private
    {
        std::vector<std::string> labels;
        std::vector<int> columns;
        bool current = false;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            int margin = 0;
            int border = 0;
            int pad = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            std::vector<int> textWidths;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            std::vector< std::vector<std::shared_ptr<Glyph> > > glyphs;
        };
        DrawData draw;
    };

    void FileBrowserItem::_init(
        const std::shared_ptr<Context>& context,
        const FileBrowserInfo& info,
        const std::shared_ptr<IWidget>& parent)
    {
        IButton::_init(context, "dtk::FileBrowserItem", parent);
        DTK_P();

        setButtonRole(ColorRole::None);

        // Icon.
        setIcon(info.isDir ? "Directory" : "File");

        // File name.
        p.labels.push_back(info.path.filename().string());

        // File extension.
        p.labels.push_back(!info.isDir ?
            info.path.extension().string() :
            std::string());

        // File size.
        std::string label;
        if (!info.isDir)
        {
            if (info.size < megabyte)
            {
                label = Format("{0}KB").
                    arg(info.size / static_cast<float>(kilobyte), 2);
            }
            else if (info.size < gigabyte)
            {
                label = Format("{0}MB").
                    arg(info.size / static_cast<float>(megabyte), 2);
            }
            else
            {
                label = Format("{0}GB").
                    arg(info.size / static_cast<float>(gigabyte), 2);
            }
        }
        p.labels.push_back(label);

        // File last modification time.
        // \todo std::format is available in C++20.
        //p.labels.push_back(std::format("{}", info.time));
    }

    FileBrowserItem::FileBrowserItem() :
        _p(new Private)
    {}

    FileBrowserItem::~FileBrowserItem()
    {}

    std::shared_ptr<FileBrowserItem> FileBrowserItem::create(
        const std::shared_ptr<Context>& context,
        const FileBrowserInfo& info,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<FileBrowserItem>(new FileBrowserItem);
        out->_init(context, info, parent);
        return out;
    }

    const std::vector<int>& FileBrowserItem::getTextWidths() const
    {
        return _p->size.textWidths;
    }

    void FileBrowserItem::setColumns(const std::vector<int>& value)
    {
        DTK_P();
        if (value == p.columns)
            return;
        p.columns = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void FileBrowserItem::setCurrent(bool value)
    {
        DTK_P();
        if (value == p.current)
            return;
        p.current = value;
        _setDrawUpdate();
    }

    void FileBrowserItem::setGeometry(const Box2I& value)
    {
        IButton::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.g2 = margin(p.draw.g, -p.size.border);
    }

    void FileBrowserItem::sizeHintEvent(const SizeHintEvent& event)
    {
        IButton::sizeHintEvent(event);
        DTK_P();

        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (p.size.init || displayScaleChanged)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginInside, p.size.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, p.size.displayScale);
            p.size.pad = event.style->getSizeRole(SizeRole::LabelPad, p.size.displayScale);
            p.size.fontInfo = event.style->getFontRole(_fontRole, p.size.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textWidths.clear();
            for (const auto& label : p.labels)
            {
                p.size.textWidths.push_back(
                    event.fontSystem->getSize(label, p.size.fontInfo).w);
            }
            p.draw.glyphs.clear();
        }

        Size2I sizeHint;
        if (!p.labels.empty())
        {
            for (const int w : p.size.textWidths)
            {
                sizeHint.w += w + p.size.pad * 2 + p.size.margin * 2;
            }
            sizeHint.h = p.size.fontMetrics.lineHeight + p.size.margin * 2;
        }
        if (_iconImage)
        {
            sizeHint.w += _iconImage->getWidth();
            sizeHint.h = std::max(sizeHint.h, _iconImage->getHeight());
        }
        sizeHint = margin(sizeHint, p.size.border);
        _setSizeHint(sizeHint);
    }

    void FileBrowserItem::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void FileBrowserItem::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IButton::drawEvent(drawRect, event);
        DTK_P();

        // Draw the mouse states.
        if (_isMousePressed())
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(ColorRole::Pressed));
        }
        else if (_isMouseInside())
        {
            event.render->drawRect(
                p.draw.g,
                event.style->getColorRole(ColorRole::Hover));
        }

        // Draw the current state.
        if (p.current)
        {
            event.render->drawMesh(
                border(p.draw.g, p.size.border),
                event.style->getColorRole(ColorRole::KeyFocus));
        }

        // Draw the icon.
        int x = p.draw.g2.x();
        if (_iconImage)
        {
            const Size2I& iconSize = _iconImage->getSize();
            event.render->drawImage(
                _iconImage,
                Box2I(
                    x,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - iconSize.h / 2,
                    iconSize.w,
                    iconSize.h),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
            x += iconSize.w;
        }

        // Draw the text.
        int rightColumnsWidth = 0;
        for (size_t i = 1; i < p.columns.size(); ++i)
        {
            rightColumnsWidth += p.columns[i] + p.size.margin * 2 + p.size.pad * 2;
        }
        const bool glyphsInit = p.draw.glyphs.empty();
        for (size_t i = 0; i < p.labels.size() && i < p.columns.size(); ++i)
        {
            if (glyphsInit)
            {
                p.draw.glyphs.push_back(
                    event.fontSystem->getGlyphs(p.labels[i], p.size.fontInfo));
            }
            event.render->drawText(
                p.draw.glyphs[i],
                p.size.fontMetrics,
                V2I(x + p.size.margin + p.size.pad,
                    p.draw.g2.y() + p.draw.g2.h() / 2 - p.size.fontMetrics.lineHeight / 2),
                event.style->getColorRole(isEnabled() ?
                    ColorRole::Text :
                    ColorRole::TextDisabled));
            if (0 == i)
            {
                x = p.draw.g2.max.x - rightColumnsWidth;
            }
            else
            {
                x += p.columns[i] + p.size.margin * 2 + p.size.pad * 2;
            }
        }
    }
}