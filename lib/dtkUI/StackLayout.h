// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/IWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Stack layout.
        class StackLayout : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            StackLayout();

        public:
            virtual ~StackLayout();

            //! Create a new layout.
            static std::shared_ptr<StackLayout> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the current index.
            int getCurrentIndex() const;

            //! Set the current index.
            void setCurrentIndex(int);

            //! Set the current widget.
            void setCurrentWidget(const std::shared_ptr<IWidget>&);

            //! Get the margin role.
            SizeRole getMarginRole() const;

            //! Set the margin role.
            void setMarginRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            core::Box2I getChildrenClipRect() const override;
            void childAddEvent(const ChildAddEvent&) override;
            void childRemoveEvent(const ChildRemoveEvent&) override;
            void sizeHintEvent(const SizeHintEvent&) override;

        private:
            std::shared_ptr<IWidget> _getCurrentWidget() const;

            void _widgetUpdate();

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
