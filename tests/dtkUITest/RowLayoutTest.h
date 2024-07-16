// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkUI/RowLayout.h>

#include <dtkTestLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class RowLayoutTest : public test::ITest
        {
        protected:
            RowLayoutTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~RowLayoutTest();

            static std::shared_ptr<RowLayoutTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<ui::RowLayout>&,
                ui::Orientation);
        };
    }
}

