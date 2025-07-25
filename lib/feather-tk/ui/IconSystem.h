// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <feather-tk/core/Context.h>
#include <feather-tk/core/ISystem.h>
#include <feather-tk/core/Image.h>

#include <future>

namespace feather_tk
{
    //! \name Icons
    ///@{

    struct IconRequest
    {
        uint64_t id = 0;
        std::future<std::shared_ptr<Image> > future;
    };
        
    //! Icon system.
    class IconSystem : public ISystem
    {
        FEATHER_TK_NON_COPYABLE(IconSystem);

    protected:
        void _init(const std::shared_ptr<Context>&);

        IconSystem(const std::shared_ptr<Context>&);

    public:
        ~IconSystem();

        //! Create a new system.
        static std::shared_ptr<IconSystem> create(
            const std::shared_ptr<Context>&);

        //! Get the icon names.
        std::vector<std::string> getNames() const;
        
        //! Add an icon. The icon is stored as an SVG file.
        void add(const std::string& name, const std::vector<uint8_t>& svg);

        //! Get an icon.
        std::shared_ptr<Image> get(
            const std::string& name,
            float displayScale);

        //! Request an async icon.
        IconRequest request(
            const std::string& name,
            float displayScale);

        //! Cancel async requests.
        void cancelRequests(const std::vector<uint64_t>&);

    private:
        FEATHER_TK_PRIVATE();
    };
        
    ///@}
}
