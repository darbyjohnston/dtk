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
        
        //! Grid layout.
        class GridLayout : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            GridLayout();

        public:
            virtual ~GridLayout();

            //! Create a new layout.
            static std::shared_ptr<GridLayout> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Set a child position within the grid.
            void setGridPos(
                const std::shared_ptr<IWidget>&,
                int row,
                int column);

            //! Get the margin role.
            SizeRole getMarginRole() const;

            //! Set the margin role.
            void setMarginRole(SizeRole);

            //! Get the spacing role.
            SizeRole getSpacingRole() const;

            //! Set the spacing role.
            void setSpacingRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void childRemoveEvent(const ChildRemoveEvent&) override;

        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}
