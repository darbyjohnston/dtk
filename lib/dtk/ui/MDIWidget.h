// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    namespace ui
    {
        class MDICanvas;

        //! \name MDI Widgets
        ///@{

        //! MDI resize directions.
        enum class MDIResize
        {
            None,
            North,
            NorthEast,
            East,
            SouthEast,
            South,
            SouthWest,
            West,
            NorthWest,

            Count,
            First = North
        };
        DTK_ENUM(MDIResize);

        //! MDI widget.
        class MDIWidget : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::shared_ptr<IWidget>& parent);

            MDIWidget();

        public:
            virtual ~MDIWidget();

            //! Create a new widget.
            static std::shared_ptr<MDIWidget> create(
                const std::shared_ptr<core::Context>&,
                const std::string& title,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the title.
            const std::string& getTitle() const;

            //! Set the title.
            void setTitle(const std::string&);

            //! Get the widget.
            const std::shared_ptr<IWidget>& getWidget() const;

            //! Set the widget.
            void setWidget(const std::shared_ptr<IWidget>&);

            //! Set the press callback.
            void setPressCallback(const std::function<void(bool)>&);

            //! Set the move callback.
            void setMoveCallback(const std::function<void(const core::V2I&)>&);

            //! Set the resize callback.
            void setResizeCallback(const std::function<void(MDIResize, const core::V2I&)>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        private:
            core::Box2I _addMargins(const core::Box2I&) const;
            core::Box2I _removeMargins(const core::Box2I&) const;
            core::Size2I _removeMargins(const core::Size2I&) const;

            friend class MDICanvas;

            DTK_PRIVATE();
        };

        ///@}
    }
}
