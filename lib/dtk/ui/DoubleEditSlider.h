// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/DoubleModel.h>
#include <dtk/ui/IWidget.h>

namespace dtk
{
    //! \name Numeric Widgets
    ///@{
        
    //! Double precision floating point value editor and slider.
    class DoubleEditSlider : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<DoubleModel>&,
            const std::shared_ptr<IWidget>& parent);

        DoubleEditSlider();

    public:
        virtual ~DoubleEditSlider();

        //! Create a new widget.
        static std::shared_ptr<DoubleEditSlider> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<DoubleEditSlider> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<DoubleModel>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the value.
        double getValue() const;

        //! Set the value.
        void setValue(double);

        //! Set the callback.
        void setCallback(const std::function<void(double)>&);

        //! Get the range.
        const RangeD& getRange() const;

        //! Set the range.
        void setRange(const RangeD&);

        //! Get the step.
        double getStep() const;

        //! Set the step.
        void setStep(double);

        //! Get the large step.
        double getLargeStep() const;

        //! Set the large step.
        void setLargeStep(double);

        //! Get the default value.
        double getDefaultValue() const;

        //! Set the default value.
        void setDefaultValue(double);

        //! Get the model.
        const std::shared_ptr<DoubleModel>& getModel() const;

        //! Get the display precision.
        int getPrecision() const;

        //! Set the display precision.
        void setPrecision(int);

        //! Get the font role.
        FontRole getFontRole() const;

        //! Set the font role.
        void setFontRole(FontRole);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
