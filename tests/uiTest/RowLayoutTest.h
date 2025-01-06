// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024-2025 Darby Johnston
// All rights reserved.

#pragma once

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/RowLayout.h>

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class RowLayoutTest : public test::ITest
        {
        protected:
            RowLayoutTest(const std::shared_ptr<Context>&);

        public:
            virtual ~RowLayoutTest();

            static std::shared_ptr<RowLayoutTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                const std::shared_ptr<RowLayout>&,
                Orientation);
        };
    }
}

