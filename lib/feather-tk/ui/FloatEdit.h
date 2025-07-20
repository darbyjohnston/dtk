// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/FloatModel.h>
#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name Numeric Widgets
    ///@{
        
    //! Floating point value editor.
    class FloatEdit : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<FloatModel>&,
            const std::shared_ptr<IWidget>& parent);

        FloatEdit();

    public:
        virtual ~FloatEdit();

        //! Create a new widget.
        static std::shared_ptr<FloatEdit> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Create a new widget.
        static std::shared_ptr<FloatEdit> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<FloatModel>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the value.
        float getValue() const;

        //! Set the value.
        void setValue(float);

        //! Set the callback.
        void setCallback(const std::function<void(float)>&);

        //! Get the range.
        const RangeF& getRange() const;

        //! Set the range.
        void setRange(const RangeF&);

        //! Set the range.
        void setRange(float, float);

        //! Get the step.
        float getStep() const;

        //! Set the step.
        void setStep(float);

        //! Get the large step.
        float getLargeStep() const;

        //! Set the large step.
        void setLargeStep(float);

        //! Get the model.
        const std::shared_ptr<FloatModel>& getModel() const;

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
        void keyPressEvent(KeyEvent&) override;
        void keyReleaseEvent(KeyEvent&) override;

    private:
        void _textUpdate();

        FEATHER_TK_PRIVATE();
    };

    //! Floating point reset button.
    class FloatResetButton : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<FloatModel>&,
            const std::shared_ptr<IWidget>& parent);

        FloatResetButton();

    public:
        virtual ~FloatResetButton();

        //! Create a new widget.
        static std::shared_ptr<FloatResetButton> create(
            const std::shared_ptr<Context>&,
            const std::shared_ptr<FloatModel>&,
            const std::shared_ptr<IWidget>& parent = nullptr);

        void setGeometry(const Box2I&) override;
        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        void _widgetUpdate();

        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
