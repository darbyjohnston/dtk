// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtk/ui/PieChart.h>

#include <dtk/ui/DrawUtil.h>
#include <dtk/ui/LayoutUtil.h>

#include <dtk/core/Format.h>

namespace dtk
{
    PieChartData::PieChartData(
        float percentage,
        const Color4F& color) :
        percentage(percentage),
        color(color)
    {}

    bool PieChartData::operator == (const PieChartData& other) const
    {
        return
            percentage == other.percentage &&
            color == other.color;
    }

    bool PieChartData::operator != (const PieChartData& other) const
    {
        return !(*this == other);
    }

    struct PieChart::Private
    {
        std::vector<PieChartData> data;
        int sizeMult = 5;

        struct SizeData
        {
            bool init = true;
            float displayScale = 0.F;
            FontMetrics fontMetrics;
        };
        SizeData size;

        struct DrawData
        {
            Box2I g;
            std::vector<TriMesh2F> meshes;
        };
        DrawData draw;
    };

    void PieChart::_init(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        IWidget::_init(context, "dtk::PieChart", parent);
    }

    PieChart::PieChart() :
        _p(new Private)
    {}

    PieChart::~PieChart()
    {}

    std::shared_ptr<PieChart> PieChart::create(
        const std::shared_ptr<Context>& context,
        const std::shared_ptr<IWidget>& parent)
    {
        auto out = std::shared_ptr<PieChart>(new PieChart);
        out->_init(context, parent);
        return out;
    }

    const std::vector<PieChartData>& PieChart::getData() const
    {
        return _p->data;
    }

    void PieChart::setData(const std::vector<PieChartData>& value)
    {
        DTK_P();
        if (value == p.data)
            return;
        p.data = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    int PieChart::getSizeMult() const
    {
        return _p->sizeMult;
    }

    void PieChart::setSizeMult(int value)
    {
        DTK_P();
        if (value == p.sizeMult)
            return;
        p.sizeMult = value;
        _setSizeUpdate();
        _setDrawUpdate();
    }

    void PieChart::setGeometry(const Box2I& value)
    {
        IWidget::setGeometry(value);
        DTK_P();
        p.draw.g = value;
        p.draw.meshes.clear();
        const float r = value.w() / 2.F;
        float a = 0.F;
        for (size_t i = 0; i < p.data.size(); ++i)
        {
            TriMesh2F mesh;
            const float d = p.data[i].percentage;
            const float inc = 2.F;
            for (int i = a; i < a + d; i += inc)
            {
                const size_t size = mesh.v.size();
                mesh.v.push_back(V2F(0.F, 0.F));
                mesh.v.push_back(V2F(
                    cos(deg2rad(i / 100.F * 360.F - 90.F)) * r,
                    sin(deg2rad(i / 100.F * 360.F - 90.F)) * r));
                mesh.v.push_back(V2F(
                    cos(deg2rad(std::min(i + inc, a + d) / 100.F * 360.F - 90.F)) * r,
                    sin(deg2rad(std::min(i + inc, a + d) / 100.F * 360.F - 90.F)) * r));
                mesh.triangles.push_back({ size + 1, size + 2, size + 3 });
            }
            p.draw.meshes.push_back(mesh);
            a += p.data[i].percentage;
        }
    }

    void PieChart::sizeHintEvent(const SizeHintEvent& event)
    {
        IWidget::sizeHintEvent(event);
        DTK_P();
        const bool displayScaleChanged = event.displayScale != p.size.displayScale;
        if (displayScaleChanged || p.size.init)
        {
            p.size.init = false;
            p.size.displayScale = event.displayScale;
            const FontInfo fontInfo = event.style->getFontRole(FontRole::Label, event.displayScale);
            p.size.fontMetrics = event.fontSystem->getMetrics(fontInfo);
        }
        const int d = p.size.fontMetrics.lineHeight * p.sizeMult;
        _setSizeHint(Size2I(d, d));
    }

    void PieChart::drawEvent(
        const Box2I& drawRect,
        const DrawEvent& event)
    {
        IWidget::drawEvent(drawRect, event);
        DTK_P();
        const V2I c = center(p.draw.g);
        for (size_t i = 0; i < p.data.size(); ++i)
        {
            event.render->drawMesh(
                p.draw.meshes[i],
                p.data[i].color,
                convert(c));
        }
    }
}