// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <uiTest/App.h>
#include <uiTest/Window.h>

#include <dtk/ui/ButtonGroup.h>

#include <testLib/ITest.h>

namespace dtk
{
    namespace ui_test
    {
        class ListWidgetTest : public test::ITest
        {
        protected:
            ListWidgetTest(const std::shared_ptr<Context>&);

        public:
            virtual ~ListWidgetTest();

            static std::shared_ptr<ListWidgetTest> create(
                const std::shared_ptr<Context>&);

            void run() override;

        private:
            void _test(
                const std::shared_ptr<Context>&,
                const std::shared_ptr<App>&,
                const std::shared_ptr<Window>&,
                ButtonGroupType);
        };
    }
}

