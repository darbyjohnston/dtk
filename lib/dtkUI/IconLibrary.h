// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkCore/Context.h>
#include <dtkCore/Image.h>

#include <future>

namespace dtk
{
    namespace ui
    {
        //! \name Icons
        ///@{
        
        //! Icon library.
        class IconLibrary : public std::enable_shared_from_this<IconLibrary>
        {
            DTK_NON_COPYABLE(IconLibrary);

        protected:
            void _init(const std::shared_ptr<core::Context>&);

            IconLibrary();

        public:
            ~IconLibrary();

            //! Create a new icon library.
            static std::shared_ptr<IconLibrary> create(
                const std::shared_ptr<core::Context>&);

            //! Request an icon.
            std::future<std::shared_ptr<core::Image> > request(
                const std::string& name,
                float displayScale);

            //! Cancel requests.
            void cancelRequests();
            
        private:
            DTK_PRIVATE();
        };
        
        ///@}
    }
}

