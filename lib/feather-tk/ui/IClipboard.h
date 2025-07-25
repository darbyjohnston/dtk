// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Context.h>

namespace feather_tk
{
    //! \name Clipboard
    ///@{
        
    //! Base class for clipboards.
    class IClipboard : public std::enable_shared_from_this<IClipboard>
    {
        FEATHER_TK_NON_COPYABLE(IClipboard);

    protected:
        void _init(
            const std::shared_ptr<Context>&);

        IClipboard();

    public:
        virtual ~IClipboard() = 0;

        //! Get the clipboard text.
        virtual std::string getText() const = 0;

        //! Set the clipboard text.
        virtual void setText(const std::string&) = 0;

    private:
        std::weak_ptr<Context> _context;
    };
        
    ///@}
}
