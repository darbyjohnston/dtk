// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/ISystem.h>

namespace dtk
{
    namespace gl
    {
        //! OpenGL system.
        class System : public core::ISystem
        {
        protected:
            System(const std::shared_ptr<core::Context>&);

        public:
            virtual ~System();

            //! Create a new system.
            static std::shared_ptr<System> create(const std::shared_ptr<core::Context>&);
        
        private:
            DTK_PRIVATE();
        };
    }
}
