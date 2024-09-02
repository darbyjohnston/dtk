// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Color Widgets
    ///@{

    //! Color swatch widget.
    class ColorSwatch : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        ColorSwatch();

    public:
        virtual ~ColorSwatch();

        //! Create a new widget.
        static std::shared_ptr<ColorSwatch> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the color.
        const Color4F& getColor() const;

        //! Set the color.
        void setColor(const Color4F&);

        //! Get whether the color is editable.
        bool isEditable() const;

        //! Set whether the color is editable.
        void setEditable(bool);

        //! Set the color callback.
        void setCallback(const std::function<void(const Color4F&)>&);

        //! Get the size role.
        SizeRole getSizeRole() const;

        //! Set the size role.
        void setSizeRole(SizeRole);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;

    private:
        void _showPopup();

        DTK_PRIVATE();
    };

    ///@}
}
