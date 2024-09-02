// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    namespace ui
    {
        //! \name Color Widgets
        ///@{

        //! Color swatch widget.
        class ColorSwatch : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            ColorSwatch();

        public:
            virtual ~ColorSwatch();

            //! Create a new widget.
            static std::shared_ptr<ColorSwatch> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the color.
            const core::Color4F& getColor() const;

            //! Set the color.
            void setColor(const core::Color4F&);

            //! Get whether the color is editable.
            bool isEditable() const;

            //! Set whether the color is editable.
            void setEditable(bool);

            //! Set the color callback.
            void setCallback(const std::function<void(const core::Color4F&)>&);

            //! Get the size role.
            SizeRole getSizeRole() const;

            //! Set the size role.
            void setSizeRole(SizeRole);

            void setGeometry(const core::Box2I&) override;
            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;
            void mousePressEvent(MouseClickEvent&) override;

        private:
            void _showPopup();

            DTK_PRIVATE();
        };

        ///@}
    }
}
