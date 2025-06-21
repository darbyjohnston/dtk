// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "ColorWidgets.h"

#include <dtk/ui/ColorWidget.h>

void ColorWidgets::_init(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    IWidget::_init(context, "ColorWidgets", parent);
    
    _layout = HorizontalLayout::create(context, shared_from_this());
    _layout->setMarginRole(SizeRole::Margin);

    ColorWidget::create(context, _layout);

    auto colorWidget = ColorWidget::create(context, _layout);
    colorWidget->setMode(ColorWidgetMode::HSV);
}

ColorWidgets::~ColorWidgets()
{}

std::shared_ptr<ColorWidgets> ColorWidgets::create(
    const std::shared_ptr<Context>& context,
    const std::shared_ptr<IWidget>& parent)
{
    auto out = std::shared_ptr<ColorWidgets>(new ColorWidgets);
    out->_init(context, parent);
    return out;
}

void ColorWidgets::setGeometry(const Box2I& value)
{
    IWidget::setGeometry(value);
    _layout->setGeometry(value);
}

void ColorWidgets::sizeHintEvent(const SizeHintEvent& event)
{
    IWidget::sizeHintEvent(event);
    _setSizeHint(_layout->getSizeHint());
}
