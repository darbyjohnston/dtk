// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/ui/IWidget.h>

namespace feather_tk
{
    //! \name Popup Widgets
    ///@{
        
    //! Base class for popups.
    class IPopup : public IWidget
    {
    protected:
        void _init(
            const std::shared_ptr<Context>&,
            const std::string& objectName,
            const std::shared_ptr<IWidget>& parent = nullptr);

        IPopup();

    public:
        virtual ~IPopup() = 0;

        //! Close the popup.
        virtual void close() = 0;
    };
        
    ///@}
}
