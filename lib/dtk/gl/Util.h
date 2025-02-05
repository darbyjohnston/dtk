// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Image.h>

#include <memory>
#include <string>

namespace dtk
{
    namespace gl
    {
        //! \name Utility
        ///@{

        //! Get the glReadPixels format.
        unsigned int getReadPixelsFormat(dtk::ImageType);

        //! Get the glReadPixels type.
        unsigned int getReadPixelsType(dtk::ImageType);

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
