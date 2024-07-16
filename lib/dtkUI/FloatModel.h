// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/ObservableValue.h>
#include <dtkCore/Range.h>

namespace dtk
{
    namespace core
    {
        class Context;
    }
    
    namespace ui
    {
        //! \name Numeric Widgets
        ///@{

        //! Floating point value model.
        class FloatModel : public std::enable_shared_from_this<FloatModel>
        {
            DTK_NON_COPYABLE(FloatModel);

            void _init(const std::shared_ptr<core::Context>&);

        protected:
            FloatModel();

        public:
            ~FloatModel();

            //! Create a new model.
            static std::shared_ptr<FloatModel> create(
                const std::shared_ptr<core::Context>&);

            //! \name Value
            ///@{

            //! Get the value.
            float getValue() const;

            //! Set the value.
            void setValue(float);

            //! Observe the value.
            std::shared_ptr<core::IObservableValue<float> > observeValue() const;

            ///@}

            //! \name Range
            ///@{

            //! Get the range.
            const core::RangeF& getRange() const;

            //! Set the range.
            void setRange(const core::RangeF&);

            //! Observe the range.
            std::shared_ptr<core::IObservableValue<core::RangeF> > observeRange() const;

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
            std::shared_ptr<core::IObservableValue<bool> > observeHasDefaultValue() const;

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
}
