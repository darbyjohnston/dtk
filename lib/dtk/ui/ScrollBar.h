// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Layouts
    ///@{

    //! Scroll bar.
    class ScrollBar : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent);

        ScrollBar();

    public:
        virtual ~ScrollBar();

        //! Create a new widget.
        static std::shared_ptr<ScrollBar> create(
            const std::shared_ptr<Context>&,
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
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void mouseEnterEvent(MouseEnterEvent&) override;
        void mouseLeaveEvent() override;
        void mouseMoveEvent(MouseMoveEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;
        void mouseReleaseEvent(MouseClickEvent&) override;

    private:
        Box2I _getHandleGeometry() const;
        int _getScrollPosMax() const;
        float _getScrollScale() const;

        DTK_PRIVATE();
    };

    ///@}
}