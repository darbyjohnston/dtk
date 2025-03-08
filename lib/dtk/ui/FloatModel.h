// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/ObservableValue.h>
#include <dtk/core/Range.h>

namespace dtk
{
    class Context;
    
    //! \name Numeric Widgets
    ///@{

    //! Floating point value model.
    class FloatModel : public std::enable_shared_from_this<FloatModel>
    {
        DTK_NON_COPYABLE(FloatModel);

        void _init(const std::shared_ptr<Context>&);

    protected:
        FloatModel();

    public:
        ~FloatModel();

        //! Create a new model.
        static std::shared_ptr<FloatModel> create(
            const std::shared_ptr<Context>&);

        //! \name Value
        ///@{

        //! Get the value.
        float getValue() const;

        //! Observe the value.
        std::shared_ptr<IObservableValue<float> > observeValue() const;

        //! Set the value.
        void setValue(float);

        ///@}

        //! \name Range
        ///@{

        //! Get the range.
        const RangeF& getRange() const;

        //! Observe the range.
        std::shared_ptr<IObservableValue<RangeF> > observeRange() const;

        //! Set the range.
        void setRange(const RangeF&);

        ///@}

        //! \name Increment
        ///@{

        //! Get the increment step.
        float getStep() const;

        //! Set the increment step.
        void setStep(float);

        //! Increment the value by a step.
        void incrementStep();

        //! Decrement the value by a step.
        void decrementStep();

        //! Get the increment large step.
        float getLargeStep() const;

        //! Set the increment large step.
        void setLargeStep(float);

        //! Increment the value by a large step.
        void incrementLargeStep();

        //! Decrement the value by a large step.
        void decrementLargeStep();

        ///@}

        //! \name Default Value
        ///@{

        //! Get whether there is a default value.
        bool hasDefaultValue() const;

        //! Observe the default value.
        std::shared_ptr<IObservableValue<bool> > observeHasDefaultValue() const;

        //! Get the default value.
        float getDefaultValue() const;

        //! Set the default value.
        void setDefaultValue(float);

        //! Set the value to the default value.
        void setDefaultValue();

        //! Clear the default value.
        void clearDefaultValue();

        ///@}

    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
