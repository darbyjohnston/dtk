// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/DoubleModel.h>
#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name Numeric Widgets
    ///@{
        
    //! Double precision floating point value slider.
    class DoubleSlider : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<DoubleModel>&,
            const std::shared_ptr<IWidget>& parent);

        DoubleSlider();

    public:
        virtual ~DoubleSlider();

        //! Create a new widget.
        static std::shared_ptr<DoubleSlider> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<DoubleSlider> create(
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

        //! Get the model.
        const std::shared_ptr<DoubleModel>& getModel() const;

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;
        void clipEvent(const Box2I&, bool) override;
        void drawEvent(const Box2I&, const DrawEvent&) override;
        void mouseEnterEvent(MouseEnterEvent&) override;
        void mouseLeaveEvent() override;
        void mouseMoveEvent(MouseMoveEvent&) override;
        void mousePressEvent(MouseClickEvent&) override;
        void mouseReleaseEvent(MouseClickEvent&) override;
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        Box2I _getSliderGeometry() const;

        double _posToValue(int) const;
        int _valueToPos(double) const;

        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
