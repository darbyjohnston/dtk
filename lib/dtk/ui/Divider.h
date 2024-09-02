// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Divider widget.
        class Divider : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent);

            Divider();

        public:
            virtual ~Divider();

            //! Create a new widget.
            static std::shared_ptr<Divider> create(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent = nullptr);

            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
