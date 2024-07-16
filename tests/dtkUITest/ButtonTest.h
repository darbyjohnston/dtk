// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <dtkUITest/App.h>
#include <dtkUITest/Window.h>

#include <dtkTestLib/ITest.h>

#include <dtkUI/IButton.h>
#include <dtkUI/RowLayout.h>

namespace dtk
{
    namespace ui_test
    {
        class ButtonTest : public test::ITest
        {
        protected:
            ButtonTest(const std::shared_ptr<core::Context>&);

        public:
            virtual ~ButtonTest();

            static std::shared_ptr<ButtonTest> create(
                const std::shared_ptr<core::Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<ui::VerticalLayout>&,
                const std::shared_ptr<ui::IButton>&);
        };
    }
}

