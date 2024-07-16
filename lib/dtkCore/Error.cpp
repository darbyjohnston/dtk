// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <dtkCore/Error.h>

namespace dtk
{
    namespace core
    {
        ParseError::ParseError() :
            invalid_argument("Cannot parse value")
        {}
    }
}
