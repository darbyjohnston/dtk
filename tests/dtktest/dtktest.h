// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtk/core/IApp.h>

namespace dtk
{
    namespace tests
    {
        //! Test application.
        class App : public core::IApp
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>& argv);

            App();

        public:
            virtual ~App();

            static std::shared_ptr<App> create(
                const std::shared_ptr<core::Context>&,
                std::vector<std::string>&);

            void run() override;
            
        private:
            DTK_PRIVATE();
        };
    }
}

