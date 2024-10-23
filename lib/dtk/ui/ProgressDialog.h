// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/ui/IDialog.h>

#include <dtk/core/Range.h>

namespace dtk
{
    //! \name Dialogs
    ///@{

    //! Progress dialog.
    class ProgressDialog : public IDialog
    {
    protected:
        void _init(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent);

        ProgressDialog();

    public:
        virtual ~ProgressDialog();

        //! Create a new widget.
        static std::shared_ptr<ProgressDialog> create(
            const std::shared_ptr<Context>& context,
            const std::string& title,
            const std::string& text,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the range.
        const RangeD& getRange() const;

        //! Set the range.
        void setRange(const RangeD&);

        //! Get the value.
        double getValue() const;

        //! Set the value.
        void setValue(double);

    private:
        DTK_PRIVATE();
    };

    ///@}
}