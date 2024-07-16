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
        
        //! Scroll bar.
        class ScrollBar : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent);

            ScrollBar();

        public:
            virtual ~ScrollBar();

            //! Create a new widget.
            static std::shared_ptr<ScrollBar> create(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the scroll size.
            int getScrollSize() const;

            //! Set the scroll size.
            void setScrollSize(int);

            //! Get the scroll position.
            int getScrollPos() const;

            //! Set the scroll position.
            void setScrollPos(int);

            //! Set the scroll position callback.
            void setScrollPosCallback(const std::function<void(int)>&);

            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseEnterEvent() override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        private:
            core::Box2I _getBorderGeometry() const;
            core::Box2I _getHandleGeometry() const;
            int _getScrollPosMax() const;
            float _getScrollScale() const;

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
