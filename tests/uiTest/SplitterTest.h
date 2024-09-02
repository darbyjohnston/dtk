// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class SplitterTest : public test::ITest
        {
        protected:
            SplitterTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~SplitterTest();

            static std::shared_ptr<SplitterTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ui::Orientation);
        };
    }
}

