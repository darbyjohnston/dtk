// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    namespace examples
    {
        namespace textedit
        {
            class TextWidget : public IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent);

                TextWidget();

            public:
                virtual ~TextWidget();

                static std::shared_ptr<TextWidget> create(
                    const std::shared_ptr<Context>&,
                    const std::shared_ptr<IWidget>& parent = nullptr);

            private:
                FEATHER_TK_PRIVATE();
            };
        }
    }
}
