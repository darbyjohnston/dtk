// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include <dtk/ui/GroupBox.h>

#include <dtk/ui/DrawUtil.h>

#include <optional>

namespace dtk
{
    struct GroupBox::Private
    {
        std::string text;
        FontRole fontRole = FontRole::Label;

        struct SizeData
        {
            std::optional<float> displayScale;
            int margin = 0;
            int spacing = 0;
            int border = 0;
            FontInfo fontInfo;
            FontMetrics fontMetrics;
            Size2I textSize;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            Box2I g2;
            TriMesh2F border;
            std::vector<std::shared_ptr<Glyph> > glyphs;
        };
        DrawData draw;
    };

    void GroupBox::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::GroupBox", parent);
    }

    GroupBox::GroupBox() :
        _p(new Private)
    {}

    GroupBox::~GroupBox()
    {}

    std::shared_ptr<GroupBox> GroupBox::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<GroupBox>(new GroupBox);
        out->_init(context, parent);
        return out;
    }

    std::shared_ptr<GroupBox> GroupBox::create(
        const std::shared_ptr<Context>& context,
        const std::string& text,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = create(context, parent);
        out->setText(text);
        return out;
    }

    const std::string& GroupBox::getText() const
    {
        return _p->text;
    }

    void GroupBox::setText(const std::string& value)
    {
        DTK_P();
        if (value == p.text)
            return;
        p.text = value;
        p.size.displayScale.reset();
        p.draw.glyphs.clear();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    FontRole GroupBox::getFontRole() const
    {
        return _p->fontRole;
    }

    void GroupBox::setFontRole(FontRole value)
    {
        DTK_P();
        if (value == p.fontRole)
            return;
        p.fontRole = value;
        p.size.displayScale.reset();
        p.draw.glyphs.clear();
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void GroupBox::clear()
    {
        auto children = getChildren();
        for (auto child : children)
        {
            child->setParent(nullptr);
        }
    }

    void GroupBox::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();

        Box2I g = value;
        g.min.y += p.size.fontMetrics.lineHeight + p.size.spacing;
        g = margin(g, -(p.size.border + p.size.margin));
        for (const auto& child : getChildren())
        {
            child->setGeometry(g);
        }

        p.draw.g = value;
        p.draw.g2 = Box2I(
            V2I(
                p.draw.g.min.x,
                p.draw.g.min.y + p.size.fontMetrics.lineHeight + p.size.spacing),
            p.draw.g.max);
        p.draw.border = border(p.draw.g2, p.size.border, p.size.margin);
    }

    void GroupBox::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();

        if (!p.size.displayScale.has_value() ||
            (p.size.displayScale.has_value() && p.size.displayScale.value() != event.displayScale))
        {
            p.size.displayScale = event.displayScale;
            p.size.margin = event.style->getSizeRole(SizeRole::MarginSmall, event.displayScale);
            p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, event.displayScale);
            p.size.border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
            p.size.fontInfo = event.style->getFontRole(p.fontRole, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            p.size.textSize = event.fontSystem->getSize(p.text, p.size.fontInfo);
            p.draw.glyphs.clear();
        }

        Size2I sizeHint;
        for (const auto& child : getChildren())
        {
            const Size2I& childSizeHint = child->getSizeHint();
            sizeHint.w = std::max(sizeHint.w, childSizeHint.w);
            sizeHint.h = std::max(sizeHint.h, childSizeHint.h);
        }
        sizeHint = margin(sizeHint, p.size.margin + p.size.border);
        sizeHint.w = std::max(sizeHint.w, p.size.textSize.w);
        sizeHint.h += p.size.fontMetrics.lineHeight + p.size.spacing;
        _setSizeHint(sizeHint);
    }

    void GroupBox::clipEvent(const Box2I& clipRect, bool clipped)
    {
        IWidget::clipEvent(clipRect, clipped);
        DTK_P();
        if (clipped)
        {
            p.draw.glyphs.clear();
        }
    }

    void GroupBox::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();

        if (!p.text.empty() && p.draw.glyphs.empty())
        {
            p.draw.glyphs = event.fontSystem->getGlyphs(p.text, p.size.fontInfo);
        }
        event.render->drawText(
            p.draw.glyphs,
            p.size.fontMetrics,
            p.draw.g.min,
            event.style->getColorRole(ColorRole::Text));

        event.render->drawMesh(
            p.draw.border,
            event.style->getColorRole(ColorRole::Border));
    }
}