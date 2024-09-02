// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <memory>
#include <string>

namespace dtk
{
    namespace gl
    {
        //! \name Utility
        ///@{
        
        //! Set whether an OpenGL capability is enabled and restore it to the
        //! previous value when finished.
        class SetAndRestore
        {
        public:
            SetAndRestore(unsigned int, bool);

            ~SetAndRestore();

        private:
            DTK_PRIVATE();
        };

        //! Get an OpenGL error label.
        std::string getErrorLabel(unsigned int);
        
        ///@}
    }
}
