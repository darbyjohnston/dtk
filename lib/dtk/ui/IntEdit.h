// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IWidget.h>
#include <dtk/ui/IntModel.h>

namespace dtk
{
    namespace ui
    {
        //! \name Numeric Widgets
        ///@{

        //! Integer value editor.
        class IntEdit : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IntModel>&,
                const std::shared_ptr<IWidget>& parent);

            IntEdit();

        public:
            virtual ~IntEdit();

            //! Create a new widget.
            static std::shared_ptr<IntEdit> create(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<IntModel>& = nullptr,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the value.
            int getValue() const;

            //! Set the value.
            void setValue(int);

            //! Set the callback.
            void setCallback(const std::function<void(int)>&);

            //! Get the range.
            const RangeI& getRange() const;

            //! Set the range.
            void setRange(const RangeI&);

            //! Get the step.
            int getStep() const;

            //! Set the step.
            void setStep(int);

            //! Get the large step.
            int getLargeStep() const;

            //! Set the large step.
            void setLargeStep(int);

            //! Get the model.
            const std::shared_ptr<IntModel>& getModel() const;

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

            DTK_PRIVATE();
        };
        
        ///@}
    }
}
