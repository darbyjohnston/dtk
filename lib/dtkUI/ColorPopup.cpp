// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkUI/ColorPopup.h>

#include <dtkUI/ColorWidget.h>
#include <dtkUI/RowLayout.h>

using namespace dtk::core;

namespace dtk
{
    namespace ui
    {
        struct ColorPopup::Private
        {
            std::shared_ptr<ColorWidget> widget;
            std::shared_ptr<VerticalLayout> layout;
            std::function<void(const Color4F&)> callback;
        };

        void ColorPopup::_init(
            const std::shared_ptr<Context>& context,
            const Color4F& color,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidgetPopup::_init(context, "dtk::ui::ColorPopup", parent);
            DTK_P();

            p.widget = ColorWidget::create(context);
            p.widget->setColor(color);

            p.layout = VerticalLayout::create(context);
            p.layout->setMarginRole(SizeRole::MarginSmall);
            p.widget->setParent(p.layout);
            setWidget(p.layout);

            p.widget->setCallback(
                [this](const Color4F& value)
                {
                    if (_p->callback)
                    {
                        _p->callback(value);
                    }
                });
        }

        ColorPopup::ColorPopup() :
            _p(new Private)
        {}

        ColorPopup::~ColorPopup()
        {}

        std::shared_ptr<ColorPopup> ColorPopup::create(
            const std::shared_ptr<Context>& context,
            const Color4F& color,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<ColorPopup>(new ColorPopup);
            out->_init(context, color, parent);
            return out;
        }

        void ColorPopup::setCallback(const std::function<void(const Color4F&)>& value)
        {
            _p->callback = value;
        }
    }
}
