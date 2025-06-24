// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#include "TextWidget.h"

using namespace feather_tk;

namespace feather_tk
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
                IWidget::_init(context, "feather_tk::examples::textedit::TextWidget", parent);
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
