// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Color Widgets
    ///@{

    enum class ColorWidgetMode
    {
        RGB,
        HSV,
        Swatches,

        Count,
        First = RGB
    };
    DTK_ENUM(ColorWidgetMode);

    //! Color widget.
    //!
    //! \todo Add a palette for saving colors.
    //! \todo Add support for displaying pixel types like U8, U16, etc.?
    class ColorWidget : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent);

        ColorWidget();

    public:
        virtual ~ColorWidget();

        //! Create a new widget.
        static std::shared_ptr<ColorWidget> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the color.
        const Color4F& getColor() const;

        //! Set the color.
        void setColor(const Color4F&);

        //! Set the color callback.
        void setCallback(const std::function<void(const Color4F&)>&);

        //! Get the widget mode.
        ColorWidgetMode getMode() const;

        //! Set the widget mode.
        void setMode(ColorWidgetMode);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _modeUpdate();
        void _colorUpdate();

        DTK_PRIVATE();
    };

    ///@}
}
