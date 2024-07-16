// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/IWidgetPopup.h>

namespace dtk
{
    namespace ui
    {
        //! \name Color Widgets
        ///@{

        //! Color popup.
        class ColorPopup : public IWidgetPopup
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const core::Color4F&,
                const std::shared_ptr<IWidget>& parent);

            ColorPopup();

        public:
            virtual ~ColorPopup();

            //! Create a new popup.
            static std::shared_ptr<ColorPopup> create(
                const std::shared_ptr<core::Context>&,
                const core::Color4F&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set the callback.
            void setCallback(const std::function<void(const core::Color4F&)>&);

        private:
            DTK_PRIVATE();
        };

        ///@}
    }
}
