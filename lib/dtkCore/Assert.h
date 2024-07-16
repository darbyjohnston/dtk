// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

//! Project namespace
namespace dtk
{
    namespace core
    {
        //! \name Assert
        ///@{
        
        //! Assert (for convenience use the DTK_ASSERT macro).
        void _assert(const char* file, int line);

        ///@}
    }
}

//! Assert macro.
#if defined(DTK_ASSERT)
#undef DTK_ASSERT
#define DTK_ASSERT(value) \
    if (!(value)) \
        dtk::core::_assert(__FILE__, __LINE__)
#else // DTK_ASSERT
#define DTK_ASSERT(value)
#endif // DTK_ASSERT

