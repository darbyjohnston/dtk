// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace dtk
{
    namespace core
    {
        inline const std::weak_ptr<Context>& ISystem::getContext() const
        {
            return _context;
        }

        inline const std::string& ISystem::getName() const
        {
            return _name;
        }
    }
}
