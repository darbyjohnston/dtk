// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUI/MDIWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name MDI Widgets
        ///@{

        //! MDI canvas.
        //!
        //! \todo Add support for maximizing MDI widgets.
        class MDICanvas : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            MDICanvas();

        public:
            virtual ~MDICanvas();

            //! Create a new canvas.
            static std::shared_ptr<MDICanvas> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the canvas size.
            const core::Size2I& getCanvasSize() const;

            //! Set the canvas size.
            void setCanvasSize(const core::Size2I&);

            //! Get the grid size.
            const core::Size2I& getGridSize() const;

            //! Set the grid size.
            void setGridSize(const core::Size2I&);

            //! Add a widget to the canvas.
            std::shared_ptr<MDIWidget> addWidget(
                const std::string& title,
                const core::V2I& pos,
                const std::shared_ptr<IWidget>&);

            void setGeometry(const core::Box2I&) override;
            void childRemoveEvent(const ChildRemoveEvent&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        private:
            int _snapToGridX(int) const;
            int _snapToGridY(int) const;
            core::Size2I _snapToGrid(const core::Size2I&) const;

            DTK_PRIVATE();
        };

        ///@}
    }
}
