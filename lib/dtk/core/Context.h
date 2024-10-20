// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Util.h>

#include <chrono>
#include <list>
#include <map>
#include <memory>

namespace dtk
{
    class ISystem;

    //! The context provides centralized access to systems and other
    //! resources.
    class Context : public std::enable_shared_from_this<Context>
    {
        DTK_NON_COPYABLE(Context);

    protected:
        Context() = default;

    public:
        ~Context();

        //! Create a new context.
        static std::shared_ptr<Context> create();

        //! Add a system.
        void addSystem(const std::shared_ptr<ISystem>&);

        //! Get the systems.
        const std::list<std::shared_ptr<ISystem> >& getSystems() const;

        //! Get a system by type.
        template<typename T>
        std::shared_ptr<T> getSystem() const;

        //! Get a system by name.
        std::shared_ptr<ISystem> getSystemByName(const std::string&) const;

        //! Tick the context.
        void tick();

    private:
        std::list<std::shared_ptr<ISystem> > _systems;
        std::map<std::shared_ptr<ISystem>, std::chrono::steady_clock::time_point> _systemTimes;
    };
}

#include <dtk/core/ContextInline.h>

