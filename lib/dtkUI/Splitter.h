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
        
        //! Splitter widget.
        class Splitter : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent);

            Splitter();

        public:
            virtual ~Splitter();

            //! Create a new widget.
            static std::shared_ptr<Splitter> create(
                const std::shared_ptr<core::Context>&,
                Orientation,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the split values.
            std::vector<float> getSplit() const;

            //! Set the split values.
            void setSplit(const std::vector<float>&);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void childAddEvent(const ChildAddEvent&) override;
            void childRemoveEvent(const ChildRemoveEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mouseEnterEvent() override;
            void mouseLeaveEvent() override;
            void mouseMoveEvent(MouseMoveEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;
            void mouseReleaseEvent(MouseClickEvent&) override;

        protected:
            void _releaseMouse() override;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
