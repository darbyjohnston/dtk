// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name Layouts
    ///@{

    //! Spacer widget.
    class Spacer : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent);

        Spacer();

    public:
        virtual ~Spacer();

        //! Create a new widget.
        static std::shared_ptr<Spacer> create(
            const std::shared_ptr<Context>&,
            Orientation,
            const std::shared_ptr<IWidget>& parent = nullptr);

        //! Get the spacing role.
        SizeRole getSpacingRole() const;

        //! Set the spacing role.
        void setSpacingRole(SizeRole);

        void sizeHintEvent(const SizeHintEvent&) override;

    private:
        FEATHER_TK_PRIVATE();
    };

    ///@}
}