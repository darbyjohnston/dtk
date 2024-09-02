// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/ScrollArea.h>

namespace dtk
{
    namespace ui
    {
        //! \name Layouts
        ///@{
        
        //! Scroll widget.
        class ScrollWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                ScrollType,
                const std::shared_ptr<IWidget>& parent);

            ScrollWidget();

        public:
            virtual ~ScrollWidget();

            //! Create a new widget.
            static std::shared_ptr<ScrollWidget> create(
                const std::shared_ptr<core::Context>&,
                ScrollType = ScrollType::Both,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the widget.
            const std::shared_ptr<IWidget>& getWidget() const;

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Get the viewport geometry.
            core::Box2I getViewport() const;

            //! Get the scroll size.
            const core::Size2I& getScrollSize() const;

            //! Get the scroll position.
            const core::V2I& getScrollPos() const;

            //! Set the scroll position.
            void setScrollPos(const core::V2I&, bool clamp = true);

            //! Scroll to make the given box visible.
            void scrollTo(const core::Box2I&);

            //! Set the scroll position callback.
            void setScrollPosCallback(const std::function<void(const core::V2I&)>&);

            //! Get whether the scroll bars are visible.
            bool areScrollBarsVisible() const;

            //! Set whether the scroll bars are visible.
            void setScrollBarsVisible(bool);

            //! Get whether scroll events are enabled.
            bool areScrollEventsEnabled() const;

            //! Set whether scroll events are enabled.
            void setScrollEventsEnabled(bool);

            //! Get whether the scroll area has a border.
            bool hasBorder() const;

            //! Set whether the scroll area has a border.
            void setBorder(bool);

            //! Get the margin role.
            SizeRole getMarginRole() const;

            //! Set the margin role.
            void setMarginRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void scrollEvent(ScrollEvent&) override;
            void keyPressEvent(KeyEvent&) override;
            void keyReleaseEvent(KeyEvent&) override;

        private:
            int _getLineStep() const;
            int _getPageStep() const;

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
