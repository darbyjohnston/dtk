// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/ISystem.h>
#include <dtk/core/ObservableList.h>
#include <dtk/core/Size.h>
#include <dtk/core/Vector.h>

#include <array>

namespace dtk
{
    namespace gl
    {
        //! Monitor information.
        struct MonitorInfo
        {
            std::string name;
            Size2I size;
            std::array<int, 3> colorBits = { 0, 0, 0 };
            int refreshRate = 0;
            V2F contentScale = V2F(1.F, 1.F);
            V2I pos;
            Size2I physicalSizeMM;

            bool operator == (const MonitorInfo&) const;
            bool operator != (const MonitorInfo&) const;
        };

        //! OpenGL system.
        class System : public ISystem
        {
        protected:
            System(const std::shared_ptr<Context>&);

        public:
            virtual ~System();

            //! Create a new system.
            static std::shared_ptr<System> create(const std::shared_ptr<Context>&);

            //! Observe the monitors.
            std::shared_ptr<IObservableList<MonitorInfo> > observeMonitors() const;
        
        private:
            DTK_PRIVATE();
        };
    }
}
