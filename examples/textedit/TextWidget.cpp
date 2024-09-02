// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "TextWidget.h"

using namespace dtk;
using namespace dtk::ui;

namespace dtk
{
    namespace examples
    {
        namespace textedit
        {
            struct TextWidget::Private
            {};

            void TextWidget::_init(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                ui::IWidget::_init(context, "dtk::examples::textedit::TextWidget", parent);
            }

            TextWidget::TextWidget() :
                _p(new Private)
            {}

            TextWidget::~TextWidget()
            {}

            std::shared_ptr<TextWidget> TextWidget::create(
                const std::shared_ptr<Context>& context,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<TextWidget>(new TextWidget);
                out->_init(context, parent);
                return out;
            }
        }
    }
}
