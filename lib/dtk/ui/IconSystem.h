// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/Context.h>
#include <dtk/core/ISystem.h>
#include <dtk/core/Image.h>

#include <future>

namespace dtk
{
    //! \name Icons
    ///@{
        
    //! Icon system.
    class IconSystem : public ISystem
    {
        DTK_NON_COPYABLE(IconSystem);

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
        
        //! Request an icon.
        std::future<std::shared_ptr<Image> > request(
            const std::string& name,
            float displayScale);

        //! Cancel requests.
        void cancelRequests();
            
    private:
        DTK_PRIVATE();
    };
        
    ///@}
}
